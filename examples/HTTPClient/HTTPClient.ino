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
