/**
 * This example demonstrates how to get the current GPS location using the ArduinoCellular library.
 * 
 * Instructions:
 * 1. Move the Arduino Pro 4G Module to an outdoor location with a clear view of the sky.
 * 2. Provide sufficient power to the Arduino Pro 4G Module. Ideally, use a 5V power supply
 * 3. Upload the sketch to the connected Arduino board.
 * 4. Open the serial monitor to view the output.
 * 
 * Initial author: Sebastian Romero
*/

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
