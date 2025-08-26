#include "ManagedTinyGsmClient.h"

// Static member definitions
uint32_t ManagedTinyGsmClient::usedSockets = 0;
bool ManagedTinyGsmClient::socketMutex = false;

void ManagedTinyGsmClient::lockSockets() {
    // Simple spinlock - not ideal but works for basic protection
    while (socketMutex) {
        delay(1); // Small delay to prevent busy waiting
    }
    socketMutex = true;
}

void ManagedTinyGsmClient::unlockSockets() {
    socketMutex = false;
}

int ManagedTinyGsmClient::allocateSocket() {
    lockSockets();
    
    for (int i = 0; i < TINY_GSM_MUX_COUNT; i++) {
        uint32_t mask = 1UL << i;
        if (!(usedSockets & mask)) {
            usedSockets |= mask;  // Set bit i
            unlockSockets();
            return i;
        }
    }
    
    unlockSockets();
    return -1; // No available sockets
}

void ManagedTinyGsmClient::releaseSocket(int socketId) {
    if (socketId >= 0 && socketId < TINY_GSM_MUX_COUNT) {
        lockSockets();
        uint32_t mask = 1UL << socketId;
        usedSockets &= ~mask;  // Clear bit socketId
        unlockSockets();
    }
}

ManagedTinyGsmClient::ManagedTinyGsmClient(TinyGsm& modem) 
    : socketId(allocateSocket()), TinyGsmClient(modem, socketId) {
    // Note: If socketId is -1, the client is invalid
}

ManagedTinyGsmClient::ManagedTinyGsmClient(const ManagedTinyGsmClient& other)
    : socketId(allocateSocket()), TinyGsmClient(other) {
    // Copy constructor allocates a new socket
    // Note: If socketId is -1, the client is invalid
}

ManagedTinyGsmClient& ManagedTinyGsmClient::operator=(const ManagedTinyGsmClient& other) {
    if (this != &other) {
        TinyGsmClient::operator=(other);
        // Keep our own socket - don't change it
    }
    return *this;
}

ManagedTinyGsmClient::ManagedTinyGsmClient(ManagedTinyGsmClient&& other)
    : socketId(other.socketId), TinyGsmClient(other) {
    other.socketId = -1; // Mark other as moved-from
}

ManagedTinyGsmClient& ManagedTinyGsmClient::operator=(ManagedTinyGsmClient&& other) {
    if (this != &other) {
        // Release our current socket
        releaseSocket(socketId);
        
        TinyGsmClient::operator=(other);
        socketId = other.socketId;
        other.socketId = -1; // Mark other as moved-from
    }
    return *this;
}

ManagedTinyGsmClient::~ManagedTinyGsmClient() {
    releaseSocket(socketId);
}