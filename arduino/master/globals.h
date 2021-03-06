
struct global{
    uint8_t sdUsage;
    uint8_t battery;
    float sourceVolt;
    float loadVoltage;
    uint32_t loadResistance;   // this is calculated when load is off. Using a voltage divider
    uint32_t loadimpedance;    // this is calculated during discharge. Impedance = v/I
    float current;
    float watt;
    uint32_t fileSize;
    float mWh;
} globals;

struct flag {
    uint8_t hiRes: 1;
    uint8_t load: 1;
    uint8_t charge: 1;
    uint8_t splashScreen: 1;
    uint8_t SD: 1;
    uint8_t activeLoad: 1;
    uint8_t log: 1;
    uint8_t tickTock: 1;
    uint8_t overDrop: 1;
} flags;

struct text {
    char* e = "E";
    char* k = "K";
    char* sd = "SD";
    char* hd = "HD";
    char* v = "V";
    char* mWh = "mWh";
    char* Wh = "Wh";
    char* na = "N/A";
    char* shrt = "SHORT";
    char* opn = "OPEN";
    char* wr = "Wh";
    char* mW = "mW";
    char* mA = "mA";
} texts;

struct clocks {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} clock;

void resetClock() {
    clock.hour = 0;
    clock.minute = 0;
    clock.second = 0;
}




