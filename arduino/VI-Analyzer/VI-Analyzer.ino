#include "config.h"
#include "globals.h"
#include "aquire.h"
#include "TimerOne.h"
#include "oled.h"


void oneSecCallback(void);

void setup() {
    // dummy section
    flags.SD = 1;
    flags.splashScreen = 1;
    globals.sdUsage = 12;
    flags.activeLoad =1;
    globals.loadVoltage = 3.7;
    clock.hour = 12;
    clock.minute = 17;
    clock.second = 30;
    globals.battery = 73;
    globals.current = 0.3;

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
    flags.splashScreen=0;
}
