#ifndef ARDUINO_4G_MODULE_H
#define ARDUINO_4G_MODULE_H

//#define DUMP_AT_COMMANDS

#define TINY_GSM_RX_BUFFER 1024
#define TINY_GSM_MODEM_BG96


#include <Arduino.h>
#include <StreamDebugger.h>
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

class ModemInterface : public TinyGsmBG96 {
public:
  explicit ModemInterface(Stream& stream, int power_pin) : TinyGsmBG96(stream),stream(&stream),power_pin(power_pin) {
    
  };
  bool init(const char* pin = NULL) {
    pinMode(power_pin, OUTPUT);
    digitalWrite(power_pin, HIGH);
    delay(1000);
    #ifdef DUMP_AT_COMMANDS
      #if defined(ARDUINO_PORTENTA_C33)
        extern UART Serial1_FC;
        Serial1_FC.begin(115200);
      #endif
    #else
    ((arduino::HardwareSerial*)stream)->begin(115200);
    #endif
    return TinyGsmBG96::init();
  };
public:
  Stream* stream;
  int power_pin;
};

extern ModemInterface modem;



#endif
