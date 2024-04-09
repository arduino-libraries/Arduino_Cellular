# Arduino 4G Module Library

This library provides a toolkit for interacting with the official Arduino 4G Modules. It allows you to connect to the internet, send and receive SMS messages, and get location from the cellular network or GPS. 

## Examples
* [examples/HTTPClient]() - Example of using this library together with [HttpClient]() to connect to a web server
* [examples/HTTPClient]() - Example of using this library together with [HttpClient]() that uses [BearSSL]() under the hood to create a secure connection to a web server
* [examples/SMSReceive]() - Example for the SMS sending and receiving functionality 
* [examples/TimeAndLocation]() - Use GPS, or Cellular to aquire the location and time of the device. 
* [examples/ModemTerminal]() - A handy example for debugging and Testing AT commands 

## Features
* Fast 4G connection to the internet
* Secure SSL connections with BearSSL
* Get location using GPS or GSM
* Synchronise time with the cell provider
* Send and Receive SMS Messages

## Instructions
1. Insert your Arduino 4G module to the Arduino Portenta Mid Carrier
2. Insert a valid SIM card either on the back of the Arduino 4G miniPCI board, or the **PCIE_SIM** connector on the Portenta Mid Carrier
3. Connect the 6 **SERIAL1** header pins to their corresponding pins on the **PCIE_BREAKOUT** header using jumpers
![](https://raw.githubusercontent.com/arduino-libraries/Arduino_Cellular/main/extras/connection_img/header.jpg?token=GHSAT0AAAAAACNPRJPUBHNVP3J3KMRPUULUZQVDLKQ)
4. Connect the **3V3 PCIE** pin to the **3V3 Buck** 
![](https://raw.githubusercontent.com/arduino-libraries/Arduino_Cellular/main/extras/connection_img/buck.jpg?token=GHSAT0AAAAAACNPRJPUBUCALG2FUCDZ7AVCZQVDLJA)
5. Connect external power to the Mid Carrier, via the **VIN** (5-12V) because modem use a lot of power when connecting or getting a GPS location. Make sure your supply can handle around 3A. 
6. Get the APN settings from your network operator and add them to the "ArduinoSecrets.h" file for each sketch
```c
const char apn[]      = "live.vodafone.com";
const char gprsUser[] = "live";
const char gprsPass[] = "";
```
7. Install the library and it's dependencies 
8. Enjoy


