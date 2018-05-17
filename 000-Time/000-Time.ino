/*
 * This Arduino sketch displays 24-hour time (Military time) and Desamber time.
 * It includes buttons to set the time. One button adds an hour, the other adds a minute.
 * Desamber is a time format created by Devine Lu Linvega. More information about Desamber here: https://wiki.xxiivv.com/#clock
 */

#include "Ardusamber.h"
#include "MilitaryTime.h"

#include "RBD_Button.h"
#include "LiquidCrystal_I2C.h"
#include "TimeLib.h"

Ardusamber _dTime = Ardusamber();
MilitaryTime _mTime = MilitaryTime();

RBD::Button buttonHour(7);
RBD::Button buttonMinute(6);

LiquidCrystal_I2C _lcd(0x20,16,2); // Set the LCD address to 0x20 for a 16 chars and 2 line display

void setup()
{
  _lcd.init();
  _lcd.backlight();
  _lcd.home();
  _lcd.clear();
}

void loop()
{
  if(buttonHour.isPressed()) 
  {
    adjustTime(3600);
  }
  if(buttonMinute.isPressed()) 
  {
    adjustTime(60);
  }

  writeToScreen(_dTime.getFormattedTime(), 5, 1);
  writeToScreen(_mTime.getFormattedTime(), 4, 0);
  
  delay(86); // '...the shortest pulse equals to 8.64 milliseconds...'
}

void writeToScreen(String value, int posX, int posY)
{
  _lcd.setCursor(posX, posY);
  _lcd.print(value);
}