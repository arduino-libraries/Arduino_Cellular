#include "ArduinoCellular.h"

ArduinoCellular cellular = ArduinoCellular();

void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.setDebugStream(Serial);
    cellular.begin();
    
    if(!cellular.enableGPS()){
        Serial.println("Failed to enable GPS");
        while(true); // Stop the program
    }
    delay(2000); // Give the modem some time to initialize
}

void loop(){
    Location location = cellular.getGPSLocation();
    Serial.println("GPS Location:");
    Serial.print("* Latitude: "); Serial.println(location.latitude, 6);
    Serial.print("* Longitude: "); Serial.println(location.longitude, 6);
    Serial.println("--------------------\n");
    delay(10000);
}
