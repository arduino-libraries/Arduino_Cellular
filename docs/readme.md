# Arduino Cellular Library


## Initialising 
This guide outlines the steps to establish cellular network connectivity using an Arduino equipped with a cellular modem. The process involves initializing the modem, setting necessary configurations, and establishing a connection to the network.

First, you need to include the ArduinoCellular library in your sketch. This library facilitates communication between your Arduino board and the cellular module.

```c
#include <ArduinoCellular.h>
```

Create an instance of the ArduinoCellular class. This instance will be used to interact with the cellular module.

```c
ArduinoCellular cellular = ArduinoCellular();
```

To begin, initialize the modem with basic configurations such as setting the modem to text mode, enabling intrrerupts etc.  This is done by calling the begin() method on your cellular instance. 
```c
cellular.begin();
```

To connect to your mobile network and start a cellular data session, use the connect() method. This requires the APN (Access Point Name), login credentials (if any), and your SIM card's PIN number (if it's locked).

```c
cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD, SECRET_PINNUMBER);

```

Note: It's a best practice to store sensitive information like the GPRS APN, login credentials, and PIN number in a separate header file named arduino_secrets.h. This prevents hardcoding sensitive information in your main sketch file.

**arduino_secrets.h**
Create or edit the arduino_secrets.h file in your project directory and define the necessary secrets as follows:

```c
#define SECRET_GPRS_APN        "your_apn_here"
#define SECRET_GPRS_LOGIN      "your_login_here"
#define SECRET_GPRS_PASSWORD   "your_password_here"
#define SECRET_PINNUMBER       "your_pin_here"
```

Replace the placeholder values with the actual APN, login, password, and PIN number provided by your mobile network operator or SIM card provider.


## Network  
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
```c
TinyGSMClient client = cellulat.getNetworkClient();
```

### Secure Network Client 
Adds a layer of security by implementing SSL/TLS encryption over the basic client.
```c
BearSSLClient secureClient = cellular.getSecureNetworkClient();
```

For convenience we added getters for http and https clients. 

### HTTP and HTTPS Clients:
These are high-level clients designed for web communication. They abstract the complexities of HTTP/HTTPS protocols, making it easy to send web requests and process responses.

```c
HttpClient http = cellular.getHTTPClient(server, port);
HttpClient http = cellular.getHTTPSClient(server, port);
```



## SMS 


## Time and Location