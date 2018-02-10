/*TODOS
- eeprom save of calibrated values. should be triggered with a button press
during the first 5 secs of startup. if button is not pressed,
last calibration values are loaded
- code refactoring
*/

#include <Arduino.h>
#include <QTRSensors.h>


//Function declarations
void set_motors(int motorspeed_l, int motorspeed_r);
void manualCalibration(const int *manual_calibration_values);
void autoCalibration(int duration_cycles, bool enable_motors);
void showDebug();
void test_motors();

// ----------------------- L298N Motor Driver Pin Definitions ---------------------------------- //
#define PWM_LEFT 3                // pwm pin left motors
#define PWM_RIGHT 8               // pwm pin right motors
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

#define L_MINSPEED 0                // minimum pwm val of the left motors
#define R_MINSPEED 0                // minimum pwm val of the right motors
#define L_MAXSPEED 255              // max. pwm val of the left motors
#define R_MAXSPEED 255              // max. pwm val of the right motors
const int MAX_BRAKE = 255;          // the higher this pwm value (0-255), the harder the motors max. brake force (= backwards turn) during a curve of the opposite direction

// ----------------------- QTR-8RC Reflectance Sensor Array ------------------------------------- //
#define NUM_SENSORS 4               // number of reflectance sensors used
#define TIMEOUT 2500                // waits for 2500 us for sensor outputs to go low
//#define EMITTER_PIN 2             // emitterPin is the Arduino digital pin that controls whether the IR LEDs are on or off. Emitter is controlled by digital pin 2
#define DEBUG 0
QTRSensorsRC Qtrrc((unsigned char[]){A6,A4,A3,A1}, NUM_SENSORS, TIMEOUT);   // instanciate object of class QTRSensorsRC
// ----------------------- PID Control ---------------------------------------------------------- //
#define KP 1
#define KD 5
int calibration_values[] = {708, 864, 812, 836, 784};

// ----------------------- Push Button ---------------------------------------------------------- //
#define BUTTON 2

// ----------------------- DO NOT CHANGE -------------------------------------------------------- //
int last_error = 0;
int position = 0;
int error = 0;
int motorSpeed = 0;
int motorspeed_l;
int motorspeed_r;
unsigned int sensors[8];
int cycles = 125;
unsigned long last_millis;
bool calibrated = 0;


void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  // autoCalibration(1,0);
  // Serial.println("AutoCalibration Done.");
  // Serial.println("Loading values from manual calibration before ...");
  // manualCalibration(manual_calibration);
  // showDebug();

  // if button is pressed within 5secs
  last_millis = millis();
  Serial.print("Last Millis:"); Serial.println(last_millis);
  while (millis() <= last_millis + 10000L && !calibrated) {
    if (digitalRead(BUTTON) == LOW) {
      last_millis = millis();
      while (millis() <= last_millis + 2000L) {
        delay(200);
        if (digitalRead(BUTTON) == LOW) {
        Serial.println("Starting manual calibration... Please hover the ATV over the line");
        autoCalibration(125,0);
        }
      }
      Serial.print("calibrated: "); Serial.println(calibrated);
      if (!calibrated) {
        Serial.println("Starting autocalibration...");
        autoCalibration(250,1);
      }
    }
  }

  // if no button was pressed, load previous calibration values from EEPROM
  // hwReadConfigBlock((void*)&kp, (void*)(1), 4);
  // hwReadConfigBlock((void*)&ki, (void*)(5), 4);
  // hwReadConfigBlock((void*)&kd, (void*)(9), 4);
  // if (!calibrated) {
  //   autoCalibration(1,0);
  //   for (int i=0;i<NUM_SENSORS;i++) {
  //     hwReadConfigBlock((void*)&Qtrrc.calibratedMinimumOn[i], (void*)(1), 4);
  //     Qtrrc.calibratedMaximumOn[i];
  //   }
  // }

}


void loop() {
  position = Qtrrc.readLine(sensors); // wert von 0 bis 1000*(NUM_SENSORS-1)
  Serial.println(position);
  error = position - (1000*(NUM_SENSORS-1))/2;            // Anpassung des Wertes, damit die Mitte bei 0 ist
  motorSpeed = KP * error + KD * (error - last_error);
  last_error = error;

  motorspeed_l = L_MINSPEED + motorSpeed; // Der minimale motorSpeed wird um einen neuen erhöht. In userem Fall ist der minimumSpeed 0. D.h. liest der Sensor eine Null, so bleibt das Fahrzeug stehen. Siehe hierzu das Protokoll vom 27.01.18
  motorspeed_r = R_MINSPEED - motorSpeed;
  set_motors(motorspeed_l, motorspeed_r);
  //test_motors();
}

void test_motors() {
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

void set_motors(int motorspeed_l, int motorspeed_r) {
  // Anpassung der Geschwindigkeiten, falls sie einen Maximal- bzw. Minimalwert über(unter)schreiten

  if (motorspeed_l > L_MAXSPEED)
    motorspeed_l = L_MAXSPEED;
  if (motorspeed_r > R_MAXSPEED)
    motorspeed_r = R_MAXSPEED;
  if (motorspeed_l < -1000) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    // Serial.print("motorspeed_l unconverted: "); Serial.print(motorspeed_l);
    motorspeed_l = map(motorspeed_l,-(NUM_SENSORS-1),-1000,0,MAX_BRAKE);
    // Serial.print(" / converted:"); Serial.println(motorspeed_l);
    // Serial.print("Brake L: "); Serial.println(motorspeed_l);
  } else {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }

  if (motorspeed_r < -1000) {
    motorspeed_r = map(motorspeed_r,-(NUM_SENSORS-1),-1000,0,MAX_BRAKE);
    // Serial.print("Brake R: "); Serial.println(motorspeed_r);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  analogWrite(PWM_LEFT, motorspeed_l);
  analogWrite(PWM_RIGHT, motorspeed_r);
}

void manualCalibration(const int *fixed_values) {
  for (int i=0; i < NUM_SENSORS; i++) {
    Qtrrc.calibratedMinimumOn[i] = fixed_values[i];
    Qtrrc.calibratedMaximumOn[i] = 2500;
  }
}

void autoCalibration(int duration_cycles, bool enable_motors) {
  if (enable_motors) {
    // left side fwd
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    // right side bwd
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_LEFT, 125);
    analogWrite(PWM_RIGHT, 125);
  }
  for (int i = 0; i < duration_cycles; i++) {
    Qtrrc.calibrate(QTR_EMITTERS_ON);
    delay(20);
  }
  calibrated = 1;
}

void showDebug() {
    for (int i = 0; i < NUM_SENSORS; i++) {
      Serial.print(Qtrrc.calibratedMinimumOn[i]);
      Serial.print(' ');
    }
    Serial.println();

    for (int i = 0; i < NUM_SENSORS; i++) {
      Serial.print(Qtrrc.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
    Serial.println();
    Serial.println();
}
