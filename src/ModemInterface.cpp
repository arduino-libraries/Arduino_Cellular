// HD connectors naming
// GPIO5 must be turned on
// SERIAL1 is the UART

#include <ModemInterface.h>


#if defined(ARDUINO_PORTENTA_C33)
    // P602/P110/P603/P604 -> Serial1
    UART Serial1_FC(UART1_TX_PIN, UART1_RX_PIN, 61, 62);

    #ifdef DUMP_AT_COMMANDS
    StreamDebugger          debugger(Serial1_FC, Serial);
    __attribute__ ((init_priority (101))) ModemInterface        modem(debugger, 32);
    #else
    __attribute__ ((init_priority (101))) ModemInterface        modem(Serial1_FC, 32);
    #endif

// P708 (32) is the ON pin
#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(CORE_CM4)
#include "pinDefinitions.h"


// P602/P110/P603/P604 -> Serial1  
    #ifdef DUMP_AT_COMMANDS
    StreamDebugger          debugger(Serial1, Serial);
    __attribute__ ((init_priority (101))) ModemInterface modem(debugger, PinNameToIndex(PG_3));
    #else
    __attribute__ ((init_priority (101))) ModemInterface modem(Serial1, PinNameToIndex(PG_3));
    #endif



// PG3 () is the ON pin
#endif
