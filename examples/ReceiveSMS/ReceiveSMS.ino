/**
 * This example demonstrates how to receive SMS messages using ArduinoCellular library.
 * It supports both polling and interrupt based methods to check for new SMS messages.
 * 
 * Instructions:
 * 1. Insert a SIM card with or without PIN code in the Arduino Pro 4G Module.
 * 2. Provide sufficient power to the Arduino Pro 4G Module. Ideally, use a 5V power supply
 *    with a current rating of at least 2A and connect it to the VIN and GND pins.
 * 3. Specify the PIN code of your SIM card if it has one.
 * 4. Upload the sketch to the connected Arduino board.
 * 5. Send an SMS to the SIM card number to test the SMS reception. 
 * 6. Check the serial monitor for the received SMS.
 * 
 * Initial author: Cristian Dragomir
*/

#include "ArduinoCellular.h"

constexpr int NEW_SMS_INTERRUPT_PIN = A0;

ArduinoCellular cellular = ArduinoCellular();
volatile boolean smsReceived = false;
constexpr int POLLING_INTERVAL_MS = 1 * 60 * 1000; // 1 minute

void printMessages(std::vector<SMS> msg){
     for(int i = 0; i < msg.size(); i++){
        Serial.println("SMS:");
        Serial.print("* Index: "); Serial.println(msg[i].index);
        Serial.print("* From: "); Serial.println(msg[i].sender);
        Serial.print("* Timestamp: "); Serial.println(msg[i].timestamp.getISO8601());
        Serial.println("* Message: "); Serial.println(msg[i].message);
        Serial.println("--------------------\n");
    }
}
void onSMSReceived(){
    smsReceived = true;
}

void setup(){
    Serial.begin(115200);
    while (!Serial);
    // cellular.setDebugStream(Serial); // Uncomment this line to enable debug output
    cellular.begin();

    String pinCode = ""; // If your SIM card has a PIN code, specify it here e.g. "1234"
    if(pinCode.length() > 0 && !cellular.unlockSIM(pinCode)){
        Serial.println("Failed to unlock SIM card.");
        while(true); // Stop here
    }
    
    Serial.println("Connecting to network...");
    cellular.connect();
    Serial.println("Connected!");

    // Register interrupt based callback for new SMS
    attachInterrupt(digitalPinToInterrupt(NEW_SMS_INTERRUPT_PIN), onSMSReceived, RISING);

    std::vector<SMS> readSMS = cellular.getReadSMS();
    if(readSMS.size() > 0){
        Serial.println("Read SMS:");
        printMessages(readSMS);
    }

    std::vector<SMS> unreadSMS = cellular.getUnreadSMS();
    if(unreadSMS.size() > 0){
        Serial.println("Unread SMS:");
        printMessages(unreadSMS);
    }
}

void loop(){
    static unsigned long lastPoll = 0;
    static bool checkForNewSMS = false;

    if(millis() - lastPoll > POLLING_INTERVAL_MS){
        checkForNewSMS = true;
        lastPoll = millis();
    }

    if(smsReceived || checkForNewSMS){
        smsReceived = false;
        checkForNewSMS = false;
        std::vector<SMS> unreadSMS = cellular.getUnreadSMS();

        if (unreadSMS.size() > 0){
            Serial.println("New SMS received!");
            printMessages(unreadSMS);
        }
    }
}
