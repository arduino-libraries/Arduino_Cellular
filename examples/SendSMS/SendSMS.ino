/*
 * This example shows how to send an SMS message using the Arduino_Cellular library.
 * 
 * Instructions:
 * 1. Insert a SIM card with or without PIN code in the Arduino Pro 4G Module.
 * 2. Provide sufficient power to the Arduino Pro 4G Module. Ideally, use a 5V power supply
 *    with a current rating of at least 2A and connect it to the VIN and GND pins.
 * 3. Make sure the SIM card has enough credit to send SMS messages.
 * 4. Specify the APN, GPRS username, and GPRS password of your mobile network provider.
 * 5. Specify the PIN code of your SIM card if it has one.
 * 6. Specify the phone number of the recipient and the message you want to send. 
 * 7. Upload the sketch to the connected Arduino board.
 * 
 * Initial author: Sebastian Romero @sebromero
 */
#include "ArduinoCellular.h"

const char apn[]      = "internet";
const char gprsUser[] = "";
const char gprsPass[] = "";

ArduinoCellular cellular = ArduinoCellular();

void setup(){
    Serial.begin(115200);
    while (!Serial);
    delay(1000); // Give the serial monitor some time to start

    cellular.begin();
    String pinCode = "1234"; // If your SIM card has a PIN code, specify it here

    Serial.println("Connecting to network...");
    cellular.connect(apn, gprsUser, gprsPass, pinCode);

    Serial.println("Sending SMS...");
    cellular.sendSMS("+41791234567", "bleep bleep");
    Serial.println("Done.");
}

void loop(){
    delay(1000);
}
