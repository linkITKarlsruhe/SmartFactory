#include "FTSlib.h"
const int NUM_SENSORS = 8;
const int TIMEOUT = 2500;
unsigned char usedDiodes[8] = {A7, A6, A5, A4, A3, A2, A1, A0};
QTRSensorsRC Qtrrc(usedDiodes, NUM_SENSORS, TIMEOUT); //TODO: Add to lib instantiate object of class QTRSensorsRC; sensors nubered from left to right; A1 Sensor num 0

FTSlib::FTSlib(int pinarray[5])
{
  pinMode(BUTTON, INPUT_PULLUP);
  IN1 = pinarray[0];
  IN2 = pinarray[1];
  IN3 = pinarray[2];
  IN4 = pinarray[3];
  BUTTON = pinarray[4];

  Qtrrc.readCalibrated(blackBarSnsrs);

  L_DECELERATED = 0;
  L_MAXSPEED = 0;
  L_MINSPEED = 255;
  R_DECELERATED = 255;
  R_MAXSPEED = 80;
  R_MINSPEED = 80;
  MAX_BRAKE = 255;
}

void FTSlib::accelerateAtBlackBarRight()
{
  //Sensor nr. 3 is not listed because it is not jet clear if it will read 0 or 1000
  if (blackBarSnsrs[0] >= 900 && blackBarSnsrs[1] >= 900 && blackBarSnsrs[2] >= 900 && blackBarSnsrs[3] >= 900 && blackBarSnsrs[5] <= 100 && blackBarSnsrs[6] <= 100 && blackBarSnsrs[7] <= 100)

  {
    l_maxspeed = 255;
    r_maxspeed = 255;
    Serial.println(l_maxspeed);
    Serial.println("Accelerate");
  }
}

void FTSlib::autoCalibration(int duration_cycles, bool enable_motors) //this function makes the FTS spin in circles, in that process it will calibrate automatically
{
  if (enable_motors)
  {
    // left side fwd
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    // right side bwd
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_LEFT, 125);
    analogWrite(PWM_RIGHT, 125);
  }
  for (int i = 0; i < duration_cycles; i++)
  {
    initializeCalibrationArrays();
    delay(20);
  }
  // Store calibration values in EEPROM
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    eepromWrite(4 * i, Qtrrc.calibratedMinimumOn[i]);
    eepromWrite((4 * i) + 2, Qtrrc.calibratedMaximumOn[i]);
    Serial.print("Written Qtrrc.calibratedMinimum/Maximum: ");
    Serial.print(Qtrrc.calibratedMinimumOn[i]);
    Serial.print(" / ");
    Serial.println(Qtrrc.calibratedMaximumOn[i]);
    Serial.println("////////");
  }
  calibrated = 1;
}

void FTSlib::calibrate()
{
  Serial.print("Jetzt kalibrieren");
  // if button is pressed within 5secs this part will calibrate the sensors to the environment
  last_millis = millis(); // Arduino standard function, returns number of milliseconds since board has been turned on

  while (millis() <= last_millis + startup_delay && !calibrated)
  {
    if (digitalRead(BUTTON) == LOW)
    {
      last_millis = millis();

      while (millis() <= last_millis + 2000L)
      {
        delay(200);
        if (digitalRead(BUTTON) == LOW)
        {
          Serial.println("Starting manual calibration...");
          autoCalibration(125, 0); // comp. to doc on autoCalibration
        }
      }
      Serial.print("calibrated: ");
      Serial.println(calibrated);

      // Start autoCalibration
      if (!calibrated)
      {
        Serial.println("Starting auto-calibration...");
        autoCalibration(250, 1); // comp. to doc on autoCalibration
      }
    }
  }

  // if no button was pressed, load previous calibration values from EEPROM
  if (!calibrated)
  {
    initializeCalibrationArrays(); // IMPORTANT! Otherwise Qtrrc.calibratedMinimumOn[i] / Qtrrc.calibratedMaximumOn[i] will not be initialized
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Qtrrc.calibratedMinimumOn[i] = eepromRead(4 * i);
      Qtrrc.calibratedMaximumOn[i] = eepromRead((4 * i) + 2);
      Serial.print("Loaded from EEPROM: Qtrrc.calibratedMinimum/Maximum: ");
      Serial.print(Qtrrc.calibratedMinimumOn[i]);
      Serial.print(" / ");
      Serial.println(Qtrrc.calibratedMaximumOn[i]);
      Serial.println("----------");
    }
  }
}

void FTSlib::checkButtonpress()
{
  if (digitalRead(BUTTON) == LOW)
  {
    fts_button_break = !fts_button_break;
  }
}

void FTSlib::decelerateAtBlackBarLeft()
{
  //Sensor nr. 4 is not listed because it is not jet clear if it will read 0 or 1000

  if (blackBarSnsrs[0] <= 100 && blackBarSnsrs[1] <= 100 && blackBarSnsrs[2] <= 100 && blackBarSnsrs[4] >= 900 && blackBarSnsrs[5] >= 900 && blackBarSnsrs[6] >= 900 && blackBarSnsrs[7] >= 900)
  {
    l_maxspeed = L_DECELERATED;
    r_maxspeed = R_DECELERATED;
    Serial.println("decc");
  }
}

int FTSlib::eepromRead(int address)
{
  //Read the 4 bytes from the eeprom memory.
  int two = EEPROM.read(address);
  int one = EEPROM.read(address + 1);

  //Return the recomposed long by using bitshift.
  return ((two << 0) & 0xFF) + ((one << 8) & 0xFFFF);
}

void FTSlib::eepromWrite(int address, int value)
{
  //Decomposition from a int to 2 bytes by using bitshift.
  //One = Most significant -> two = Least significant byte
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);

  //Write the 2 bytes into the eeprom memory.
  EEPROM.write(address, two);
  EEPROM.write(address + 1, one);
}

void FTSlib::getOutOfBlackZone(int waitTime)
{
  last_millis = millis();
  while (millis() <= last_millis + waitTime)
  {
    setMotors(100, 100);
  }
}

void FTSlib::goFTS()
{
  Serial.print("Go");
  fts_go = true;
}

void FTSlib::isStopped()
{
}

void FTSlib::stopAtLongBlackBar()
{
  Qtrrc.readCalibrated(blackBarSnsrs);
  if (blackBarSnsrs[0] >= 900 && blackBarSnsrs[1] >= 900 && blackBarSnsrs[2] >= 900 && blackBarSnsrs[3] >= 900 && blackBarSnsrs[4] >= 900 && blackBarSnsrs[5] >= 900 && blackBarSnsrs[6] >= 900 && blackBarSnsrs[7] >= 900)
  {
    Serial.print("Stop");
    fts_go = false;
  }
}

void FTSlib::updateDirection()
{
  if (fts_button_break)
  {

    if (fts_go)
    {
      position = Qtrrc.readLine(sensors);                // wert von 0 bis 1000*(NUM_SENSORS-1)
      error = position - (1000 * (NUM_SENSORS - 1)) / 2; // Anpassung des Wertes, damit die Mitte bei 0 ist
      motorSpeed = KP * error + KD * (error - last_error);
      last_error = error;

      motorspeed_l = L_MINSPEED + motorSpeed; // Der minimale motorSpeed wird um einen neuen erhöht. In userem Fall ist der minimumSpeed 0. D.h. liest der Sensor eine Null, so bleibt das Fahrzeug stehen. Siehe hierzu das Protokoll vom 27.01.18
      motorspeed_r = R_MINSPEED - motorSpeed;
      setMotors(motorspeed_l, motorspeed_r);
      //test_motors(); // only needed while debugging
    }
    else
    {
      setMotors(-1001, -1001);
      delay(100);
      setMotors(0, 0);
      delay(waitAtBlackBarTime);
      goFTS();
      getOutOfBlackZone(getOutOfBlackZoneTime);
    }
  }
  else
  {
    setMotors(0, 0);
  }
}

void FTSlib::initializeCalibrationArrays()
{
  Qtrrc.calibrate(QTR_EMITTERS_ON);
}

void FTSlib::setMotors(int motorspeed_l, int motorspeed_r)
{
  // Anpassung der Geschwindigkeiten, falls sie einen Maximal- bzw. Minimalwert über(unter)schreiten
  Serial.println("setMotors");
  Serial.println(motorspeed_l);
  Serial.println(IN1);

  if (motorspeed_l > l_maxspeed)
  {
    motorspeed_l = l_maxspeed;
  }
  if (motorspeed_r > r_maxspeed)
  {
    motorspeed_r = r_maxspeed;
  }
  if (motorspeed_l < -1000)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    motorspeed_l = map(motorspeed_l, -(NUM_SENSORS - 1), -5000, 0, MAX_BRAKE);
  }
  else
  {
    digitalWrite(IN1, HIGH); //TODO: backward/forward
    digitalWrite(IN2, LOW);
  }

  if (motorspeed_r < -1000)
  {
    motorspeed_r = map(motorspeed_r, -(NUM_SENSORS - 1), -5000, 0, MAX_BRAKE);
    // Serial.print("Brake R: "); Serial.println(motorspeed_r);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  analogWrite(PWM_LEFT, motorspeed_l);
  analogWrite(PWM_RIGHT, motorspeed_r);
}
