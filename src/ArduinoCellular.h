
/**
 * @file ArduinoCellular.h
 * @brief Header file for the ArduinoCellular library.
 * 
 * This library provides methods to interact with the Arduino Pro Modem, such as connecting to the network,
 * sending SMS messages, getting GPS location, and more.
 */

#ifndef ARDUINO_CELLULAR_MODEM_H
#define ARDUINO_CELLULAR_MODEM_H

#if defined(ARDUINO_CELLULAR_DEBUG)
#define DUMP_AT_COMMANDS
#endif 

#include <Arduino.h>
#include <vector>

#if defined __has_include
  #if !__has_include (<ArduinoIoTCloud.h>)
    #define ARDUINO_CELLULAR_BEARSSL
  #endif
#endif

#if defined(ARDUINO_CELLULAR_BEARSSL)
  #include "ArduinoBearSSLConfig.h"
  #include <ArduinoBearSSL.h>
#endif

#include <ModemInterface.h>
#include <TimeUtils.h>

/**
 * @enum ModemModel
 * @brief Represents the model of the modem.
*/
enum ModemModel {
    EC200, /**< Quectel EC200 modem. */
    EG25,  /**< Quectel EG25 modem. */
    Unsupported /**< Unsupported modem model. */
};

/**
 * Represents an SMS message.
 */
class SMS {
    public:
        int16_t index; /**< The index of the SMS message. */
        String sender; /**< The phone number associated with the SMS. */
        String message; /**< The content of the SMS message. */
        Time timestamp; /**< The timestamp when the SMS was received. */

        /**
         * Default constructor for SMS.
         * Initializes the number, message, and timestamp to empty values.
         */
        SMS() {
            this->index = -1;
            this->sender = "";
            this->message = "";
            this->timestamp = Time();
        }
        
        /**
         * Constructor for SMS.
         * @param index The index of the SMS message.
         * @param sender The phone number associated with the sender of the SMS.
         * @param message The content of the SMS message.
         * @param timestamp The timestamp when the SMS was received.
         */
        SMS(int16_t index, String sender, String message, Time timestamp) {
            this->sender = sender;
            this->message = message;
            this->timestamp = timestamp;
        }
};


/**
 * @struct Geolocation
 * @brief Represents a geographic location with latitude and longitude coordinates.
 */
struct Geolocation {
    float latitude; /**< The latitude coordinate of the location. */
    float longitude; /**< The longitude coordinate of the location. */
};

/**
 * @class ArduinoCellular
 * 
 * This class provides methods to interact with the Arduino Pro Modem, such as connecting to the network,
 * sending SMS messages, getting GPS location, and more.
 */
class ArduinoCellular {
    public: 
        /**
         * @brief Creates an instance of the ArduinoCellular class.
         */
        ArduinoCellular();

        /**
         * @brief Initializes the modem.
         * This function must be called before using any other functions in the library.
         */
        void begin();

        /**
         * @brief Unlocks the SIM card using the specified PIN.
         * @param pin The SIM card PIN.
         * @return True if the SIM card is unlocked, false otherwise.
         */
        bool unlockSIM(String pin);

        /**
         * @brief Registers with the cellular network and connects to the Internet
         * if the APN, GPRS username, and GPRS password are provided.
         * @param apn The Access Point Name.
         * @param username The APN username.
         * @param password The APN password.
         * @return True if the connection is successful, false otherwise.
         */
        bool connect(String apn = "", String username = "", String password = "");

        /**
         * @brief Checks if the modem is registered on the network.
         * @return True if the network is connected, false otherwise.
         */
        bool isConnectedToOperator();

        /**
         * @brief Checks if the GPRS network is connected.
         * @return True if the GPRS network is connected, false otherwise.
         */
        bool isConnectedToInternet();

        /**
         * @brief Enables or disables the GPS functionality.
         * @param assisted True to enable assisted GPS, false to disable it. Assist GPS uses the network to get the GPS location faster, so cellular needs to be enabled. 
         * @return True if GPS was enabled successfully, false otherwise.
         */
        bool enableGPS(bool assisted = false);

        /**
         * @brief Gets the GPS location. (Blocking call)
         * @param timeout The timeout (In milliseconds) to wait for the GPS location. 
         * @return The GPS location. If the location is not retrieved, the latitude and longitude will be 0.0.
         */
        Geolocation getGPSLocation(unsigned long timeout = 60000);
        
        /**
         * @brief Gets the current time from the network.
         * @return The current time.
         */
        Time getCellularTime();

        /**
         * @brief Gets the current time from the GPS module.
         * @return The current time.
         */
        Time getGPSTime();

        /**
         * @brief Sends an SMS message to the specified number.
         * @param number The phone number to send the SMS to.
         * @param message The message to send.
         */
        void sendSMS(String number, String message);

        /**
         * @brief Gets the list of read SMS messages.
         * @return A vector of SMS messages.
         */
        std::vector<SMS> getReadSMS();

        /**
         * @brief Gets the list of unread SMS messages.
         * @return A vector of SMS messages.
         */
        std::vector<SMS> getUnreadSMS();

        /**
         * @brief Deletes an SMS message at the specified index.
         *
         * @param index The index of the SMS message to delete.
         * @return True if the SMS message was successfully deleted, false otherwise.
         */
        bool deleteSMS(uint16_t index);

        /**
         * @brief Sends an AT command to the modem and waits for a response, then returns the response.
         * @param command The AT command to send.
         * @param timeout The timeout (In milliseconds) to wait for the response. Default is 1000ms.
         * @return The response from the modem.
         */
        String sendATCommand(const char * command, unsigned long timeout = 1000);



        /**
         * @brief Sends a USSD command to the network operator and waits for a response.
         * @param command The USSD command to send.
         * @return The response from the network operator. (Note: The response may be an SMS message or a USSD response)
         */
        String sendUSSDCommand(const char * command);
    


        /**
         * @brief Gets the Network client. (OSI Layer 3)
         * @return The GSM client.
         */
        TinyGsmClient getNetworkClient();

        /**
         * @brief Gets the Transport Layer Security (TLS) client. (OSI Layer 4)
         * @return The GSM client.
         */
#if defined(ARDUINO_CELLULAR_BEARSSL)
        BearSSLClient getSecureNetworkClient();
#endif

        /**
         * @brief Gets the HTTP client for the specified server and port.
         * @param server The server address.
         * @param port The server port.
         * @return The HTTP client.
         */
        HttpClient getHTTPClient(const char * server, const int port);

        /**
         * @brief Gets the HTTPS client for the specified server and port.
         * @param server The server address.
         * @param port The server port.
         * @return The HTTPS client.
         */
        HttpClient getHTTPSClient(const char * server, const int port);
        
        /**
         * @brief Gets the local IP address.
         * @return The local IP address.
         */
        IPAddress getIPAddress();

        /**
         * @brief Gets the signal quality.
         * @return The signal quality.
         */
        int getSignalQuality();

        /**
         * @brief Sets the debug stream for ArduinoCellular.
         * 
         * This function allows you to set the debug stream for ArduinoCellular. 
         * The debug stream is used to output debug messages and information.
         * 
         * @param stream A pointer to the Stream object that will be used as the debug stream.
         */
        void setDebugStream(Stream& stream);

    private:
        bool connectToGPRS(const char * apn, const char * gprsUser, const char * gprsPass);
        
        /**
         * @brief Gets the SIM card status.
         * @return The SIM card status.
         */
        SimStatus getSimStatus();

        /**
         * @brief Waits for network registration. (Blocking call)
         * @return True if the network registration is successful, false otherwise.
         */
        bool awaitNetworkRegistration();

        /**
         * @brief Gets the GPS location. (Blocking call)
         * @param latitude Pointer to store the latitude. (0.0 if not retrieved)
         * @param longitude Pointer to store the longitude. (0.0 if not retrieved)
         * @param timeout The timeout (In milliseconds) to wait for the GPS location.
         */
        void getGPSLocation(float* latitude, float* longitude, unsigned long timeout = 60000);


        TinyGsmClient client; /**< The GSM client. */

        ModemModel model; /**< The modem model. */

        Stream* debugStream = nullptr; /**< The stream to be used for printing debugging messages. */

        static unsigned long getTime(); /** Callback for getting the current time as an unix timestamp. */

        static constexpr unsigned long waitForNetworkTimeout = 20000L; /**< Maximum wait time for network registration (In milliseconds). */
};


#endif
