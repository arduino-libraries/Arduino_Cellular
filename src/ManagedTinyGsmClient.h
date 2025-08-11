#ifndef MANAGED_TINY_GSM_CLIENT_H
#define MANAGED_TINY_GSM_CLIENT_H

#include "ModemInterface.h"

/**
 * @class ManagedTinyGsmClient
 * @brief A managed client for TinyGSM that automatically handles socket allocation and release.
 * This class allows you to create multiple clients without worrying about socket management.
 * It uses a static bit field to track used sockets and provides methods to lock and unlock the sockets.
 */
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
    /**
     * @brief Constructs a ManagedTinyGsmClient with the specified modem.
     * @param modem The TinyGsm modem to use.
     */
    ManagedTinyGsmClient(TinyGsm& modem);

    /**
     * Copy constructor for ManagedTinyGsmClient.
     * This constructor allocates a new socket for the copied client.
     * @param other The other ManagedTinyGsmClient to copy from.
     * Note: If the other client is invalid, this will also create an invalid client.
     * The socketId will be -1.
     */
    ManagedTinyGsmClient(const ManagedTinyGsmClient& other);

    /**
     * Assignment operator for ManagedTinyGsmClient.
     * @param other The other ManagedTinyGsmClient to copy from.
     * @return A reference to this ManagedTinyGsmClient.
     */
    ManagedTinyGsmClient& operator=(const ManagedTinyGsmClient& other);

    /**
     * Move constructor for ManagedTinyGsmClient.
     * @param other The other ManagedTinyGsmClient to move from.
     */
    ManagedTinyGsmClient(ManagedTinyGsmClient&& other);

    /**
     * Move assignment operator for ManagedTinyGsmClient.
     * This operator transfers ownership of the socket from the other client to this one.
     * @param other The other ManagedTinyGsmClient to move from.
     * @return A reference to this ManagedTinyGsmClient.
     */
    ManagedTinyGsmClient& operator=(ManagedTinyGsmClient&& other);

    /**
     * Destructor for ManagedTinyGsmClient.
     * Releases the socket if it is valid.
     */
    ~ManagedTinyGsmClient();
    
    /**
     * Get the socket ID for this client.
     * The maximum number of sockets is defined by TINY_GSM_MUX_COUNT.
     * If the client is invalid, the socketId will be -1.
     * @return The socket ID (0 - (TINY_GSM_MUX_COUNT - 1) or -1 if invalid).
     */
    int getSocketId() const { return socketId; }

    /**
     * Check if the client is valid.
     * A client is valid if it has a socket ID >= 0.
     * This is useful to check if the client can be used for network operations.
     * @return True if the client is valid, false otherwise.
     */
    bool isValid() const { return socketId >= 0; }
};

#endif // MANAGED_TINY_GSM_CLIENT_H
