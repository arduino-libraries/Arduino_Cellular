# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`ArduinoCellular`](#class_arduino_cellular) | This class provides methods to interact with the Arduino Pro Modem, such as connecting to the network, sending [SMS](#class_s_m_s) messages, getting GPS location, and more.
`class ` [`ModemInterface`](#class_modem_interface) | Represents the interface to the 4G modem module which extends the TinyGsmBG96 class.
`class ` [`SMS`](#class_s_m_s) | Represents an [SMS](#class_s_m_s) message.
`class ` [`Time`](#class_time) | Represents a point in time with year, month, day, hour, minute, second, and offset.
`struct ` [`Location`](#struct_location) | Represents a geographic location with latitude and longitude coordinates.

# class `ArduinoCellular` <a id="class_arduino_cellular" class="anchor"></a>

This class provides methods to interact with the Arduino Pro Modem, such as connecting to the network, sending [SMS](#class_s_m_s) messages, getting GPS location, and more.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`ArduinoCellular`](#class_arduino_cellular_1a96d1d9f3fbe80adc3d460b4364d47870) | Creates an instance of the [ArduinoCellular](#class_arduino_cellular) class. |
| [`begin`](#class_arduino_cellular_1ad5ca7cf61f48c40569f41f3029d6516e) | Initializes the modem. This function must be called before using any other functions in the library. |
| [`unlockSIM`](#class_arduino_cellular_1aa0be2795ff7b23c39ecef90d9906bbdf) | Unlocks the SIM card using the specified PIN. |
| [`connect`](#class_arduino_cellular_1a7fb3c3e841b39c4faacef32cec6277b4) | Registers with the cellular network and connects to the Internet if the APN, GPRS username, and GPRS password are provided. |
| [`isConnectedToOperator`](#class_arduino_cellular_1af7453ef90702e9042e2b4b18fa89db03) | Checks if the modem is registered on the network. |
| [`isConnectedToInternet`](#class_arduino_cellular_1a6f8251e06de1810897b8bd8f8fb1b1a2) | Checks if the GPRS network is connected. |
| [`enableGPS`](#class_arduino_cellular_1abe77a53e0eba6e8d62ba5db3bb6f5e92) | Enables or disables the GPS functionality. |
| [`getGPSLocation`](#class_arduino_cellular_1aee57a2eec5be06172b2fb7cd574d9106) | Gets the GPS location. (Blocking call) |
| [`getCellularTime`](#class_arduino_cellular_1a6b3ce5485badff582584d539e790aff4) | Gets the current time from the network. |
| [`getGPSTime`](#class_arduino_cellular_1a4aeb898c958e6eb001d606f0c7da8799) | Gets the current time from the GPS module. |
| [`sendSMS`](#class_arduino_cellular_1a371aef1318857f0863f443eaeabf4ac2) | Sends an [SMS](#class_s_m_s) message to the specified number. |
| [`getReadSMS`](#class_arduino_cellular_1ae032c4e4cade6579a2c1edfe53d2ff2b) | Gets the list of read [SMS](#class_s_m_s) messages. |
| [`getUnreadSMS`](#class_arduino_cellular_1a212513654884058947a2a4d332f6ccfc) | Gets the list of unread [SMS](#class_s_m_s) messages. |
| [`deleteSMS`](#class_arduino_cellular_1abe4337f0bc8c486a076011309120ace1) | Deletes an [SMS](#class_s_m_s) message at the specified index. |
| [`sendATCommand`](#class_arduino_cellular_1a58a3e3713af0c01ad1075a2509c6874d) | Sends an AT command to the modem and waits for a response, then returns the response. |
| [`sendUSSDCommand`](#class_arduino_cellular_1a6886aec5850836ea8e8f135d4e5632ab) | Sends a USSD command to the network operator and waits for a response. |
| [`getNetworkClient`](#class_arduino_cellular_1acff92474af3bd819b62f132cf12f45ba) | Gets the Network client. (OSI Layer 3) |
| [`getSecureNetworkClient`](#class_arduino_cellular_1a8b7486d1a682787588c015af8d65a38e) | Gets the Transport Layer Security (TLS) client. (OSI Layer 4) |
| [`getHTTPClient`](#class_arduino_cellular_1aa1b4c3bbd14984d2a7ed1db7fa1ac930) | Gets the HTTP client for the specified server and port. |
| [`getHTTPSClient`](#class_arduino_cellular_1aeb2d1bff0405e92197c0de750cef87e0) | Gets the HTTPS client for the specified server and port. |
| [`getIPAddress`](#class_arduino_cellular_1aabf2ad2144827d34c3ba298b5f423344) | Gets the local IP address. |
| [`getSignalQuality`](#class_arduino_cellular_1aefdae9cb2b8c9f05130b09c18c3f245e) | Gets the signal quality. |
| [`setDebugStream`](#class_arduino_cellular_1aae2cacf5a5778293f0bd3312d2289327) | Sets the debug stream for [ArduinoCellular](#class_arduino_cellular). |

## Members

### `ArduinoCellular` <a id="class_arduino_cellular_1a96d1d9f3fbe80adc3d460b4364d47870" class="anchor"></a>

```cpp
ArduinoCellular()
```

Creates an instance of the [ArduinoCellular](#class_arduino_cellular) class.

<hr />

### `begin` <a id="class_arduino_cellular_1ad5ca7cf61f48c40569f41f3029d6516e" class="anchor"></a>

```cpp
void begin()
```

Initializes the modem. This function must be called before using any other functions in the library.

<hr />

### `unlockSIM` <a id="class_arduino_cellular_1aa0be2795ff7b23c39ecef90d9906bbdf" class="anchor"></a>

```cpp
bool unlockSIM(String pin)
```

Unlocks the SIM card using the specified PIN.

#### Parameters
* `pin` The SIM card PIN. 

#### Returns
True if the SIM card is unlocked, false otherwise.
<hr />

### `connect` <a id="class_arduino_cellular_1a7fb3c3e841b39c4faacef32cec6277b4" class="anchor"></a>

```cpp
bool connect(String apn, String username, String password)
```

Registers with the cellular network and connects to the Internet if the APN, GPRS username, and GPRS password are provided.

#### Parameters
* `apn` The Access Point Name. 

* `username` The APN username. 

* `password` The APN password. 

#### Returns
True if the connection is successful, false otherwise.
<hr />

### `isConnectedToOperator` <a id="class_arduino_cellular_1af7453ef90702e9042e2b4b18fa89db03" class="anchor"></a>

```cpp
bool isConnectedToOperator()
```

Checks if the modem is registered on the network.

#### Returns
True if the network is connected, false otherwise.
<hr />

### `isConnectedToInternet` <a id="class_arduino_cellular_1a6f8251e06de1810897b8bd8f8fb1b1a2" class="anchor"></a>

```cpp
bool isConnectedToInternet()
```

Checks if the GPRS network is connected.

#### Returns
True if the GPRS network is connected, false otherwise.
<hr />

### `enableGPS` <a id="class_arduino_cellular_1abe77a53e0eba6e8d62ba5db3bb6f5e92" class="anchor"></a>

```cpp
bool enableGPS(bool assisted)
```

Enables or disables the GPS functionality.

#### Parameters
* `assisted` True to enable assisted GPS, false to disable it. Assist GPS uses the network to get the GPS location faster, so cellular needs to be enabled. 

#### Returns
True if GPS was enabled successfully, false otherwise.
<hr />

### `getGPSLocation` <a id="class_arduino_cellular_1aee57a2eec5be06172b2fb7cd574d9106" class="anchor"></a>

```cpp
Location getGPSLocation(unsigned long timeout)
```

Gets the GPS location. (Blocking call)

#### Parameters
* `timeout` The timeout (In milliseconds) to wait for the GPS location. 

#### Returns
The GPS location. If the location is not retrieved, the latitude and longitude will be 0.0.
<hr />

### `getCellularTime` <a id="class_arduino_cellular_1a6b3ce5485badff582584d539e790aff4" class="anchor"></a>

```cpp
Time getCellularTime()
```

Gets the current time from the network.

#### Returns
The current time.
<hr />

### `getGPSTime` <a id="class_arduino_cellular_1a4aeb898c958e6eb001d606f0c7da8799" class="anchor"></a>

```cpp
Time getGPSTime()
```

Gets the current time from the GPS module.

#### Returns
The current time.
<hr />

### `sendSMS` <a id="class_arduino_cellular_1a371aef1318857f0863f443eaeabf4ac2" class="anchor"></a>

```cpp
void sendSMS(String number, String message)
```

Sends an [SMS](#class_s_m_s) message to the specified number.

#### Parameters
* `number` The phone number to send the [SMS](#class_s_m_s) to. 

* `message` The message to send.
<hr />

### `getReadSMS` <a id="class_arduino_cellular_1ae032c4e4cade6579a2c1edfe53d2ff2b" class="anchor"></a>

```cpp
std::vector< SMS > getReadSMS()
```

Gets the list of read [SMS](#class_s_m_s) messages.

#### Returns
A vector of [SMS](#class_s_m_s) messages.
<hr />

### `getUnreadSMS` <a id="class_arduino_cellular_1a212513654884058947a2a4d332f6ccfc" class="anchor"></a>

```cpp
std::vector< SMS > getUnreadSMS()
```

Gets the list of unread [SMS](#class_s_m_s) messages.

#### Returns
A vector of [SMS](#class_s_m_s) messages.
<hr />

### `deleteSMS` <a id="class_arduino_cellular_1abe4337f0bc8c486a076011309120ace1" class="anchor"></a>

```cpp
bool deleteSMS(uint16_t index)
```

Deletes an [SMS](#class_s_m_s) message at the specified index.

#### Parameters
* `index` The index of the [SMS](#class_s_m_s) message to delete. 

#### Returns
True if the [SMS](#class_s_m_s) message was successfully deleted, false otherwise.
<hr />

### `sendATCommand` <a id="class_arduino_cellular_1a58a3e3713af0c01ad1075a2509c6874d" class="anchor"></a>

```cpp
String sendATCommand(const char * command, unsigned long timeout)
```

Sends an AT command to the modem and waits for a response, then returns the response.

#### Parameters
* `command` The AT command to send. 

* `timeout` The timeout (In milliseconds) to wait for the response. Default is 1000ms. 

#### Returns
The response from the modem.
<hr />

### `sendUSSDCommand` <a id="class_arduino_cellular_1a6886aec5850836ea8e8f135d4e5632ab" class="anchor"></a>

```cpp
String sendUSSDCommand(const char * command)
```

Sends a USSD command to the network operator and waits for a response.

#### Parameters
* `command` The USSD command to send. 

#### Returns
The response from the network operator. (Note: The response may be an [SMS](#class_s_m_s) message or a USSD response)
<hr />

### `getNetworkClient` <a id="class_arduino_cellular_1acff92474af3bd819b62f132cf12f45ba" class="anchor"></a>

```cpp
TinyGsmClient getNetworkClient()
```

Gets the Network client. (OSI Layer 3)

#### Returns
The GSM client.
<hr />

### `getSecureNetworkClient` <a id="class_arduino_cellular_1a8b7486d1a682787588c015af8d65a38e" class="anchor"></a>

```cpp
BearSSLClient getSecureNetworkClient()
```

Gets the Transport Layer Security (TLS) client. (OSI Layer 4)

#### Returns
The GSM client.
<hr />

### `getHTTPClient` <a id="class_arduino_cellular_1aa1b4c3bbd14984d2a7ed1db7fa1ac930" class="anchor"></a>

```cpp
HttpClient getHTTPClient(const char * server, const int port)
```

Gets the HTTP client for the specified server and port.

#### Parameters
* `server` The server address. 

* `port` The server port. 

#### Returns
The HTTP client.
<hr />

### `getHTTPSClient` <a id="class_arduino_cellular_1aeb2d1bff0405e92197c0de750cef87e0" class="anchor"></a>

```cpp
HttpClient getHTTPSClient(const char * server, const int port)
```

Gets the HTTPS client for the specified server and port.

#### Parameters
* `server` The server address. 

* `port` The server port. 

#### Returns
The HTTPS client.
<hr />

### `getIPAddress` <a id="class_arduino_cellular_1aabf2ad2144827d34c3ba298b5f423344" class="anchor"></a>

```cpp
IPAddress getIPAddress()
```

Gets the local IP address.

#### Returns
The local IP address.
<hr />

### `getSignalQuality` <a id="class_arduino_cellular_1aefdae9cb2b8c9f05130b09c18c3f245e" class="anchor"></a>

```cpp
int getSignalQuality()
```

Gets the signal quality.

#### Returns
The signal quality.
<hr />

### `setDebugStream` <a id="class_arduino_cellular_1aae2cacf5a5778293f0bd3312d2289327" class="anchor"></a>

```cpp
void setDebugStream(Stream & stream)
```

Sets the debug stream for [ArduinoCellular](#class_arduino_cellular).

This function allows you to set the debug stream for [ArduinoCellular](#class_arduino_cellular). The debug stream is used to output debug messages and information.

#### Parameters
* `stream` A pointer to the Stream object that will be used as the debug stream.
<hr />

# class `ModemInterface` <a id="class_modem_interface" class="anchor"></a>

```cpp
class ModemInterface
  : public TinyGsmBG96
```

Represents the interface to the 4G modem module which extends the TinyGsmBG96 class.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`stream`](#class_modem_interface_1a4a8be6e54608e2cbd9704614b807b4b0) | The stream object for communication with the modem. |
| [`powerPin`](#class_modem_interface_1a26e5e7417ff90759520c89776fb0c7f2) | The pin number for controlling the power of the modem. |
| [`ModemInterface`](#class_modem_interface_1aa364cae2d778d717ca1c53a0e4ee8702) | Constructor for the [ModemInterface](#class_modem_interface) class. |
| [`init`](#class_modem_interface_1a2f8f381994be24bb821ace646f7fde9b) | Initializes the modem interface. (Overrides the init method in TinyGsmBG96) |

## Members

### `stream` <a id="class_modem_interface_1a4a8be6e54608e2cbd9704614b807b4b0" class="anchor"></a>

```cpp
Stream * stream
```

The stream object for communication with the modem.
<hr />

### `powerPin` <a id="class_modem_interface_1a26e5e7417ff90759520c89776fb0c7f2" class="anchor"></a>

```cpp
int powerPin
```

The pin number for controlling the power of the modem.
<hr />

### `ModemInterface` <a id="class_modem_interface_1aa364cae2d778d717ca1c53a0e4ee8702" class="anchor"></a>

```cpp
inline explicit ModemInterface(Stream & stream, int powerPin)
```

Constructor for the [ModemInterface](#class_modem_interface) class.

#### Parameters
* `stream` The stream object for communication with the modem. 

* `powerPin` The pin number for controlling the power of the modem.
<hr />

### `init` <a id="class_modem_interface_1a2f8f381994be24bb821ace646f7fde9b" class="anchor"></a>

```cpp
inline bool init(const char * pin)
```

Initializes the modem interface. (Overrides the init method in TinyGsmBG96)

#### Parameters
* `pin` The PIN code for the SIM card (optional). 

#### Returns
True if initialization is successful, false otherwise.
<hr />

# class `SMS` <a id="class_s_m_s" class="anchor"></a>

Represents an [SMS](#class_s_m_s) message.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`index`](#class_s_m_s_1a1d7df5242fd17e58cb5c7ef1f81472fb) | The index of the [SMS](#class_s_m_s) message. |
| [`sender`](#class_s_m_s_1aafb60a0ef09724cc5e3f659505c9dab3) | The phone number associated with the [SMS](#class_s_m_s). |
| [`message`](#class_s_m_s_1ad2f3aac08b66f78472b18727a653c7c4) | The content of the [SMS](#class_s_m_s) message. |
| [`timestamp`](#class_s_m_s_1a8f275bdda4111b2ecc95f269cec70940) | The timestamp when the [SMS](#class_s_m_s) was received. |
| [`SMS`](#class_s_m_s_1ac4a683a43558570b5a9cb3a92100c29e) | Default constructor for [SMS](#class_s_m_s). Initializes the number, message, and timestamp to empty values. |
| [`SMS`](#class_s_m_s_1abb10fd15a6e3d1f3b6a9bb24123d4e0a) | Constructor for [SMS](#class_s_m_s).  |

## Members

### `index` <a id="class_s_m_s_1a1d7df5242fd17e58cb5c7ef1f81472fb" class="anchor"></a>

```cpp
int16_t index
```

The index of the [SMS](#class_s_m_s) message.
<hr />

### `sender` <a id="class_s_m_s_1aafb60a0ef09724cc5e3f659505c9dab3" class="anchor"></a>

```cpp
String sender
```

The phone number associated with the [SMS](#class_s_m_s).
<hr />

### `message` <a id="class_s_m_s_1ad2f3aac08b66f78472b18727a653c7c4" class="anchor"></a>

```cpp
String message
```

The content of the [SMS](#class_s_m_s) message.
<hr />

### `timestamp` <a id="class_s_m_s_1a8f275bdda4111b2ecc95f269cec70940" class="anchor"></a>

```cpp
Time timestamp
```

The timestamp when the [SMS](#class_s_m_s) was received.
<hr />

### `SMS` <a id="class_s_m_s_1ac4a683a43558570b5a9cb3a92100c29e" class="anchor"></a>

```cpp
inline SMS()
```

Default constructor for [SMS](#class_s_m_s). Initializes the number, message, and timestamp to empty values.
<hr />

### `SMS` <a id="class_s_m_s_1abb10fd15a6e3d1f3b6a9bb24123d4e0a" class="anchor"></a>

```cpp
inline SMS(int16_t index, String sender, String message, Time timestamp)
```

Constructor for [SMS](#class_s_m_s). 
#### Parameters
* `index` The index of the [SMS](#class_s_m_s) message. 

* `sender` The phone number associated with the sender of the [SMS](#class_s_m_s). 

* `message` The content of the [SMS](#class_s_m_s) message. 

* `timestamp` The timestamp when the [SMS](#class_s_m_s) was received.
<hr />

# class `Time` <a id="class_time" class="anchor"></a>

Represents a point in time with year, month, day, hour, minute, second, and offset.

The [Time](#class_time) class provides methods to manipulate and retrieve information about a specific point in time. It supports conversion to and from ISO8601 format and UNIX timestamp.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Time`](#class_time_1a4409c3606f350cffec23e8398a751423) | Constructor for [Time](#class_time) class. Initializes the year, month, day, hour, minute, second, and offset to zero.  |
| [`Time`](#class_time_1a4245e409c7347d1d671858962c2ca3b5) | Default constructor for [Time](#class_time) class. Initializes the year, month, day, hour, minute, second, and offset to zero. |
| [`fromISO8601`](#class_time_1aeb356de4b6abb0a87d6fcbe71e3511b2) | Parses an ISO8601 formatted string and sets the time components accordingly.  |
| [`fromUNIXTimestamp`](#class_time_1a21e89ae360cfbf160325b43a1ed5d585) | Parses a UNIX timestamp and sets the time components accordingly.  |
| [`fromComponents`](#class_time_1a6882b5a11a79e6b366f4db9629e9e28f) | Initialises the time components with the given values.  |
| [`getISO8601`](#class_time_1aede6d5253f6b170cac35f414504a0b38) | Returns the time in ISO8601 format.  |
| [`getUNIXTimestampString`](#class_time_1a63d16642c348784ba87a02294ce80b1c) | Returns the time in UNIX timestamp format.  |
| [`getUNIXTimestamp`](#class_time_1adf9665ffec318732f4c47b9bbfd56fe9) | Returns the time in UNIX timestamp format.  |
| [`parseISO8601`](#class_time_1a1eb205ba41b7e6df4151a3b84250564d) | Returns the year component of the time.\  |
| [`parseUNIXTimestamp`](#class_time_1a07a0971f2d633c875f3bc312da188071) | Parses a UNIX timestamp and sets the time components accordingly.  |
| [`setYear`](#class_time_1a6d590de7818f9ab16bea1ff8e2a316dd) | Sets the year component of the time.  |
| [`setMonth`](#class_time_1aaa60fd08e34a3d4c106e7871c1fcbbdb) | Sets the month component of the time.  |
| [`setDay`](#class_time_1a31d352e8cf6a025b275e281689e100cd) | Sets the day component of the time.  |
| [`setHour`](#class_time_1ab77d5f9f5fa8582d23a70d418ab6a182) | Sets the hour component of the time.  |
| [`setMinute`](#class_time_1a9c53c93d10be3785c85449186beb6b6a) | Sets the minute component of the time.  |
| [`setSecond`](#class_time_1a599fc9b7c0babdc1cd630795965676e6) | Sets the second component of the time.  |
| [`setOffset`](#class_time_1a481c412a3a2ce55b948faeebf95b6019) | Sets the timezone offset of the time.  |
| [`getYear`](#class_time_1acd89f95ef13a7c182664af83e132f0b3) | Returns the year component of the time.  |
| [`getMonth`](#class_time_1aaee5a0c3f71f457265875940d3c0cbfb) | Returns the month component of the time.  |
| [`getDay`](#class_time_1a99f53a2fb08e1514298ad857f8d26313) | Returns the day component of the time.  |
| [`getHour`](#class_time_1ae0ce1e970c739d756282c95ebe458baf) | Returns the hour component of the time.  |
| [`getMinute`](#class_time_1ad231692eb5f467f28322d75a31bde810) | Returns the minute component of the time.  |
| [`getSecond`](#class_time_1a87251fcbf46ce6ccde1f274351a6a637) | Returns the second component of the time.  |
| [`getOffset`](#class_time_1ae5b2a5284affb0aa290e5efee7734364) | Returns the timezone offset of the time.  |

## Members

### `Time` <a id="class_time_1a4409c3606f350cffec23e8398a751423" class="anchor"></a>

```cpp
inline Time(int year, int month, int day, int hour, int minute, int second, int offset)
```

Constructor for [Time](#class_time) class. Initializes the year, month, day, hour, minute, second, and offset to zero. 
#### Parameters
* `year` The year component of the time. 

* `month` The month component of the time. 

* `day` The day component of the time. 

* `hour` The hour component of the time. 

* `minute` The minute component of the time. 

* `second` The second component of the time. 

* `offset` The timezone offset in hours (default is 0).
<hr />

### `Time` <a id="class_time_1a4245e409c7347d1d671858962c2ca3b5" class="anchor"></a>

```cpp
inline Time()
```

Default constructor for [Time](#class_time) class. Initializes the year, month, day, hour, minute, second, and offset to zero.
<hr />

### `fromISO8601` <a id="class_time_1aeb356de4b6abb0a87d6fcbe71e3511b2" class="anchor"></a>

```cpp
inline void fromISO8601(String ISO8601)
```

Parses an ISO8601 formatted string and sets the time components accordingly. 
#### Parameters
* `ISO8601` The ISO8601 formatted string to parse.
<hr />

### `fromUNIXTimestamp` <a id="class_time_1a21e89ae360cfbf160325b43a1ed5d585" class="anchor"></a>

```cpp
inline void fromUNIXTimestamp(String UNIXTimestamp)
```

Parses a UNIX timestamp and sets the time components accordingly. 
#### Parameters
* `UNIXTimestamp` The UNIX timestamp to parse.
<hr />

### `fromComponents` <a id="class_time_1a6882b5a11a79e6b366f4db9629e9e28f" class="anchor"></a>

```cpp
inline void fromComponents(int year, int month, int day, int hour, int minute, int second, int offset)
```

Initialises the time components with the given values. 
#### Parameters
* `year` The year component of the time. 

* `month` The month component of the time. 

* `day` The day component of the time. 

* `hour` The hour component of the time. 

* `minute` The minute component of the time. 

* `second` The second component of the time. 

* `offset` The timezone offset in hours (default is 0).
<hr />

### `getISO8601` <a id="class_time_1aede6d5253f6b170cac35f414504a0b38" class="anchor"></a>

```cpp
inline String getISO8601()
```

Returns the time in ISO8601 format. 
#### Returns
The time in ISO8601 format.
<hr />

### `getUNIXTimestampString` <a id="class_time_1a63d16642c348784ba87a02294ce80b1c" class="anchor"></a>

```cpp
inline String getUNIXTimestampString()
```

Returns the time in UNIX timestamp format. 
#### Returns
The time in UNIX timestamp format.
<hr />

### `getUNIXTimestamp` <a id="class_time_1adf9665ffec318732f4c47b9bbfd56fe9" class="anchor"></a>

```cpp
inline unsigned long getUNIXTimestamp()
```

Returns the time in UNIX timestamp format. 
#### Returns
The time in UNIX timestamp format.
<hr />

### `parseISO8601` <a id="class_time_1a1eb205ba41b7e6df4151a3b84250564d" class="anchor"></a>

```cpp
inline void parseISO8601(String iso8601)
```

Returns the year component of the time.\ 
#### Parameters
* `iso8601` The ISO8601 formatted string to parse.
<hr />

### `parseUNIXTimestamp` <a id="class_time_1a07a0971f2d633c875f3bc312da188071" class="anchor"></a>

```cpp
inline void parseUNIXTimestamp(long unixTimestamp)
```

Parses a UNIX timestamp and sets the time components accordingly. 
#### Parameters
* `unixTimestamp` The UNIX timestamp to parse.
<hr />

### `setYear` <a id="class_time_1a6d590de7818f9ab16bea1ff8e2a316dd" class="anchor"></a>

```cpp
inline void setYear(int year)
```

Sets the year component of the time. 
#### Parameters
* `year` The year component of the time.
<hr />

### `setMonth` <a id="class_time_1aaa60fd08e34a3d4c106e7871c1fcbbdb" class="anchor"></a>

```cpp
inline void setMonth(int month)
```

Sets the month component of the time. 
#### Parameters
* `month` The month component of the time.
<hr />

### `setDay` <a id="class_time_1a31d352e8cf6a025b275e281689e100cd" class="anchor"></a>

```cpp
inline void setDay(int day)
```

Sets the day component of the time. 
#### Parameters
* `day` The day component of the time.
<hr />

### `setHour` <a id="class_time_1ab77d5f9f5fa8582d23a70d418ab6a182" class="anchor"></a>

```cpp
inline void setHour(int hour)
```

Sets the hour component of the time. 
#### Parameters
* `hour` The hour component of the time.
<hr />

### `setMinute` <a id="class_time_1a9c53c93d10be3785c85449186beb6b6a" class="anchor"></a>

```cpp
inline void setMinute(int minute)
```

Sets the minute component of the time. 
#### Parameters
* `minute` The minute component of the time.
<hr />

### `setSecond` <a id="class_time_1a599fc9b7c0babdc1cd630795965676e6" class="anchor"></a>

```cpp
inline void setSecond(int second)
```

Sets the second component of the time. 
#### Parameters
* `second` The second component of the time.
<hr />

### `setOffset` <a id="class_time_1a481c412a3a2ce55b948faeebf95b6019" class="anchor"></a>

```cpp
inline void setOffset(int offset)
```

Sets the timezone offset of the time. 
#### Parameters
* `offset` The timezone offset of the time.
<hr />

### `getYear` <a id="class_time_1acd89f95ef13a7c182664af83e132f0b3" class="anchor"></a>

```cpp
inline int getYear()
```

Returns the year component of the time. 
#### Returns
The year component of the time.
<hr />

### `getMonth` <a id="class_time_1aaee5a0c3f71f457265875940d3c0cbfb" class="anchor"></a>

```cpp
inline int getMonth()
```

Returns the month component of the time. 
#### Returns
The month component of the time.
<hr />

### `getDay` <a id="class_time_1a99f53a2fb08e1514298ad857f8d26313" class="anchor"></a>

```cpp
inline int getDay()
```

Returns the day component of the time. 
#### Returns
The day component of the time.
<hr />

### `getHour` <a id="class_time_1ae0ce1e970c739d756282c95ebe458baf" class="anchor"></a>

```cpp
inline int getHour()
```

Returns the hour component of the time. 
#### Returns
The hour component of the time.
<hr />

### `getMinute` <a id="class_time_1ad231692eb5f467f28322d75a31bde810" class="anchor"></a>

```cpp
inline int getMinute()
```

Returns the minute component of the time. 
#### Returns
The minute component of the time.
<hr />

### `getSecond` <a id="class_time_1a87251fcbf46ce6ccde1f274351a6a637" class="anchor"></a>

```cpp
inline int getSecond()
```

Returns the second component of the time. 
#### Returns
The second component of the time.
<hr />

### `getOffset` <a id="class_time_1ae5b2a5284affb0aa290e5efee7734364" class="anchor"></a>

```cpp
inline int getOffset()
```

Returns the timezone offset of the time. 
#### Returns
The timezone offset of the time.
<hr />

# struct `Location` <a id="struct_location" class="anchor"></a>

Represents a geographic location with latitude and longitude coordinates.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`latitude`](#struct_location_1a194bf3edf130d2a4bf281720e7d01409) | The latitude coordinate of the location. |
| [`longitude`](#struct_location_1ae36169ef2dfcad63e26b492a6a82b990) | The longitude coordinate of the location. |

## Members

### `latitude` <a id="struct_location_1a194bf3edf130d2a4bf281720e7d01409" class="anchor"></a>

```cpp
float latitude
```

The latitude coordinate of the location.
<hr />

### `longitude` <a id="struct_location_1ae36169ef2dfcad63e26b492a6a82b990" class="anchor"></a>

```cpp
float longitude
```

The longitude coordinate of the location.
<hr />

