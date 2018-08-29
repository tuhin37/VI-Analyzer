void checkSwitches() {
    flags.hiRes = digitalRead(HI_RES_PIN);
    flags.load = !(digitalRead(LOAD_PIN));
    flags.charge = digitalRead(CHARGE_PIN);
 }

 void aquireParams() {
    // get source voltage
    uint16_t sourceVoltRaw;
   
    sourceVoltRaw = analogRead(SRC_VOLT_PIN);
    if(sourceVoltRaw == 0) {
        globals.sourceVolt = 0;
    }
    else {
        globals.sourceVolt = (sourceVoltRaw * 0.03007) + 0.0691;
    }
    //get load impedance
    globals.loadimpedance = globals.sourceVolt/globals.current;
    
    //dummy
    globals.loadimpedance = 30;
    globals.current = 1.223;
    globals.watt = 167.345;
 }
