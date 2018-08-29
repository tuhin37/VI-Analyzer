
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
        
        // HI-RES ICON
        if(flags.hiRes) {
            u8g.drawStr(46, 10, "HD");
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


        // clock at down-left 
        u8g.setPrintPos(0, 64);
        u8g.print(clock.hour);
        u8g.drawStr(14, 64, ":");
        u8g.setPrintPos(22, 64);
        u8g.print(clock.minute);
        u8g.drawStr(35, 64, ":");
        u8g.setPrintPos(43, 64);
        u8g.print(clock.second);

    

        // Body of the display
        // if the load switch is off
        if(!flags.load) {
            u8g.setFont(u8g_font_helvB12);
            // show source voltage
            if(globals.sourceVolt>0 && globals.sourceVolt <10) {
                u8g.setPrintPos(0, 35);
                u8g.print(globals.sourceVolt);
                u8g.drawStr(33, 35, "V"); 
            }
            else if(globals.sourceVolt>=10) {
                u8g.setPrintPos(0, 35);
                u8g.print(globals.sourceVolt);
                u8g.drawStr(42, 35, "V");
            }
            else if(globals.sourceVolt<=0.2) {
                u8g.drawStr(0, 35, "N/A");
            }

            // if load is of active type then show load voltage

            if(flags.activeLoad) {
                u8g.setPrintPos(85, 35);
                u8g.print(globals.loadVoltage);
                u8g.drawStr(117, 35, "V"); 
            }

        }
        // if load switch is pressed
        else{
            u8g.setFont(u8g_font_helvR08);
            
            // show source voltage
            if(globals.sourceVolt>0 && globals.sourceVolt <10) {
                u8g.setPrintPos(0, 35);
                u8g.print(globals.sourceVolt);
                u8g.drawStr(23, 35, "V"); 
            }
            else if(globals.sourceVolt>=10) {
                u8g.setPrintPos(0, 35);
                u8g.print(globals.sourceVolt);
                u8g.drawStr(30, 35, "V");
            }
            else if(globals.sourceVolt<=0.2) {
                u8g.drawStr(0, 35, "N/A");
            }

            // show load Impedance
            if(globals.loadimpedance <100) {   // if current is non zero
                u8g.setPrintPos(110, 35);
                u8g.print(globals.loadimpedance);
                u8g.drawStr(123, 35, "E");   
            }
            else if(globals.loadimpedance>=100 && globals.loadimpedance <1000) {
                u8g.setPrintPos(104, 35);
                u8g.print(globals.loadimpedance);
                u8g.drawStr(123, 35, "E");
            }
            else if(globals.loadimpedance>=1000) {
                u8g.setPrintPos(104, 35);
                float impedance = globals.loadimpedance/1000.0;
                if(globals.loadimpedance%1000){
                    u8g.print(impedance, 1);
                }
                else {
                    u8g.print(impedance, 0);
                }
                u8g.drawStr(122, 35, "K");
            }

            // show watt
            uint16_t mW;
            mW = globals.watt*1000;
            if(globals.watt >=1) {
                u8g.drawStr(119, 50, "W");
                u8g.setPrintPos(96, 50);
                if(globals.watt <10) {
                    u8g.print(globals.watt, 2);
                }
                else if(globals.watt>=10 && globals.watt < 100){
                    u8g.print(globals.watt, 1);
                }
                else {
                    u8g.setPrintPos(99, 50);
                    u8g.print(globals.watt, 0);
                }
            }
            else {
                u8g.drawStr(111, 50, "mW");
                if(mW<10){
                    u8g.setPrintPos(103, 50);
                    u8g.print(mW);
                }
                if(mW>=10 && mW<100){
                    u8g.setPrintPos(95, 50);
                    u8g.print(mW);
                }
                else {
                    u8g.setPrintPos(89, 50);
                    u8g.print(mW);
                    
                }
            }


            // show load current
            u8g.setFont(u8g_font_helvB12);
            uint16_t mA;
            mA = globals.current*1000;

            if(globals.current >= 1) {
                u8g.setPrintPos(38, 35);
                u8g.print(globals.current, 2);
                u8g.drawStr(74, 35, "A");
            }
            else {
                if(mA<10) {
                    u8g.setPrintPos(45, 35);
                    u8g.print(mA, 0);
                    u8g.drawStr(57, 35, "mA");
                }
                else if(mA >=10 && mA < 100) {
                    u8g.setPrintPos(40, 35);
                    u8g.print(mA, 0);
                    u8g.drawStr(62, 35, "mA");
                }
                else {
                    u8g.setPrintPos(37, 35);
                    u8g.print(mA, 0);
                    u8g.drawStr(71, 35, "mA");
                }
            }

            
        }

        // u8g.setPrintPos(30, 50);
        // u8g.print(globals.loadResistance);

            
    } 
    while( u8g.nextPage() );
}
