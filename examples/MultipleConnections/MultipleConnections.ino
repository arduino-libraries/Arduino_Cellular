/**
 * This example shows how to use the connection management features of the ArduinoCellular library
 * to maintain multiple HTTP and HTTPS clients.
 * This is useful if e.g. you want to use ArduinoIoTCloud or other services that require
 * a dedicated client while making custom HTTP requests to other servers.
 *
 * Instructions:
 * 1. Insert a SIM card with or without PIN code in the Arduino Pro 4G Module.
 * 2. Provide sufficient power to the Arduino Pro 4G Module. Ideally, use a 5V power supply
 *   with a current rating of at least 2A and connect it to the VIN and GND pins.
 * 3. Specify the APN, login, and password for your cellular network provider.
 * 4. Upload the sketch to the connected Arduino board.
 * 5. Open the serial monitor to view the output.
 * 
 * Initial author: Sebastian Romero
*/

#include <Arduino.h>
#include "ArduinoCellular.h"
#include <ArduinoHttpClient.h>

#define SECRET_PINNUMBER ""
#define SECRET_GPRS_LOGIN ""
#define SECRET_GPRS_APN "gprs.swisscom.ch"
#define SECRET_GPRS_PASSWORD ""

constexpr int  SSL_PORT = 443;

ArduinoCellular cellular = ArduinoCellular();

void getResource(HttpClient &client, const char *resource) {
    Serial.println("Making GET request...");
    client.get(resource);
    int statusCode = client.responseStatusCode();   

    if (statusCode < 0) {
        Serial.print("Error Response Code: ");
        Serial.println(statusCode);
        return;
    }
    Serial.print("Response: ");
    Serial.println(client.responseBody()); 
}


void setup(){
    Serial.begin(115200);
    while (!Serial);
 
    cellular.begin();

    if(String(SECRET_PINNUMBER).length() > 0 && !cellular.unlockSIM(SECRET_PINNUMBER)){
        Serial.println("Failed to unlock SIM card.");
        while(true); // Stop here
    }

    Serial.println("Connecting...");
    if(!cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD)){
        Serial.println("Failed to connect to the network.");
        while(true); // Stop here
    }
    Serial.println("Connected!");

    HttpClient client1 = cellular.getHTTPSClient("vsh.pp.ua", SSL_PORT);
    HttpClient client2 = cellular.getHTTPSClient("wttr.in", SSL_PORT);
    Serial.print("Managed client count: ");
    Serial.println(cellular.getManagedClientCount());
    
    getResource(client1, "/TinyGSM/logo.txt");
    getResource(client2, "/?format=3");
    client1.stop();
    client2.stop();
    cellular.cleanup(); // Clean up connections after use

    Serial.print("Managed client count: ");
    Serial.println(cellular.getManagedClientCount());
}

void loop(){}
