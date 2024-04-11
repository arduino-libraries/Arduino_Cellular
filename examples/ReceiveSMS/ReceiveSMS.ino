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
    
    Serial.println("Connecting...");
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
