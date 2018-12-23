void checkSwitches() {
    flags.hiRes = digitalRead(HI_RES_PIN);
    flags.load = !(digitalRead(LOAD_PIN));
    flags.charge = digitalRead(CHARGE_PIN);
 }

 void aquireParams() {
    // get source voltage
    uint16_t sourceVoltRaw;
    uint16_t adcRaw;
    float filteredData;

    // get source voltage
    adcRaw = ads.readADC_SingleEnded(ADS_SRC_VOLT_PIN);
    
    if(adcRaw<41) {
        globals.sourceVolt=0;
    }
    else if(adcRaw>=41 && adcRaw<=1468) {
        globals.sourceVolt =  0.003499*adcRaw - 0.1361;
    }
    else if(adcRaw>adcRaw && adcRaw<=2892) {
        globals.sourceVolt =  0.003513*adcRaw - 0.1578;
    }
    else {
        globals.sourceVolt =  0.003568*adcRaw - 0.3469;
    }



    Serial.print("Voltage: ");
    Serial.println(globals.sourceVolt);
    

    //Serial.print("RAW Volt: ");
    //Serial.println(sourceVoltRaw);

    

    // get load current
    adcRaw = ads.readADC_SingleEnded(ADS_HD_CURR_PIN);
    filteredData=acsADCFilter.output(adcRaw);
    if(filteredData>= 10) 
        globals.current = filteredData*0.000006073 + .001458;
    else 
        globals.current = 0;

    // calculate power (in watt)
    globals.watt = globals.current * globals.sourceVolt;


    
    //get load impedance
    globals.loadimpedance = globals.sourceVolt/globals.current;
    

    if(globals.current == 0) {
        globals.loadimpedance = 1000000;
    }


    //dummy
    //globals.loadimpedance = 4787988;
    //globals.current = 1.146;
    // globals.watt = 0.016;
    //globals.fileSize = 443;
    //flags.log=0;
    //globals.mWh = 0;
    //flags.overDrop = 1;

 }
