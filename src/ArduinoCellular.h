
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
#include "ArduinoBearSSLConfig.h"
#include <ArduinoBearSSL.h>
#include <ModemInterface.h>
#include <TimeUtils.h>

/**
 * @enum ModemModel
 * @brief Represents the model of the modem.
*/
enum ModemModel {
    EC200, /**< Quectel EC200 modem. */
    EG95,  /**< Quectel EG95 modem. */
    Unsupported /**< Unsupported modem model. */
};

/**
 * Represents an SMS message.
 */
class SMS {
    public:
        String number; /**< The phone number associated with the SMS. */
        String message; /**< The content of the SMS message. */
        Time timestamp; /**< The timestamp when the SMS was received. */

        /**
         * Default constructor for SMS.
         * Initializes the number, message, and timestamp to empty values.
         */
        SMS() {
            this->number = "";
            this->message = "";
            this->timestamp = Time();
        }
        
        /**
         * Constructor for SMS.
         * @param number The phone number associated with the SMS.
         * @param message The content of the SMS message.
         * @param timestamp The timestamp when the SMS was received.
         */
        SMS(String number, String message, Time timestamp) {
            this->number = number;
            this->message = message;
            this->timestamp = timestamp;
        }
};


/**
 * @struct Location
 * @brief Represents a geographic location with latitude and longitude coordinates.
 */
struct Location {
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
         * @brief Default constructor.
         */
        ArduinoCellular();

        /**
         * @brief Initializes the modem.
         */
        void begin();

        /**
         * @brief Connects to the network using the specified APN, GPRS username, and GPRS password.
         * @param apn The Access Point Name.
         * @param gprsUser The GPRS username.
         * @param gprsPass The GPRS password.
         * @param pin The SIM card PIN.
         * @return True if the connection is successful, false otherwise.
         */
        bool connect(String apn, String gprsUser, String gprsPass, String pin = "");

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
         * @brief Enables or disables the GPS module.
         * @param assisted True to enable assisted GPS, false to disable it. Assist GPS uses the network to get the GPS location faster, so cellular needs to be enabled. 
         * @return True if the GPS module is enabled, false otherwise.
         */
        bool enableGPS(bool assisted = false);

        /**
         * @brief Gets the GPS location. (Blocking call)
         * @param timeout The timeout (In milliseconds) to wait for the GPS location. 
         * @return The GPS location. If the location is not retrieved, the latitude and longitude will be 0.0.
         */
        Location getGPSLocation(unsigned long timeout = 60000);
        
        /**
         * @brief Gets the cellular location. (Blocking call) 
         * @param timeout The timeout (In milliseconds) to wait for the cellular location. 
         * @return The cellular location. If the location is not retrieved, the latitude and longitude will be 0.0.
         */
        Location getCellularLocation(unsigned long timeout = 10000);

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
         * @brief Sends an AT command to the modem and waits for a response, then returns the response.
         * @param command The AT command to send.
         * @param timeout The timeout (In milliseconds) to wait for the response.
         * @return The response from the modem.
         */
        String sendATCommand(char * command, unsigned long timeout = 1000);


        /**
         * @brief Gets the Network client. (OSI Layer 3)
         * @return The GSM client.
         */
        TinyGsmClient getNetworkClient();

        /**
         * @brief Gets the Transport Layer Security (TLS) client. (OSI Layer 4)
         * @return The GSM client.
         */
        BearSSLClient getSecureNetworkClient();

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
         * @brief Unlocks the SIM card using the specified PIN.
         * @param pin The SIM card PIN.
         * @return True if the SIM card is unlocked, false otherwise.
         */
        bool unlockSIM(const char * pin);

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
};


#endif
