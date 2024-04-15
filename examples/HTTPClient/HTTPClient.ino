/**
 * This example demonstrates how to make a HTTP GET request using 
 * the ArduinoHttpClient library and the ArduinoCellular library.
 * 
 * Instructions:
 * 1. Insert a SIM card with or without PIN code in the Arduino Pro 4G Module.
 * 2. Provide sufficient power to the Arduino Pro 4G Module. Ideally, use a 5V power supply
 *    with a current rating of at least 2A and connect it to the VIN and GND pins.
 * 3. Specify the APN, login, and password for your cellular network provider.
 * 4. Upload the sketch to the connected Arduino board.
 * 5. Open the serial monitor to view the output.
 * 
 * Initial author: Cristian Dragomir
*/

#define ARDUINO_CELLULAR_DEBUG

#include "ArduinoCellular.h"
#include "arduino_secrets.h"

const char server[]   = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";
const int  port       = 80;

ArduinoCellular cellular = ArduinoCellular();
HttpClient client = cellular.getHTTPClient(server, port);

void getResource(){

  Serial.println("Making GET request...");

  client.get(resource);

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  client.stop();
}

void setup(){
    Serial.begin(115200);
    while (!Serial);
    // cellular.setDebugStream(Serial); // Uncomment this line to enable debug output
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

    getResource();
}

void loop(){}
