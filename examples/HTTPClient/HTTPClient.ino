#define ARDUINO_CELLULAR_DEBUG

#include "ArduinoCellular.h"
#include "arduino_secrets.h"

const char server[]   = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";
const int  port       = 80;

ArduinoCellular cellular = ArduinoCellular();
HttpClient client = cellular.getHTTPClient(server, port);

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
