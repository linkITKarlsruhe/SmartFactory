#include <FTSlib.h>
#include <Arduino.h>
#include <EEPROM.h> // lib for memory for saving calibration
#include <QTRSensors.h>

#define TIN1 4

int pinarray[5] = {4, 5, 6, 7, 2};
FTSlib LinkItFts(pinarray);

void setup()
{
  Serial.begin(1000);

  // LinkItFts.calibrate();
}

void loop()
{
  LinkItFts.setMotors(300, 300);
   digitalWrite(TIN1, LOW);
    digitalWrite(TIN2, HIGH);
  // LinkItFts.stopAtLongBlackBar();
  // LinkItFts.accelerateAtBlackBarRight();
  // LinkItFts.decelerateAtBlackBarLeft();

  // LinkItFts.checkButtonpress();
  // LinkItFts.updateDirection();
  // LinkItFts.isStopped();
}
