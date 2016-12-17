
#include "LedControl.h"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>


/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 2 is connected to the DataIn
 pin 4 is connected to the CLK
 pin 3 is connected to LOAD
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(2,4,3,1);

// unsigned long delaytime=250;
int intensity = 15;

void setup() {
    Serial.begin(9600);

    setSyncProvider(RTC.get);
    setSyncInterval(3600); // sync every hour, hopefully before clock gets 1s off

    /*
     The MAX72XX is in power-saving mode on startup,
     we have to do a wakeup call
     */
    lc.shutdown(0,false);
    lc.setIntensity(0,15);
    lc.clearDisplay(0);
    pinMode(13, OUTPUT);
}

void loop() {
    digitalClockDisplay();

    //setDigit(chip, digit_position, number, dot);
    // lc.setDigit(0,,i,false);
    if (intensity == 0){
        intensity = 15;
    }


    //setLed(chip, row, column, state);
    lc.setLed(0, 4, 0, 1); //DP4
    lc.setLed(0, 0, 4, 0); //D0
    lc.setIntensity(0,15);
    digitalWrite(13, LOW);
    delay(1000);
    lc.setLed(0, 4, 0, 0); //DP4
    lc.setLed(0, 0, 4, 1); //D0
    lc.setIntensity(0,8);
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    lc.clearDisplay(0);
    delay(1000);

}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
