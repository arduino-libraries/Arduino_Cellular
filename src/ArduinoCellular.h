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

enum ModemModel {
    EC200,
    EG95,
    Unsupported
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
         * @return True if the connection is successful, false otherwise.
         */
        bool connect(const char * apn, const char * gprsUser, const char * gprsPass);

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
         * @param number The phone number to send the SMS to. (TODO: find out number format)
         * @param message The message to send.
         * @return True if the SMS is sent successfully, false otherwise.
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
         * @return The response from the modem.
         */
        String sendATCommand(char * command, unsigned long timeout = 1000);

        /*
        * @brief Sends an USSD command to the modem and waits for a response, then returns the response.
        * @param command The USSD command to send. (e.g. *100#)
        * @return The response from the modem.
        */
        String sendUSSDCommand(char * command);

        /**
         * @brief Gets the Network client. (OSI Layer 3)
         * @return The GSM client.
         */
        TinyGsmClient getNetworkClient();

        /**
         * @brief Gets the HTTP client for the specified server and port.
         * @param server The server address.
         * @param port The server port.
         * @return The HTTP client.
         */
        HttpClient getHTTPClient(const char * server, const int port);

        HttpClient getHTTPSClient(const char * server, const int port);

        void getConnectionStatus();
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
         * @return True if the GPS location is retrieved, false otherwise.
         */
        void getGPSLocation(float* latitude, float* longitude, unsigned long timeout = 60000);


        TinyGsmClient client; /**< The GSM client. */

        ModemModel model; /**< The modem model. */

        static unsigned long getTime();
};


#endif