
#include "LedControl.h"
#include <SparkFunDS1307RTC.h>
#include <Wire.h>


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

    rtc.begin();
    rtc.update();
    rtc.autoTime();
    rtc.update();

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
    rtc.update();

    Serial.print("Time: ");
    Serial.print(rtc.dayStr());
    Serial.print(" " + String(rtc.month()) + "/");   // Print month
    Serial.print(String(rtc.date()) + "/");
    Serial.print(String(rtc.year()) + " ");
    Serial.print(String(rtc.hour()) + ":");
    Serial.print(String(rtc.minute()) + ":");
    Serial.println(String(rtc.second()));
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
    lc.setIntensity(0,intensity--);
    Serial.println(String(intensity));
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    lc.clearDisplay(0);
    delay(1000);

}


// /*
//  This method will display the characters for the
//  word "Arduino" one after the other on digit 0.
//  */
// void writeArduinoOn7Segment() {
//   lc.setChar(0,0,'a',false);
//   delay(delaytime);
//   lc.setRow(0,0,0x05);
//   delay(delaytime);
//   lc.setChar(0,0,'d',false);
//   delay(delaytime);
//   lc.setRow(0,0,0x1c);
//   delay(delaytime);
//   lc.setRow(0,0,B00010000);
//   delay(delaytime);
//   lc.setRow(0,0,0x15);
//   delay(delaytime);
//   lc.setRow(0,0,0x1D);
//   delay(delaytime);
//   lc.clearDisplay(0);
//   delay(delaytime);
// }

// /*
//   This method will scroll all the hexa-decimal
//  numbers and letters on the display. You will need at least
//  four 7-Segment digits. otherwise it won't really look that good.
//  */
// void scrollDigits() {
//   for(int i=0;i<13;i++) {
//     lc.setDigit(0,3,i,false);
//     lc.setDigit(0,2,i+1,false);
//     lc.setDigit(0,1,i+2,false);
//     lc.setDigit(0,0,i+3,false);
//     delay(delaytime);
//   }
//   lc.clearDisplay(0);
//   delay(delaytime);
// }
