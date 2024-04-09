
#include <Arduino.h>
#include "ArduinoCellular.h"
#include <ArduinoHttpClient.h>
#include "arduino_secrets.h"


const char server[]   = "example.com";
const char resource[] = "/";
const int  port       = 443;

ArduinoCellular cellular = ArduinoCellular();
HttpClient http = cellular.getHTTPSClient(server, port);

void setup(){
    Serial.begin(115200);
    while (!Serial);
 
    cellular.begin();
    cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD, SECRET_PINNUMBER);
}

void loop()
{
  Serial.println("Making GET request...");

  http.get(resource);

  int status_code = http.responseStatusCode();
  String response = http.responseBody();

  Serial.print("Status code: ");
  Serial.println(status_code);
  Serial.print("Response: ");
  Serial.println(response);

  http.stop();

  delay(5000);
}