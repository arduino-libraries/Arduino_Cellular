# 📡 Arduino Cellular Library

## ⤵️ Initialising 
This guide outlines the steps to establish cellular network connectivity using an Arduino equipped with a cellular modem. The process involves initializing the modem, setting necessary configurations, and establishing a connection to the network.

First, you need to include the ArduinoCellular library in your sketch. This library facilitates communication between your Arduino board and the cellular module.

```cpp
#include <ArduinoCellular.h>
```

Create an instance of the ArduinoCellular class. This instance will be used to interact with the cellular module.

```cpp
ArduinoCellular cellular = ArduinoCellular();
```

To begin, initialize the modem with basic configurations such as setting the modem to text mode, enabling intrrerupts etc.  This is done by calling the begin() method on your cellular instance. 
```cpp
cellular.begin();
```

To connect to your mobile network and start a cellular data session, use the connect() method. This requires the APN (Access Point Name) and login credentials (if any). You can unlock your SIM card's using its PIN number (if it's locked).

```cpp
cellular.unlockSIM(SECRET_PINNUMBER)
cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD);

```

Note: It's a best practice to store sensitive information like the GPRS APN, login credentials, and PIN number in a separate header file named arduino_secrets.h. This prevents hardcoding sensitive information in your main sketch file.

**arduino_secrets.h**
Create or edit the arduino_secrets.h file in your project directory and define the necessary secrets as follows:

```cpp
#define SECRET_GPRS_APN        "your_apn_here"
#define SECRET_GPRS_LOGIN      "your_login_here"
#define SECRET_GPRS_PASSWORD   "your_password_here"
#define SECRET_PINNUMBER       "your_pin_here"
```

Replace the placeholder values with the actual APN, login, password, and PIN number provided by your mobile network operator or SIM card provider.


## 🌐 Network  
The Arduino environment provides a set of classes designed to abstract the complexities of handling network communications. Among these, the Client class plays a crucial role as it defines a standard interface for network communication across various Arduino-compatible networking libraries. 

The Arduino networking stack is designed to simplify the process of implementing network communication for IoT (Internet of Things) projects. This stack encompasses both hardware (e.g., Ethernet shields, WiFi modules) and software components (libraries that interface with the hardware). The stack is built in a way that allows sketches (Arduino programs) to communicate over the network using common protocols like TCP and UDP without needing to delve into the low-level mechanics of these protocols.

For different networking hardware, specific libraries provide concrete implementations of the Client class. For example:

* **Ethernet Library:** Contains the EthernetClient, tailored for wired network connections.
* **WiFi Library:** Includes the WiFiClient, designed for wireless network interactions.
* **TinyGSM Library:** Offers the TinyGSMClient for cellular network communications.
These implementations handle the low-level details of communicating over their respective network mediums while presenting a unified interface to the user.


A powerful feature of this design is the ability to layer and chain clients to add functionalities. For instance, you might start with a basic network client for TCP/IP communication. If you need secure communications, you can wrap this client within a SSL/TLS client that encrypts the data, such as BearSSLClient. On top of this, if your application communicates over HTTP or HTTPS, you can use an HTTP client that leverages the underlying secure client.

This layered approach is not only modular but also highly flexible, allowing developers to mix and match functionalities as needed.


### Network Client (OSI Layer 3)
Represents a basic client for network communication, suitable for protocols like TCP/IP.
```cpp
TinyGSMClient client = cellular.getNetworkClient();
```

### Secure Network Client 
Adds a layer of security by implementing SSL/TLS encryption over the basic client.
```cpp
BearSSLClient secureClient = cellular.getSecureNetworkClient();
```

For convenience we added getters for http and https clients. 

### HTTP and HTTPS Clients:
These are high-level clients designed for web communication. They abstract the complexities of HTTP/HTTPS protocols, making it easy to send web requests and process responses.

```cpp
HttpClient http = cellular.getHTTPClient(server, port);
HttpClient http = cellular.getHTTPSClient(server, port);
```



## 📨 SMS 
The SMS functionality allows devices to exchange information with users or other systems through simple text messages, enabling a wide range of applications from remote monitoring to control systems or a fallback communication method when the others are not available. 

### Reading SMS Messages
**getReadSMS():** This method returns a vector containing SMS messages that have already been read. It's particularly useful for applications that need to process or display messages that have been acknowledged.

**getUnreadSMS():** This method fetches a vector of unread SMS messages, allowing the application to process or notify users about new messages.

Each SMS message is represented as an instance of the `SMS` class, which contains the sender's number, the message text, and a timestamp marking when the message was received.


### The SMS Class
The SMS class serves as a container for information related to a single SMS message. It includes the following attributes:

* `sender`: The phone number from which the SMS was sent.
* `message`: The body of the SMS message.
* `timestamp`: A timestamp indicating when the message was received by the module.

The class provides constructors for initializing an SMS object either with default values or with specific details about the message.

### Sending SMS Messages
Sending SMS messages is a straightforward process with the Arduino cellular library. 

The method sendSMS() is designed for this purpose, taking two parameters:

* `number`: The recipient's phone number.
* `message`: The text of the message to be sent.

This functionality allows Arduino devices to communicate outwardly to users or other systems, sending alerts, data, or control commands via SMS.

## ⌚️📍 Time and Location
These features enable precise tracking of device locations and ensure synchronized operations across different systems. This guide focuses on utilizing GPS and cellular network capabilities for location tracking and time synchronization. It's important to note that GPS functionality is exclusively available in the Global Version of the modem, highlighting the need for appropriate hardware selection based on the project requirements.

### GPS Location
**Method Overview:** `getGPSLocation(unsigned long timeout = 60000)` is a blocking call that attempts to acquire the current GPS location within the specified timeout period. The method returns a Location structure, containing latitude and longitude values. If the location cannot be retrieved within the timeout, both values default to 0.0.

GPS Location is ideal for applications requiring high-precision location data, such as asset tracking or outdoor navigation solutions. This functionality relies on the Global Version of the modem, which is equipped with GPS capabilities.

To enable GPS Location you will need to call `enableGPS(bool assisted)`. Assisted GPS or A-GPS is an enhancement of GPS that uses the cellular network to get the location, it performs that much quicker than without assistance but depends on Cellular network coverage. 

### Time Synchronization
Time synchronization is crucial for maintaining accurate timing across IoT devices, especially for data logging, scheduled tasks, and time-stamped communications.

#### Cellular Time
**Method Overview**: `getCellularTime()` fetches the current time from the cellular network, providing a reliable time source even without GPS signals. The time is returned as a Time object.

Cellular time is perfect for devices that require accurate time but operate in areas with limited or no GPS coverage. Since it relies on the cellular network, it ensures time synchronization across devices distributed geographically.

#### GPS Time
**Method Overview**: getGPSTime() obtains the current time from the GPS module, offering highly accurate and globally synchronized time data. The method returns a Time object.

GPS Time for applications demanding precise timekeeping, benefiting from the global synchronization capabilities of GPS satellites. This feature is exclusive to devices equipped with the Global Version of the modem that includes GPS functionality.


### The Time Class
The Time class represents a specific point in time, including year, month, day, hour, minute, second, and timezone offset. 

It supports parsing from ISO8601 and UNIX timestamp formats, offering flexibility in handling time data. This class is crucial for applications that manage events, log data with timestamps, or perform scheduled operations.
