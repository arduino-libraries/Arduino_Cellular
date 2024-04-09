#define ARDUINO_CELLULAR_DEBUG

#include "ArduinoCellular.h"
#include "arduino_secrets.h"


const char server[]   = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";
const int  port       = 80;

ArduinoCellular cellular = ArduinoCellular();
HttpClient http = cellular.getHTTPClient(server, port);


void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.begin();
    cellular.connect(SECRET_GPRS_APN, SECRET_GPRS_LOGIN, SECRET_GPRS_PASSWORD, SECRET_PINNUMBER);
}

void loop(){

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

