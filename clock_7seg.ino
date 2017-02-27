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

uint8_t hour_high = 0;
uint8_t hour_low = 0;
uint8_t minute_high = 0;
uint8_t minute_low = 0;
uint8_t second_high = 0;
uint8_t second_low = 0;

void setup() {
    Serial.begin(9600);

    setSyncProvider(RTC.get);
    setSyncInterval(3600); // sync every hour, hopefully before clock gets 1s off

    lc.setScanLimit(0,3); //only display on first 4 digits, to get higher brightness
    lc.shutdown(0,false); //start the max7219
    lc.setIntensity(0,15);
    lc.clearDisplay(0);
}

void loop() {
//     lc.setLed(0, 4, 0, 1); //DP4
//     lc.setLed(0, 0, 4, 1); //D0
//     delay(1000);
//     lc.setLed(0, 4, 0, 0); //DP4
//     lc.setLed(0, 0, 4, 0); //D0
    digitalClockDisplay();
    delay(1000);
}

void digitalClockDisplay(){
    uint8_t cur_hour = hour();


    if (cur_hour > 12){ cur_hour -= 12; } //12 hour mode
    if (cur_hour == 0){ cur_hour = 12; } //midnight fix

    hour_high = cur_hour / 10;
    hour_low = cur_hour % 10;

    minute_high = minute() / 10;
    minute_low = minute() % 10;

    second_high = second() / 10;
    second_low = second() % 10;


    lc.setDigit(0, 0, hour_high, false);
    if (hour_high == 0) {
        lc.setChar(0, 0, ' ', false); //clear first digit
    }
    lc.setDigit(0, 1, hour_low, false);
    lc.setDigit(0, 2, minute_high, false);
    lc.setDigit(0, 3, minute_low, false);
    // lc.setDigit(0, 4, second_high, false);
    // lc.setDigit(0, 5, second_low, false);


    //setDigit(chip, digit_position, number, dot);
    // lc.setDigit(0,,i,false);
    Serial.print(hour_high);
    Serial.print(hour_low);
    Serial.print(":");
    Serial.print(minute_high);
    Serial.print(minute_low);
    Serial.print(":");
    Serial.print(second_high);
    Serial.println(second_low);
}
