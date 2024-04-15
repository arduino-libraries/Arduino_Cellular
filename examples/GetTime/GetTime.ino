#include "ArduinoCellular.h"

ArduinoCellular cellular = ArduinoCellular();

void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.begin();

    if(!cellular.enableGPS()){
        Serial.println("Failed to enable GPS");
        while(true); // Stop the program
    }
    delay(2000); // Give the modem some time to initialize
}

void loop(){
    Location location = cellular.getGPSLocation(10000);

    if(location.latitude == 0.0 && location.longitude == 0.0){
        Serial.println("Failed to get GPS location");
    } else {
        Time time = cellular.getGPSTime();
        Serial.print("Current time (ISO8601): "); Serial.println(time.getISO8601());
    }
    
    delay(10000);
}