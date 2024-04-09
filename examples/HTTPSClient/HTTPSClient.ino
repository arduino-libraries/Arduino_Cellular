
#include <Arduino.h>
#include "ArduinoCellular.h"
#include <ArduinoHttpClient.h>
#include "arduino_secrets.h"

const char server[]   = "example.com";
const char resource[] = "/";
const int  port       = 443;

ArduinoCellular cellular = ArduinoCellular();
HttpClient client = cellular.getHTTPSClient(server, port);

void setup(){
    Serial.begin(115200);
    while (!Serial);
 
    cellular.begin();
    cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD, SECRET_PINNUMBER);
}

void loop(){
  Serial.println("Making GET request...");

  client.get(resource);

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  client.stop();
  delay(5000);
}
