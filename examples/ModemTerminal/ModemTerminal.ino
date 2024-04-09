#include "ArduinoCellular.h"
#include "arduino_secrets.h"


ArduinoCellular cellular = ArduinoCellular();

float lat = 0.00;
float lon = 0.00;


void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.begin();
    cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD, SECRET_PINNUMBER);
}

void loop() {
  if (Serial.available() > 0) {
    // Define a buffer to store incoming data. Adjust the size as needed.
    char incomingData[255]; // Adjust the size according to your needs
    
    // Read data from serial until newline is found
    int size = Serial.readBytesUntil('\n', incomingData, sizeof(incomingData) - 1); // Leave space for null terminator
    
    // Null-terminate the string
    incomingData[size] = '\0';
    // Call the sendATCommand function with the read data
    Serial.println(cellular.sendATCommand(GF(incomingData)));
  }
}