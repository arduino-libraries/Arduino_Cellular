// HD connectors naming
// GPIO5 must be turned on
// SERIAL1 is the UART

#include <ModemInterface.h>

#if defined(ARDUINO_PORTENTA_C33)
    #define ON_PIN 32 // P708 (32) is the ON pin

    // P602/P110/P603/P604 -> Serial1
    UART Serial1_FC(UART1_TX_PIN, UART1_RX_PIN, 61, 62);

    #ifdef DUMP_AT_COMMANDS
    StreamDebugger          debugger(Serial1_FC, Serial);
    __attribute__ ((init_priority (101))) ModemInterface        modem(debugger, ON_PIN);
    #else
    __attribute__ ((init_priority (101))) ModemInterface        modem(Serial1_FC, ON_PIN);
    #endif

#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(CORE_CM4)
    #include "pinDefinitions.h"
    #define ON_PIN PG_3 // PG3 is the ON pin

    // P602/P110/P603/P604 -> Serial1  
    #ifdef DUMP_AT_COMMANDS
    StreamDebugger          debugger(Serial1, Serial);
    __attribute__ ((init_priority (101))) ModemInterface modem(debugger, PinNameToIndex(ON_PIN));
    #else
    __attribute__ ((init_priority (101))) ModemInterface modem(Serial1, PinNameToIndex(ON_PIN));
    #endif

#endif
