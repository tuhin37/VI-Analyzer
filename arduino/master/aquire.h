void checkSwitches() {
    flags.hiRes = digitalRead(HI_RES_PIN);
    flags.load = !(digitalRead(LOAD_PIN));
    flags.charge = digitalRead(CHARGE_PIN);
 }

 void aquireParams() {

    uint16_t adcRaw;
    float filteredData;


    // get source voltage from ADS1115
    //adcRaw = ads.readADC_SingleEnded(ADS_SRC_VOLT_PIN);
    // get source voltage from ADC
    //adcRaw = analogRead(SRC_VOLT_PIN);
    //Serial.println(analogRead(SRC_VOLT_PIN));

    // if(adcRaw<41) {
    //     globals.sourceVolt=0;
    // }
    // else if(adcRaw>=41 && adcRaw<=1468) {
    //     globals.sourceVolt =  0.003499*adcRaw - 0.1361;
    // }
    // else if(adcRaw>1468 && adcRaw<=2892) {
    //     globals.sourceVolt =  0.003513*adcRaw - 0.1578;
    // }
    // else {
    //     globals.sourceVolt =  0.003568*adcRaw - 0.3469;
    // }

    
    if(Serial.available()) {
        globals.sourceVolt = Serial.parseFloat();
        Serial.println(globals.sourceVolt,4);
        Serial.flush();
    }

    // // get acs out RAW
    // adcRaw = ads.readADC_SingleEnded(ADS_ACS_PIN);
    // globals.current = 0.9816*adcRaw-13350;
    // // Serial.print("ACS Raw: ");
    // // Serial.print(adcRaw);
    // // Serial.print("  mA: ");
    // // Serial.println(globals.current);


    //get acs amped
    if(globals.current<1000) {
        adcRaw = ads.readADC_SingleEnded(ADS_AMPED_ACS_PIN);
        globals.current = 0.1379*adcRaw-599.9;
    }
   

    //  get HI-RES AMPED
    //adcRaw =analogRead(HD_CURR_PIN);
    //filteredData = acsADCFilter.output(adcRaw);
    // globals.current = 0.1379*filteredData-599.9;
    //Serial.print("Hi-res raw: ");
    //Serial.println(adcRaw);
    // Serial.print("  H-res filtered: ");
    // Serial.println(filteredData);
    // // Serial.print("  mA: ");
    // Serial.println(globals.current);


    // // get load current
    // adcRaw = ads.readADC_SingleEnded(ADS_HD_CURR_PIN);
    // filteredData=acsADCFilter.output(adcRaw);
    // if(filteredData>= 10) 
    //     globals.current = filteredData*0.000006073 + .001458;
    // else 
    //     globals.current = 0;

    // // calculate power (in watt)
    // globals.watt = globals.current * globals.sourceVolt;


    
    //get load impedance
    globals.loadimpedance = (globals.sourceVolt*1000)/globals.current;
    
    // //get load Resistance when load is off
    // digitalWrite(PULL_UP, HIGH);
    // delay(500);
    // adcRaw = analogRead(LOAD_VOLT_PIN);
    // Serial.println(adcRaw);
    // //globals.loadResistance=

    
    
    //get mw
    globals.watt =globals.sourceVolt*globals.current/1000;

    // if(globals.current == 0) {
    //     globals.loadimpedance = 1000000;
    // }


    //dummy
    //globals.loadimpedance = 4787988;
    //globals.current = 1.146;
    // globals.watt = 0.016;
    //globals.fileSize = 443;
    //flags.log=0;
    //globals.mWh = 0;
    //flags.overDrop = 1;

 }
