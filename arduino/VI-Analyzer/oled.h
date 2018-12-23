
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST); // Fast I2C / TWI 



void initOLED() {
    // flip screen, if required
    u8g.setRot180();

    // set SPI backup if required
    //u8g.setHardwareBackup(u8g_backup_avr_spi);

    // assign default color value
    if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
        u8g.setColorIndex(255);     // white
    }
    else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
        u8g.setColorIndex(3);         // max intensity
    }
    else if ( u8g.getMode() == U8G_MODE_BW ) {
        u8g.setColorIndex(1);         // pixel on
    }
    else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
        u8g.setHiColorByRGB(255,255,255);
    }
}


void updateDisplay() {
    uint8_t Ypos = 0;
    uint8_t Xpos = 0;
    u8g.firstPage();
    do {
        
        // splash screen
        if(flags.splashScreen) {
            u8g.setFont(u8g_font_courB18);
            u8g.drawStr(13, 28, "VI");
            u8g.drawStr(5, 48, "Analyzer");
            continue;
        }
        
        // ************* Menu bar *************
        u8g.setFont(u8g_font_6x10);
        //SD CARD ICON
        if(flags.SD) {
            u8g.drawStr(0, 10, "SD");
            u8g.drawStr(33, 10, "%");
            u8g.setPrintPos(20, 10);
            u8g.print(globals.sdUsage );
        }
        else {
            u8g.drawStr(0, 10, "NO-SD");
        }
        
        // HI-RES ICON
        if(flags.hiRes) {
            if(flags.overDrop) {
                if(flags.tickTock) {
                    u8g.drawStr(46, 10, "HD");
                }
                else {
                    u8g.drawStr(46, 10, "HD");
                }

            }
            else {
                u8g.drawStr(46, 10, "HD");
            }
        }
        
        // LOAD ICON
        if(flags.load) {
            u8g.drawStr(66, 10, "LD");
        }

        // CHARGE ICON
        if(flags.charge) {
            u8g.drawStr(85, 10, "CH");
        }

        // BATTERY CHARGE
        u8g.drawStr(120, 10, "%");
        u8g.setPrintPos(105, 10);
        u8g.print(globals.battery);

    

        // Body of the display
        // if the load switch is off
        if(!flags.load) {

            // show source voltage 
            Ypos = 41   ;
            u8g.setFont(u8g_font_helvB12);
            // show source voltage
            if(globals.sourceVolt>=0.1 && globals.sourceVolt <10) {
                u8g.setPrintPos(0, Ypos);
                u8g.print(globals.sourceVolt);
                u8g.drawStr(33, Ypos, "V"); 
            }
            else if(globals.sourceVolt>=10) {
                u8g.setPrintPos(0, Ypos);
                u8g.print(globals.sourceVolt);
                u8g.drawStr(42, Ypos, "V");
            }
            else if(globals.sourceVolt<0.1) {
                u8g.drawStr(0, Ypos, "N/A");
            }



            // if load is of active type then show load voltage
            if(flags.activeLoad) {
                if(globals.loadVoltage<10) {
                    u8g.setPrintPos(85, Ypos);
                    u8g.print(globals.loadVoltage);
                }
                else {
                    u8g.setPrintPos(75, Ypos);
                    u8g.print(globals.loadVoltage);
                }
                u8g.drawStr(117, Ypos, "V"); 
            }
            // else show load resistance
            else {
                if(!globals.loadResistance) {
                    u8g.drawStr(70, Ypos, "SHORT");
                }
                else if(globals.loadResistance>0 &&globals.loadResistance<10) {
                    u8g.setPrintPos(107, Ypos);
                    u8g.print(globals.loadResistance);
                    u8g.drawStr(117, Ypos, "E");
                }
                else if(globals.loadResistance >=10 && globals.loadResistance<100) {
                    u8g.setPrintPos(97, Ypos);
                    u8g.print(globals.loadResistance);
                    u8g.drawStr(117, Ypos, "E");
                }
                else if(globals.loadResistance>=100 && globals.loadResistance<1000) {
                    u8g.setPrintPos(87, Ypos);
                    u8g.print(globals.loadResistance);
                    u8g.drawStr(117, Ypos, "E");
                }
                else if(globals.loadResistance >=1000 && globals.loadResistance<10000){
                    u8g.setPrintPos(85, Ypos);
                    u8g.print(globals.loadResistance/1000.0, 2);
                    u8g.drawStr(117, Ypos, "K");
                }
                else if(globals.loadResistance>= 10000 && globals.loadResistance<100000) {
                    u8g.setPrintPos(85, Ypos);
                    u8g.print(globals.loadResistance/1000.0, 1);
                    u8g.drawStr(117, Ypos, "K");
                }
                else if(globals.loadResistance>=100000 && globals.loadResistance<1000000) {
                    u8g.setPrintPos(87, Ypos);
                    u8g.print(globals.loadResistance/1000.0, 0);
                    u8g.drawStr(117, Ypos, "K");   
                }
                else if(globals.loadResistance>=1000000) {
                    u8g.drawStr(80, Ypos, "OPEN");  
                }
                
                
            }


            // show mWh data
            Ypos = 64;
            Xpos = 0;
            if(!globals.mWh);
            else if(globals.mWh<10) {
                u8g.setPrintPos(Xpos+0, Ypos);
                u8g.print(globals.mWh);
                u8g.drawStr(Xpos+12, Ypos, "mWh");
            }
            else if(globals.mWh>=10 && globals.mWh<100) {
                u8g.setPrintPos(Xpos+0, Ypos);
                u8g.print(globals.mWh);
                u8g.drawStr(Xpos+23, Ypos, "mWh");
            }
            else if(globals.mWh>=100 && globals.mWh<1000) {
                u8g.setPrintPos(Xpos+0, Ypos);
                u8g.print(globals.mWh);
                u8g.drawStr(Xpos+32, Ypos, "mWh");
            }
            else if(globals.mWh>=1000 && globals.mWh<10000) {
                u8g.setPrintPos(Xpos+0, Ypos);
                u8g.print(globals.mWh);
                u8g.drawStr(Xpos+43, Ypos, "mWh");
            }
            else {
                float Wh = 0;
                Wh = globals.mWh/1000.0;
                u8g.setPrintPos(Xpos+0, Ypos);
                if(globals.mWh>=10000 && globals.mWh<100000) {
                    u8g.print(Wh,2);
                    u8g.drawStr(Xpos+43, Ypos, "Wh");    
                }
                else if(globals.mWh>=100000 && globals.mWh<1000000) {
                    u8g.print(Wh,1);
                    u8g.drawStr(Xpos+43, Ypos, "Wh");
                }
                else {    
                    u8g.setPrintPos(Xpos+0, Ypos);
                    u8g.print(Wh,0);
                    u8g.drawStr(Xpos+39, Ypos, "Wh");
                }
                
            }

        }
        // if load switch is pressed
        else{
            // clock at down-left 
            u8g.setPrintPos(0, 64);
            u8g.print(clock.hour);
            u8g.drawStr(14, 64, ":");
            u8g.setPrintPos(22, 64);
            u8g.print(clock.minute);
            u8g.drawStr(35, 64, ":");
            u8g.setPrintPos(43, 64);
            u8g.print(clock.second);

            
            // show source voltage
            u8g.setFont(u8g_font_helvR08);            
            Ypos = 38;
            if(globals.sourceVolt>=0.1 && globals.sourceVolt <10) {
                u8g.setPrintPos(0, Ypos);
                u8g.print(globals.sourceVolt);
                u8g.drawStr(23, Ypos, "V"); 
            }
            else if(globals.sourceVolt>=10) {
                u8g.setPrintPos(0, Ypos);
                u8g.print(globals.sourceVolt);
                u8g.drawStr(28, Ypos, "V");
            }
            else if(globals.sourceVolt<0.1) {
                u8g.drawStr(0, Ypos, "N/A");
            }

            // show load Impedance
            if(flags.log) {
                 Ypos = 30;
            }
            else {
                Ypos = 37;
            }

            if(globals.loadimpedance == 0 && globals.current>1) {
                u8g.drawStr(92, Ypos, "SHORT");
            }
            else if(globals.loadimpedance>0 && globals.loadimpedance <10) {
                u8g.setPrintPos(116, Ypos);
                u8g.print(globals.loadimpedance);
                u8g.drawStr(123, Ypos, "E");   
            }
            else if(globals.loadimpedance>=10 && globals.loadimpedance <100) {   // if current is non zero
                u8g.setPrintPos(110, Ypos);
                u8g.print(globals.loadimpedance);
                u8g.drawStr(123, Ypos, "E");   
            }
            else if(globals.loadimpedance>=100 && globals.loadimpedance <1000) {
                u8g.setPrintPos(104, Ypos);
                u8g.print(globals.loadimpedance);
                u8g.drawStr(123, Ypos, "E");
            }
            else if(globals.loadimpedance>=1000 && globals.loadimpedance<10000) {
                u8g.setPrintPos(99, Ypos);
                u8g.print(globals.loadimpedance/1000.0, 2);
                u8g.drawStr(122, Ypos, "K");
            }
            else if(globals.loadimpedance>=10000 && globals.loadimpedance<100000) {
                u8g.setPrintPos(99, Ypos);
                u8g.print(globals.loadimpedance/1000.0, 1);
                u8g.drawStr(122, Ypos, "K");
            }
            else if(globals.loadimpedance>=100000 && globals.loadimpedance<1000000) {
                u8g.setPrintPos(102, Ypos);
                u8g.print(globals.loadimpedance/1000.0, 0);
                u8g.drawStr(122, Ypos, "K");
            }   
            else if(globals.loadimpedance>=1000000) {
                u8g.drawStr(98, Ypos, "OPEN");
            }
            

            // show watt
            uint16_t mW;
            Ypos += 15;
            mW = globals.watt*1000;
            if(globals.watt >=1) {
                u8g.drawStr(119, Ypos, "W");
                u8g.setPrintPos(96, Ypos);
                if(globals.watt <10) {
                    u8g.print(globals.watt, 2);
                }
                else if(globals.watt>=10 && globals.watt < 100){
                    u8g.print(globals.watt, 1);
                }
                else {
                    u8g.setPrintPos(99, Ypos);
                    u8g.print(globals.watt, 0);
                }
            }
            else {
                if(!globals.watt);
                else if(mW<10){
                    u8g.setPrintPos(103, Ypos);
                    u8g.print(mW);
                    u8g.drawStr(111, Ypos, "mW");
                }
                else if(mW>=10 && mW<100){
                    u8g.setPrintPos(95, Ypos);
                    u8g.print(mW);
                    u8g.drawStr(111, Ypos, "mW");
                }
                else {
                    u8g.setPrintPos(89, Ypos);
                    u8g.print(mW);
                    u8g.drawStr(111, Ypos, "mW");
                }
            }

            // show miliWatt-hour 
            if(flags.log) {
                Ypos = 48;    
            }
            else {
                Ypos = 51; 
            }
            if(!globals.mWh);
            else if(globals.mWh>0 && globals.mWh<10) {
                u8g.setPrintPos(50, Ypos);
                u8g.print(globals.mWh);
                u8g.drawStr(58, Ypos, "mWh");
            }
            else if(globals.mWh>=10 && globals.mWh<100) {
                u8g.setPrintPos(46, Ypos);
                u8g.print(globals.mWh);
                u8g.drawStr(62, Ypos, "mWh");
            }
            else if(globals.mWh>=100 && globals.mWh<1000) {
                u8g.setPrintPos(40, Ypos);
                u8g.print(globals.mWh);
                u8g.drawStr(62, Ypos, "mWh");
            }
            else if(globals.mWh>=1000 && globals.mWh<10000) {
                u8g.setPrintPos(37, Ypos);
                u8g.print(globals.mWh);
                u8g.drawStr(66, Ypos, "mWh");
            }
            else {
                float Wh = 0;
                Wh = globals.mWh/1000.0;
                u8g.setPrintPos(40, Ypos);
                if(globals.mWh>=10000 && globals.mWh<100000)
                    u8g.print(Wh,2);
                else if(globals.mWh>=100000 && globals.mWh<1000000)
                    u8g.print(Wh,1);
                else {    
                    u8g.setPrintPos(44, Ypos);
                    u8g.print(Wh,0);
                }
                u8g.drawStr(70, Ypos, "Wh");
            }



            // show load current
            if(flags.log) {
                Ypos = 32;
            }
            else {
                Ypos = 35;
            }
            
            u8g.setFont(u8g_font_helvB12);
            uint16_t mA;
            mA = globals.current*1000;

            if(globals.current >= 1) {
                u8g.setPrintPos(41, Ypos);
                u8g.print(globals.current, 2);
                u8g.drawStr(75, Ypos, "A");
            }
            else {
                if(mA<10) {
                    u8g.setPrintPos(45, Ypos);
                    u8g.print(mA);
                    u8g.drawStr(57, Ypos, "mA");
                }
                else if(mA >=10 && mA < 100) {
                    u8g.setPrintPos(44, Ypos);
                    u8g.print(mA);
                    u8g.drawStr(65, Ypos, "mA");
                }
                else {
                    u8g.setFont(u8g_font_courB10);
                    u8g.setPrintPos(42, Ypos);
                    u8g.print(mA);
                    u8g.drawStr(71, Ypos, "mA");
                }
            }

            // dummy 
            if(flags.log) {
                u8g.setFont(u8g_font_helvR08);
                u8g.drawStr(80, 64, "Bla bla bla");
            }



            
        }

            
    } 
    while( u8g.nextPage() );
}
