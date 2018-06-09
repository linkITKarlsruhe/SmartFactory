#include <Arduino.h>
#include "FTSlib.h"
#include <EEPROM.h> // lib for memory for saving calibration
#include <QTRSensors.h>

int pinarray[5] = {4, 5, 6, 7, 2};
FTSlib LinkItFts(pinarray);

void setup()
{

  LinkItFts.calibrate();
}

void loop()
{
  LinkItFts.stopAtLongBlackBar();
  LinkItFts.accelerateAtBlackBarRight();
  LinkItFts.decelerateAtBlackBarLeft();

  LinkItFts.checkButtonpress();
  LinkItFts.updateDirection();
  LinkItFts.isStopped();
}