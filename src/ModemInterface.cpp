// HD connectors naming
// GPIO5 must be turned on
// SERIAL1 is the UART

#include <ModemInterface.h>

#if defined(ARDUINO_PORTENTA_C33)
    // On the C33 the Serial1 object is already defined, but it does not have hardware flow control
    // mbed allows us to define a UART object with software flow control on given pins 
    // P602/P110/P603/P604 -> Serial1
    UART Serial1_FC(UART1_TX_PIN, UART1_RX_PIN, PORTENTA_C33_CTS_PIN, PORTENTA_C33_RTS_PIN);

    #ifdef DUMP_AT_COMMANDS
    StreamDebugger          debugger(Serial1_FC, Serial);
    
    // we need to make sure that the Modem object is initialised before anything else in the sketch to avoid issues with the TinyGSM library
    // the init_priority attribute is used to set the priority of the constructor, the lower the number the higher the priority (101 to 65535)
    // for more information see https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Attributes.html
    __attribute__ ((init_priority (101))) ModemInterface        modem(debugger, PORTENTA_C33_MODEM_ON_PIN);
    #else
    __attribute__ ((init_priority (101))) ModemInterface        modem(Serial1_FC, PORTENTA_C33_MODEM_ON_PIN);
    #endif

#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(CORE_CM4)
    #include "pinDefinitions.h"

    // P602/P110/P603/P604 -> Serial1  
    #ifdef DUMP_AT_COMMANDS
    StreamDebugger          debugger(Serial1, Serial);
    __attribute__ ((init_priority (101))) ModemInterface modem(debugger, PinNameToIndex(PORTENTA_H7_MODEM_ON_PIN));
    #else
    __attribute__ ((init_priority (101))) ModemInterface modem(Serial1, PinNameToIndex(PORTENTA_H7_MODEM_ON_PIN));
    #endif

#else
    #error "Unsupported board. Please define the modem interface for your board."
#endif
