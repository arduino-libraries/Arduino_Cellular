#include "ArduinoCellular.h"
#include "arduino_secrets.h"

ArduinoCellular cellular = ArduinoCellular();

void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.setDebugStream(Serial); // Uncomment this line to enable debug output
    cellular.begin();

    if(String(SECRET_PINNUMBER).length() > 0 && !cellular.unlockSIM(SECRET_PINNUMBER)){
        Serial.println("Failed to unlock SIM card.");
        while(true); // Stop here
    }

    Serial.println("Connecting...");
    cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD);
    Serial.println("Connected!");
    Serial.println("You can now send AT commands to the modem.");
}

void loop() {
  while(Serial.available() == 0); // Wait for user input

  // Read data from serial until newline
  String userInput = Serial.readStringUntil('\n');

  // Call the sendATCommand function with the read data
  String response = cellular.sendATCommand(userInput.c_str());
  Serial.println(response);
}