#ifndef MANAGED_TINY_GSM_CLIENT_H
#define MANAGED_TINY_GSM_CLIENT_H

#include "ModemInterface.h"

class ManagedTinyGsmClient : public TinyGsmClient {
private:
    int socketId;
    static uint32_t usedSockets;        // Bit field to track sockets 0-(TINY_GSM_MUX_COUNT-1)
    static bool socketMutex;            // Simple mutex flag
    
    static int allocateSocket();
    static void releaseSocket(int socketId);
    static void lockSockets();
    static void unlockSockets();

public:
    ManagedTinyGsmClient(TinyGsm& modem);
    ManagedTinyGsmClient(const ManagedTinyGsmClient& other);
    ManagedTinyGsmClient& operator=(const ManagedTinyGsmClient& other);
    ManagedTinyGsmClient(ManagedTinyGsmClient&& other);
    ManagedTinyGsmClient& operator=(ManagedTinyGsmClient&& other);
    ~ManagedTinyGsmClient();
    
    int getSocketId() const { return socketId; }
    bool isValid() const { return socketId >= 0; }
};

#endif // MANAGED_TINY_GSM_CLIENT_H
