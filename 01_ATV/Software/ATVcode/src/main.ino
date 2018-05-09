/*TODO: 
- eeprom save of calibrated values. should be triggered with a button press
during the first 5 seconds of startup. if button is not pressed,
last calibration values are loaded
- code refactoring
*/

#include <Arduino.h>
#include <EEPROM.h>     // lib for memory for saving calibration
#include <QTRSensors.h> // lib of line following sensors

//Function declarations
void set_motors(int motorspeed_l, int motorspeed_r);
void autoCalibration(int duration_cycles, bool enable_motors);
void showDebug();
void test_motors();
int eepromRead(int address);
void eepromWrite(int address, int value);
void initializeCalibrationArrays();

// ----------------------- L298N Motor Driver Pin Definitions ---------------------------------- //

#define PWM_LEFT 3  // pwm pin left motors
#define PWM_RIGHT 8 // pwm pin right motors

/* left side motor pins.
forward:  IN1 HIGH, IN2 LOW
backward: IN1 LOW,  IN2 HIGH
*/
#define IN1 4
#define IN2 5
/* right side motor pins
forward:  IN3 LOW,  IN4 HIGH
backward: IN3 HIGH,  IN4 LOW
*/
#define IN3 6
#define IN4 7

#define L_MINSPEED 0       // minimum pwm value of the left motors
#define R_MINSPEED 0       // minimum pwm value of the right motors
#define L_MAXSPEED 255     // max. pwm value of the left motors // initialized again as a not constant value
#define R_MAXSPEED 255     // max. pwm value of the right motors
#define L_DECELERATED 100
#define R_DECELERATED 100
const int MAX_BRAKE = 255; // the higher this pwm value (0-255), the harder the motors max. brake force (= backwards turn) during a curve of the opposite direction

// ----------------------- QTR-8RC Reflectance Sensor Array ------------------------------------- //

#define NUM_SENSORS 8 // number of reflectance sensors used
#define TIMEOUT 2500  // waits for 2500 us for sensor outputs to go low
//#define EMITTER_PIN 2             // emitterPin is the Arduino digital pin that controls whether the IR LEDs are on or off. Emitter is controlled by digital pin 2
#define DEBUG 0
QTRSensorsRC Qtrrc((unsigned char[]){A7, A6, A5, A4, A3, A2, A1, A0}, NUM_SENSORS, TIMEOUT); // instantiate object of class QTRSensorsRC; sensors nubered from left to right; A1 Sensor num 0

// ----------------------- PID Control ---------------------------------------------------------- //

#define KP 1
#define KD 5
int calibration_values[] = {708, 864, 812, 836, 784};

// ----------------------- Push Button ---------------------------------------------------------- //

#define BUTTON 2

// ----------------------- Misc ---------------------------------------------------------- //

const long startup_delay = 4000;
const long getOutOfBlackZoneTime = 500;
const long waitAtBlackBarTime = 5000;
int  l_maxspeed = L_MAXSPEED;
int  r_maxspeed = R_MAXSPEED;
bool fts_go = true;
bool fts_button_break = false;

// ----------------------- DO NOT CHANGE -------------------------------------------------------- //

int last_error = 0;
int position = 0;
int error = 0;
int motorSpeed = 0;
int motorspeed_l;
int motorspeed_r;
int address = 0;
unsigned int sensors[8]; // see QTR Doc .readline
unsigned int blackBarSnsrs[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // probably not really necessary, used for finding black markings on the underground
int cycles = 125;
unsigned long last_millis;
bool calibrated = 0;

// ----------------------- Setup -------------------------------------------------------- //

void setup()
{
  Serial.print("Jetzt kalibrieren");
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
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

// ----------------------- Loop -------------------------------------------------------- //

void loop()
{
  stopAtLongBlackBar();
  deccelerateAtBlackBarLeft();
  accelerateAtBlackBarRight();

  if (digitalRead(BUTTON) == LOW)
  {
    fts_button_break = !fts_button_break;
  }

  Qtrrc.readCalibrated(blackBarSnsrs);

  if (!fts_button_break)
  {

    if (fts_go == true)
    {
      position = Qtrrc.readLine(sensors);                // wert von 0 bis 1000*(NUM_SENSORS-1)
      error = position - (1000 * (NUM_SENSORS - 1)) / 2; // Anpassung des Wertes, damit die Mitte bei 0 ist
      motorSpeed = KP * error + KD * (error - last_error);
      last_error = error;

      motorspeed_l = L_MINSPEED + motorSpeed; // Der minimale motorSpeed wird um einen neuen erhöht. In userem Fall ist der minimumSpeed 0. D.h. liest der Sensor eine Null, so bleibt das Fahrzeug stehen. Siehe hierzu das Protokoll vom 27.01.18
      motorspeed_r = R_MINSPEED - motorSpeed;
      set_motors(motorspeed_l, motorspeed_r);
      //test_motors(); // only needed while debugging
    }
    else
    {
      set_motors(-1001, -1001);
      delay(100);
      set_motors(0, 0);
      delay(waitAtBlackBarTime);
      goFTS();
      getOutOfBlackZone(getOutOfBlackZoneTime);
    }
  }
  else
  {
    set_motors(0, 0);
  }
}

// ----------------------- Set Motors -------------------------------------------------------- //

void set_motors(int motorspeed_l, int motorspeed_r)
{
  // Anpassung der Geschwindigkeiten, falls sie einen Maximal- bzw. Minimalwert über(unter)schreiten

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

// ----------------------- Stop and go at Black Bars -------------------------------------------------------- //

void stopAtLongBlackBar()
{
  Qtrrc.readCalibrated(blackBarSnsrs);
  Serial.println(sensors[0]);
  if (blackBarSnsrs[0] >= 900 && blackBarSnsrs[1] >= 900 && blackBarSnsrs[2] >= 900 && blackBarSnsrs[3] >= 900 && blackBarSnsrs[4] >= 900 && blackBarSnsrs[5] >= 900 && blackBarSnsrs[6] >= 900 && blackBarSnsrs[7] >= 900)
  {
    Serial.print("Hi");
    fts_go = false;
  }
}

void goFTS()
{
  fts_go = true;
}

void getOutOfBlackZone(int waitTime) //exists to stop FTS from stopping immediately again after starting
{
  last_millis = millis();
  while (millis() <= last_millis + waitTime)
  {
    set_motors(100, 100);
  }
}

void deccelerateAtBlackBarLeft(){ //Sensor nr. 4 is not listed because it is not jet clear if it will read 0 or 1000
    if (blackBarSnsrs[0] >= 900 && blackBarSnsrs[1] >= 900 && blackBarSnsrs[2] >= 900 && blackBarSnsrs[3] >= 900 && blackBarSnsrs[5] <= 20 && blackBarSnsrs[6] <= 20 && blackBarSnsrs[7] <= 20){
      l_maxspeed = L_DECELERATED;
      r_maxspeed = R_DECELERATED;
    }
}

void accelerateAtBlackBarRight(){ //Sensor nr. 3 is not listed because it is not jet clear if it will read 0 or 1000
    if (blackBarSnsrs[0] <= 20 && blackBarSnsrs[1] <= 20 && blackBarSnsrs[2] <= 20 && blackBarSnsrs[4] >= 900 && blackBarSnsrs[5] >= 900 && blackBarSnsrs[6] >= 900 && blackBarSnsrs[7] >= 900){
      l_maxspeed = L_MAXSPEED;
      r_maxspeed = L_MINSPEED;
    }
}


// ----------------------- Calibration and saving of values -------------------------------------------------------- //

void autoCalibration(int duration_cycles, bool enable_motors) //this function makes the FTS spin in circles, in that process it will calibrate automatically
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

void eepromWrite(int addr, int value)
{
  //Decomposition from a int to 2 bytes by using bitshift.
  //One = Most significant -> two = Least significant byte
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);

  //Write the 2 bytes into the eeprom memory.
  EEPROM.write(addr, two);
  EEPROM.write(addr + 1, one);
}

int eepromRead(int addr)
{
  //Read the 4 bytes from the eeprom memory.
  int two = EEPROM.read(addr);
  int one = EEPROM.read(addr + 1);

  //Return the recomposed long by using bitshift.
  return ((two << 0) & 0xFF) + ((one << 8) & 0xFFFF);
}

void initializeCalibrationArrays()
{
  Qtrrc.calibrate(QTR_EMITTERS_ON);
}

// ----------------------- Debugging -------------------------------------------------------- //

void test_motors()
{
  //move forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(PWM_LEFT, 80);
  analogWrite(PWM_RIGHT, 80);

  delay(5000);
  //move backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(PWM_LEFT, 80);
  analogWrite(PWM_RIGHT, 80);

  delay(5000);
  //move left side backward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(PWM_LEFT, 80);
  analogWrite(PWM_RIGHT, 0);

  delay(5000);
  //move right side backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(PWM_LEFT, 0);
  analogWrite(PWM_RIGHT, 80);

  delay(5000);
}

void showDebug()
{
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(Qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(Qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
}