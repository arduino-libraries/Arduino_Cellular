#include "ArduinoCellular.h"

ArduinoCellular cellular = ArduinoCellular();

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

void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.begin();
    delay(2000); // Give the modem some time to initialize
}

void loop(){
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

    // Prompt user which SMS to delete
    Serial.println("Enter the index of the SMS you want to delete:");
    
    while(Serial.available() == 0);
    auto index = Serial.readStringUntil('\n').toInt();
    Serial.println("Deleting SMS...");

    if(cellular.deleteSMS(index)){
        Serial.println("SMS deleted.");
    } else {
        Serial.println("Failed to delete SMS.");
    }
}
