/**
 * @file ModemInterface.h
 * @brief Header file for the ModemInterface class.
 */

#ifndef ARDUINO_4G_MODULE_H
#define ARDUINO_4G_MODULE_H

//#define DUMP_AT_COMMANDS

#define TINY_GSM_RX_BUFFER 1024
#define TINY_GSM_MODEM_BG96


#include <Arduino.h>
#include <StreamDebugger.h>
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

/**
 * @class ModemInterface
 * @brief Represents the interface to the 4G modem module.
 */
class ModemInterface : public TinyGsmBG96 {
public:
  /**
   * @brief Constructor for the ModemInterface class.
   * @param stream The stream object for communication with the modem.
   * @param power_pin The pin number for controlling the power of the modem.
   */
  explicit ModemInterface(Stream& stream, int power_pin) : TinyGsmBG96(stream),stream(&stream),power_pin(power_pin) {
    
  };

  /**
   * @brief Initializes the modem interface.
   * @param pin The PIN code for the SIM card (optional).
   * @return True if initialization is successful, false otherwise.
   */
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
  Stream* stream; /**< The stream object for communication with the modem. */
  int power_pin; /**< The pin number for controlling the power of the modem. */
};

/**
 * @brief The global modem object.
 */
extern ModemInterface modem; 

#endif
