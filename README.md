# 📡 Arduino Cellular 

[![Arduino Lint](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/arduino-lint.yml) [![Compile Examples](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/spell-check.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/spell-check.yml) [![Sync Labels](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/sync-labels.yml) [![Render Documentation](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/render-documentation.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_Cellular/actions/workflows/render-documentation.yml)


This library provides a toolkit for interacting with the official Arduino 4G Modules ([EMEA](https://store.arduino.cc/products/4g-module-emea) and [Global Versions](https://store.arduino.cc/products/4g-module-global)). 
It allows you to connect to the internet, send and receive SMS messages, and get location from the cellular network or GPS. 

## Examples
* [DeleteSMS](examples/DeleteSMS) - Example that shows how to delete SMS.
* [GetLocation](examples/GetLocation) - Shows how to get the current GPS location.
* [GetTime](examples/GetTime) - Use GPS to acquire the time of the device.
* [HTTPClient](examples/HTTPClient) - Example of using this library together with [ArduinoHttpClient]() to connect to a web server
* [HTTPSClient](examples/HTTPSClient) - Example of using this library together with [ArduinoHttpClient]() that uses [BearSSL]() under the hood to create a secure connection to a web server
* [ModemTerminal](examples/ModemTerminal) - A handy example for debugging and Testing AT commands 
* [ReceiveSMS](examples/ReceiveSMS) - Example for the SMS sending and receiving functionality 
* [SendSMS](examples/SendSMS) - Shows how to send an SMS

## ✨ Features
* Fast 4G connection to the internet
* Secure SSL connections with BearSSL
* Get location using GPS or GSM
* Synchronise time with the cell provider
* Send and Receive SMS Messages

## 👀 Instructions
1. Insert a nano SIM card in the **PCIE_SIM** connector on the [Arduino Portenta Mid Carrier](https://docs.arduino.cc/hardware/portenta-mid-carrier/).
2. Connect the Serial (J17) to the adjacent PCIE Breakout Pins (J16) with jumpers included in the Portenta Mid Carrier:
    | Serial 1 (J17)         | PCIE Breakout (J16) |
    |------------------------|---------------------|
    | RX (Pin 1)             | CK_N (Pin 1)        |
    | TX (Pin 2)             | CK_P (Pin 3)        |
    | RTS (Pin 3)            | RX_N (Pin 5)        |
    | CTS (Pin 4)            | RX_P (Pin 7)        |
    | mPCIE_GPIO_RST (Pin 5) | mPCIE_RST (Pin 9)   |
    
    <img src="./docs/Arduino_Portenta_Mid_Carrier_PortentaH7_and_PCIEBreakout_Pins.png" alt="Portenta Mid Carrier with Portenta H7 and PCIE Breakout Pin Configuration" width="400"/>

3. On J9, using jumpers connect the following pins:
    | Source (J9)      | Buck Converter (J9) |
    |------------------|---------------------|
    | 3V3 PCIE (Pin 1) | 3V3 BUCK (Pin 3)    |
    | OUT VCC (Pin 2)  | 3V3 BUCK EN (Pin 4) |

    <img src="./docs/Arduino_Portenta_Mid_Carrier_SIM_and_Power_Pins.png" alt="Portenta Mid Carrier SIM and Power Pin Configuration" width="400"/>

4. Insert the [Arduino Pro 4G Module](https://docs.arduino.cc/hardware/pro-4g-module) in the Arduino Portenta Mid Carrier.

5. Screw one black post with a white nut from under the Portenta Mid Carrier. Using another black post, screw the board to the post. Place two washers on top, and one underneath the Pro 4G Module. So that the board is fixed to the post snuggly and horizontally.

6. (EMEA and GNSS variants) Connect the cellular antenna (flat antenna in [Arduino Pro 4G Module Antennas Kit](https://store.arduino.cc/products/4g-module-antenna)) to the left microUFL connector marked MAIN.

7. (PRO 4G GNSS only) Connect the GNSS antenna (square antenna in [Arduino Pro 4G Module Antennas Kit](https://store.arduino.cc/products/4g-module-antenna)) to the middle microUFL connector marked GNSS.

    <img src="./docs/Arduino_Portenta_Mid_Carrier_GNSS_with_GNSS_MAIN_Antennas.png" alt="Portenta Mid Carrier with Pro 4G Module GNSS with both the MAIN and GNSS antennas connected" width="400"/>

8. Insert a [Portenta C33](https://docs.arduino.cc/hardware/portenta-c33) or [Portenta H7](https://docs.arduino.cc/hardware/portenta-h7) Board into the marked location. The USB-C port of the Portenta board should be next to the Ethernet port on the Mid Carrier.

9.  Insert a Terminal Block 2-pin > DC female adapter into the screw terminal (J4). Ensure that the negative (-) pin is connected to GND.

    <img src="./docs/Arduino_Portenta_Mid_Carrier_PortentaC33_4GPRO_GNSS_All_Antennas.png" alt="Portenta Mid Carrier with Portenta C33 and Pro 4G Module GNSS with all antennas connected" width="400"/>

10. Use a 5V adapter that can output at least 3A and connect it to the DC female adapter.

11. Connect the Portenta board to your computer using a USB-C cable.

12. Install the `Arduino_Cellular` library and its dependencies

13. Obtain the APN (Access Point Name) settings from your network operator and add them to the `arduino_secrets.h` file for each sketch. For example:
    ```cpp
    #define SECRET_PINNUMBER     "" // replace with your SIM card PIN
    #define SECRET_GPRS_APN      "services.telenor.se" // replace with your GPRS APN
    #define SECRET_GPRS_LOGIN    ""    // replace with your GPRS login
    #define SECRET_GPRS_PASSWORD "" // replace with your GPRS password
    ```  

14. Upload sketch to the Portenta board. Enjoy!


## 📖 Documentation

For more information about this library please read the documentation [here](./docs).
