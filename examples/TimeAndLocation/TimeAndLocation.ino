#define DUMP_AT_COMMANDS 

#include "ArduinoCellular.h"


ArduinoCellular cellular = ArduinoCellular();

float lat = 0.00000;
float lon = 0.00000;
int year = 0;
int month = 0;
int day = 0;
int hour = 0;
int minute = 0;
int second = 0;


const char apn[]      = "internet";
const char gprsUser[] = "";
const char gprsPass[] = "";

void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.begin();
    //cellularModem.connect(apn, gprsUser, gprsPass);
    cellular.enableGPS(false);
}

void loop(){
    Location loc = cellular.getGPSLocation(10000);
    Serial.print("Latitude: "); Serial.println(lat);
    Serial.print("Longitude: "); Serial.println(lon);

    Time t = cellular.getGPSTime();
    Serial.print("ISO String: "); Serial.println(t.getISO8601());
    
    delay(1000);

}