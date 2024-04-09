#include "ArduinoCellular.h"
#include "arduino_secrets.h"

// #define TINY_GSM_DEBUG Serial
// #define ARDUINO_CELLULAR_DEBUG

constexpr int NEW_SMS_INTERRUPT_PIN = A0;

ArduinoCellular cellular = ArduinoCellular();
volatile boolean smsReceived = false;

void printMessages(std::vector<SMS> msg){
     for(int i = 0; i < msg.size(); i++){
        Serial.println("SMS:");
        Serial.print("\t * From: "); Serial.println(msg[i].number);
        Serial.print("\t * Message: "); Serial.println(msg[i].message);
        Serial.print("\t * Timestamp: "); Serial.println(msg[i].timestamp.getISO8601());
    }
}
void onSMSReceived(){
    Serial.println("New SMS received!");
    smsReceived = true;
}

void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.setDebugStream(Serial);

    cellular.begin();
    Serial.println("Connecting...");
    cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD, SECRET_PINNUMBER);
    
    // Register interrupt based callback for new SMS
    attachInterrupt(digitalPinToInterrupt(NEW_SMS_INTERRUPT_PIN), onSMSReceived, RISING);

    Serial.println("Read SMS:");
    std::vector<SMS> readSMS = cellular.getReadSMS();
    printMessages(readSMS);

    Serial.println("Unread SMS:");
    std::vector<SMS> unreadSMS = cellular.getUnreadSMS();
    printMessages(unreadSMS);
}

void loop(){
    if(smsReceived){
        smsReceived = false;
        std::vector<SMS> unreadSMS = cellular.getUnreadSMS();
        if (unreadSMS.size() > 0){
            printMessages(unreadSMS);
        }
    }
}
