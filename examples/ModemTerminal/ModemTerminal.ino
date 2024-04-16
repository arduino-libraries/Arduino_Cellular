/**
 * The ModemTerminal example demonstrates how to use the ArduinoCellular library to send raw AT commands to the modem.
 * 
 * Instructions:
 * 1. Insert a SIM card with or without PIN code in the Arduino Pro 4G Module.
 * 2. Provide sufficient power to the Arduino Pro 4G Module. Ideally, use a 5V power supply
 *   with a current rating of at least 2A and connect it to the VIN and GND pins.
 * 3. Specify the APN, login, and password for your cellular network provider.
 * 4. Upload the sketch to the connected Arduino board.
 * 5. Open the serial monitor and type AT commands to interact with the modem.
 * 
 * Initial author: Cristian Dragomir
*/

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