/**
 * This example demonstrates how to get the current time using the ArduinoCellular library.
 * It derives the time from GPS connection.
 * 
 * Instructions:
 * 1. Move the Arduino Pro 4G Module to an outdoor location with a clear view of the sky.
 * 2. Provide sufficient power to the Arduino Pro 4G Module. Ideally, use a 5V power supply
 * 3. Upload the sketch to the connected Arduino board.
 * 4. Open the serial monitor to view the output.
 * 
 * Initial author: Cristian Dragomir
*/

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
    Geolocation location = cellular.getGPSLocation(10000);

    if(location.latitude == 0.0 && location.longitude == 0.0){
        Serial.println("Failed to get GPS location");
    } else {
        Time time = cellular.getGPSTime();
        Serial.print("Current time (ISO8601): "); Serial.println(time.getISO8601());
    }
    
    delay(10000);
}