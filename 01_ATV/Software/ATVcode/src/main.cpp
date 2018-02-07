/*TODOS
- eeprom save of calibrated values. should be triggered with a button press
during the first 5 secs of startup. if button is not pressed,
last calibration values are loaded
- code refactoring
*/

#include <Arduino.h>
#include <QTRSensors.h>


//Function declarations
void autoCalibration();
void set_motors(int motorspeed_l, int motorspeed_r);
void manualCalibration(const int *manual_calibration_values);
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
#define NUM_SENSORS 8               // number of reflectance sensors used
#define TIMEOUT 2500                // waits for 2500 us for sensor outputs to go low
//#define EMITTER_PIN 2             // emitterPin is the Arduino digital pin that controls whether the IR LEDs are on or off. Emitter is controlled by digital pin 2
#define DEBUG 0
QTRSensorsRC Qtrrc((unsigned char[]){A7,A6,A5,A4,A3,A2,A1,A0}, NUM_SENSORS, TIMEOUT);   // instanciate object of class QTRSensorsRC
// ----------------------- PID Control ---------------------------------------------------------- //
#define KP 1
#define KD 5
const int LAST_CALIBRATION[] = {708, 864, 812, 836, 784};

// ----------------------- DO NOT CHANGE -------------------------------------------------------- //
int last_error = 0;
int position = 0;
int error = 0;
int motorSpeed = 0;
int motorspeed_l;
int motorspeed_r;
unsigned int sensors[8];


void setup() {
  Serial.begin(115200);
  // showDebug();
  // delay(2000);
  autoCalibration();
  // showDebug();
  // delay(2000);
  // Serial.println("AutoCalibration Done.");
  // Serial.println("Loading values from manual calibration before ...");
  // manualCalibration(manual_calibration);
  // showDebug();
}


void loop() {
  position = Qtrrc.readLine(sensors); // wert von 0 bis 1000*(NUM_SENSORS-1)
  Serial.println(error);
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
    motorspeed_l = map(motorspeed_l,-7000,-1000,0,MAX_BRAKE);
    // Serial.print(" / converted:"); Serial.println(motorspeed_l);
    // Serial.print("Brake L: "); Serial.println(motorspeed_l);
  } else {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }

  if (motorspeed_r < -1000) {
    motorspeed_r = map(motorspeed_r,-7000,-1000,0,MAX_BRAKE);
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

void autoCalibration() {
  int i;
  for (i = 0; i < 125; i++) {
    Qtrrc.calibrate(QTR_EMITTERS_ON);
    delay(20);
  }
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
