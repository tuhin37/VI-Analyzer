#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "kalman.h"

Adafruit_ADS1115 ads(0x48);
kalman acsADCFilter;

#include "config.h"
#include "globals.h"
#include "aquire.h"
#include "TimerOne.h"
#include "oled.h"





void oneSecCallback(void);

void setup() {
    acsADCFilter.setAccuracy(0.1);
    //Serial.begin(9600);
    // dummy section
    flags.splashScreen = 1;
    // flags.SD=1;
    globals.sdUsage = 12;
    globals.battery = 73;
    globals.loadResistance=1000000;

    initOLED();

    // one second interrupt callback
    Timer1.initialize(1000000);         // initialize timer1, and set a 1/2 second period
    Timer1.attachInterrupt(oneSecCallback);  // attaches callback() as a timer overflow interrupt
    analogReference(EXTERNAL);
}

void loop() {
    checkSwitches();
    aquireParams();
    
    updateDisplay();
}



void oneSecCallback() {

    //Serial.println(globals.current);
    flags.splashScreen=0;
    if(flags.tickTock) {
        flags.tickTock=0;
    }
    else {
        flags.tickTock=1;
    }

    // start clock id load switch is pressed
    if(flags.load) {
        clock.second++;
        
        if(clock.second==60) {
            clock.second=0;
            clock.minute++;
        }

        if(clock.minute==60) {
            clock.hour++;
            clock.minute=0;
        }
    }
}
