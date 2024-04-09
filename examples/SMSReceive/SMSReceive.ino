#include "ArduinoCellular.h"
#include "arduino_secrets.h"



#define TINY_GSM_DEBUG Serial
#define ARDUINO_CELLULAR_DEBUG

ArduinoCellular cellular = ArduinoCellular();

boolean newSMS = false;


void printMessages(std::vector<SMS> msg){
     for(int i = 0; i < msg.size(); i++){
        Serial.println("SMS:");
        Serial.print("\t * From: "); Serial.println(msg[i].number);
        Serial.print("\t * Message: "); Serial.println(msg[i].message);
        Serial.print("\t * Timestamp: "); Serial.println(msg[i].timestamp.getISO8601());
    }
}
void newSMSCallback(){
    Serial.println("new sms received");
    newSMS = true;
}

void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.begin();
    cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD, SECRET_PINNUMBER);
    
    
    attachInterrupt(digitalPinToInterrupt(A0), newSMSCallback, RISING);

    Serial.println("Read SMS:");
    std::vector<SMS> readSMS = cellular.getReadSMS();
    printMessages(readSMS);

    Serial.println("Unread SMS:");
    std::vector<SMS> unreadSMS = cellular.getUnreadSMS();
    printMessages(unreadSMS);

    cellular.sendSMS("+40788494946", "bleep bleep");
}

void loop(){
    if(newSMS){
        newSMS = false;
        std::vector<SMS> unreadSMS = cellular.getUnreadSMS();
        if (unreadSMS.size() > 0){
            printMessages(unreadSMS);
        }
    }
}