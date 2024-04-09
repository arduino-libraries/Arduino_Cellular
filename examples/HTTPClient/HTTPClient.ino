#define ARDUINO_CELLULAR_DEBUG

#include "ArduinoCellular.h"


const char apn[]      = "live.vodafone.com";
const char gprsUser[] = "live";
const char gprsPass[] = "";

const char server[]   = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";
const int  port       = 80;

ArduinoCellular cellular = ArduinoCellular();
//TinyGsmClient networkClient = cellular.getNetworkClient();
//HttpClient http = HttpClient(networkClient, server, port);
 HttpClient http = cellular.getHTTPClient(server, port);


void setup(){
    Serial.begin(115200);
    while (!Serial);
    cellular.begin();
    cellular.connect(apn, gprsUser, gprsPass);
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

