#include <FTSlib.h>
#include <Arduino.h>
#include <EEPROM.h> // lib for memory for saving calibration
#include <QTRSensors.h>
#include <HC_SR04.h>

#define TIN1 4
#define TIN2 5

int pinarray[5] = {4, 5, 6, 7, 2};
FTSlib LinkItFts(pinarray);

int TRIG_PIN = 21; // Arduino Pin an HC-SR04 Trig
int ECHO_PIN = 20; // Arduino Pin an HC-SR04 Echo
int ECHO_INT = 0;

HC_SR04 sensor(TRIG_PIN, ECHO_PIN, ECHO_INT);
// SoftwareSerial linkITUltraSonic(10, 11); //Using pins 11,12

void setup()
{
  sensor.begin();
  Serial.begin(9600);
  while (!Serial)
    continue;
  sensor.start();
  LinkItFts.calibrate();
}

void loop()
{
  Serial.println(LinkItFts.fts_button_break);
  if (sensor.isFinished())
  {
    Serial.println("Red");
    if (sensor.getRange() < 10)
    {
      LinkItFts.fts_button_break = false;
    }
    else
    {
      LinkItFts.fts_button_break = true;
    }

    sensor.start();
  }
  // LinkItFts.setMotors(300, 300);
  LinkItFts.stopAtLongBlackBar();
  LinkItFts.accelerateAtBlackBarRight();
  LinkItFts.decelerateAtBlackBarLeft();
  // LinkItFts.checkButtonpress();
  LinkItFts.updateDirection();

  // LinkItFts.entfernungGD();
  // LinkItFts.isStopped();
}
