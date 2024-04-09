#include "ArduinoCellular.h"

unsigned long ArduinoCellular::getTime() {
    int year, month, day, hour, minute, second;
    float tz;
    modem.getNetworkTime(&year, &month, &day, &hour, &minute, &second, &tz);
    return Time(year, month, day, hour, minute, second).getUNIXTimestamp();
}

ArduinoCellular::ArduinoCellular() {
    
}

void ArduinoCellular::begin() {
    // set sim slot
    modem.init();

 
    String modemInfo = this ->sendATCommand("I");
    if(modemInfo.indexOf("EC200A") > 0){
        this->model = ModemModel::EC200;
    } else if (modemInfo.indexOf("EG95") > 0){
        this->model = ModemModel::EG95;
    } else {
        this->model = ModemModel::Unsupported;
    }

    // Set GSM module to text mode
    modem.sendAT("+CMGF=1");
    modem.waitResponse();

    modem.sendAT(GF("+CSCS=\"GSM\""));
    modem.waitResponse();

    // Send intrerupt when SMS has been received
    modem.sendAT("+CNMI=2,1,0,0,0");
    modem.waitResponse();


    ArduinoBearSSL.onGetTime(ArduinoCellular::getTime);

}

bool ArduinoCellular::connect(const char * apn, const char * gprsUser, const char * gprsPass){
    SimStatus simStatus = getSimStatus();
    if(simStatus == SimStatus::SIM_LOCKED) {
       unlockSIM("1234");
    }

    simStatus = getSimStatus();
    if(simStatus == SimStatus::SIM_READY) {
        if(awaitNetworkRegistration()){
            if(connectToGPRS(apn, gprsUser, gprsPass)){
                Serial.println("Setting DNS...");
                Serial.println(this->sendATCommand("+QIDNSCFG=1,\"8.8.8.8\",\"8.8.4.4\""));
                return true;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}


Location ArduinoCellular::getGPSLocation(unsigned long timeout){
    if (model == ModemModel::EG95){
        float latitude = 0.00000;
        float longitude = 0.00000;
        unsigned long startTime = millis();

        while((latitude == 0.00000 || longitude == 0.00000) && (millis() - startTime < timeout)) {
            modem.getGPS(&latitude, &longitude);
            delay(1000);
        }
        
        Location loc;
        loc.latitude = latitude;
        loc.longitude = longitude;

        return loc;
    } else {
        Serial.println("Unsupported modem model");
        return Location();
    }
}

Time ArduinoCellular::getGPSTime(){
    int year, month, day, hour, minute, second;
    modem.getGPSTime(&year, &month, &day, &hour, &minute, &second);
    return Time(year, month, day, hour, minute, second);
}

Time ArduinoCellular::getCellularTime(){
    int year, month, day, hour, minute, second;
    float tz;
    modem.getNetworkTime(&year, &month, &day, &hour, &minute, &second, &tz);
    return Time(year, month, day, hour, minute, second);
}


void ArduinoCellular::sendSMS(String number, String message){
    modem.sendAT(GF("+CMGS=\""), number, GF("\""));
    if (modem.waitResponse(GF(">")) != 1) { }
    modem.stream->print(message);  // Actually send the message
    modem.stream->write(static_cast<char>(0x1A));  // Terminate the message
    modem.stream->flush();
    Serial.println(modem.waitResponse(10000L));
  }


void ArduinoCellular::getConnectionStatus(){

   IPAddress local = modem.localIP();
   Serial.print("Local IP:"); Serial.println(local.toString());
   Serial.println("Signal quality:"); Serial.println(modem.getSignalQuality());
}

TinyGsmClient ArduinoCellular::getNetworkClient(){
    return TinyGsmClient(modem);
}

HttpClient ArduinoCellular::getHTTPClient(const char * server, const int port){
    return HttpClient(* new TinyGsmClient(modem), server, port);
}

HttpClient ArduinoCellular::getHTTPSClient(const char * server, const int port){
    return HttpClient(* new BearSSLClient(* new TinyGsmClient(modem)), server, port);
}

bool ArduinoCellular::isConnectedToOperator(){
    return modem.isNetworkConnected();
}

bool ArduinoCellular::connectToGPRS(const char * apn, const char * gprsUser, const char * gprsPass){
    Serial.print(F("Connecting to 4G network..."));
    while(!modem.gprsConnect(apn, gprsUser, gprsPass)) {
        Serial.print(".");
        delay(2000);
    }
    return true;
}

bool ArduinoCellular::isConnectedToInternet(){
    return modem.isGprsConnected();
}

SimStatus ArduinoCellular::getSimStatus(){
    int simStatus = modem.getSimStatus();
    Serial.println("SIM Status: " + String(simStatus));

    if (modem.getSimStatus() == 0) {
        return SimStatus::SIM_ERROR;
    } else if (modem.getSimStatus() == 1) {
        return SimStatus::SIM_READY;
    } else if (modem.getSimStatus() == 2) {
        return SimStatus::SIM_LOCKED;
    } else if (modem.getSimStatus() == 3) {
        return SimStatus::SIM_ANTITHEFT_LOCKED;
    } else {
        return SimStatus::SIM_ERROR;
    }
}

bool ArduinoCellular::unlockSIM(const char * pin){
    Serial.println("Unlocking SIM...");
    modem.simUnlock(pin); 
}

bool ArduinoCellular::awaitNetworkRegistration(){
    Serial.print("Waiting for network registration...");
    while (!modem.waitForNetwork()) {
        Serial.println(".");
        delay(2000);
    } 
    return true;
}

bool ArduinoCellular::enableGPS(bool assisted){
    Serial.println("Enabling GPS...");
    if(assisted){
        sendATCommand("AT+QGPSCFG=\"agpsposmode\",33488767");
    } else {
        sendATCommand("AT+QGPSCFG=\"agpsposmode\",8388608");
    }

    //modem.sendAT(GF("+UTIME=1,1"));
    //modem.waitResponse();
    //modem.sendAT(GF("+UGPIOC=23,0,1"));

    //modem.waitResponse();

    modem.enableGPS();
    //delay(10000);
    // TODO: ^ move this to the sketch 
}

String ArduinoCellular::sendATCommand( char * command, unsigned long timeout){
    String resp;
    modem.sendAT(const_cast<char *>(command)); 
    modem.waitResponse(timeout, resp);
    return resp;
}



Time parseTimestamp(const String &timestampStr) {
  int hour, minute, second, day, month, year, offset;
  
  int commaIndex = timestampStr.indexOf(',');
  String date = timestampStr.substring(0, commaIndex);
  String time = timestampStr.substring(commaIndex + 1, timestampStr.indexOf('+'));
  String offsetStr = timestampStr.substring(timestampStr.indexOf('+') + 1);

  int firstSlashIndex = date.indexOf('/');
  int secondSlashIndex = date.lastIndexOf('/');
  day = date.substring(0, firstSlashIndex).toInt();
  month = date.substring(firstSlashIndex + 1, secondSlashIndex).toInt();
  year = date.substring(secondSlashIndex + 1).toInt() + 2000;

  int firstColonIndex = time.indexOf(':');
  int secondColonIndex = time.lastIndexOf(':');
  hour = time.substring(0, firstColonIndex).toInt();
  minute = time.substring(firstColonIndex + 1, secondColonIndex).toInt();
  second = time.substring(secondColonIndex + 1).toInt();

  offset = offsetStr.toInt();

  return Time(year, month, day, hour, minute, second, offset);
}
// Parses a single SMS entry from the data
SMS parseSMSEntry(const String& entry) {
  SMS sms;
  int firstQuoteIndex = entry.indexOf('"');
  int secondQuoteIndex = entry.indexOf('"', firstQuoteIndex + 1);
  int thirdQuoteIndex = entry.indexOf('"', secondQuoteIndex + 1);
  int fourthQuoteIndex = entry.indexOf('"', thirdQuoteIndex + 1);
  int commaIndexBeforeTimestamp = entry.lastIndexOf(',', entry.lastIndexOf(',') - 1);

  // Extracting number and raw timestamp
  sms.number = entry.substring(thirdQuoteIndex + 1, fourthQuoteIndex);
  String rawTimestamp = entry.substring(commaIndexBeforeTimestamp + 2, entry.indexOf('+', commaIndexBeforeTimestamp) + 3);

  // Parse the timestamp
  sms.timestamp = parseTimestamp(rawTimestamp);

  // Extracting the message content
  int messageStartIndex = entry.indexOf('\n') + 1; // Assuming message starts after the newline
  if (messageStartIndex != -1) {
      sms.message = entry.substring(messageStartIndex, entry.indexOf('\n'));
  }

  return sms;
}

// Splits the entire message string into individual SMS entries and parses them
std::vector<SMS> parseSMSData(const String& data) {
  std::vector<SMS> smsList;
  int start = 0;
  int end = data.indexOf("\n+CMGL: ", start);
  
  while (end != -1) {
    String entry = data.substring(start, end);
    smsList.push_back(parseSMSEntry(entry));
    start = end + 1;
    end = data.indexOf("\n+CMGL: ", start);
  }
  // Adding the last SMS entry, if there's any remaining part
  if (start < data.length()) {
    smsList.push_back(parseSMSEntry(data.substring(start)));
  }

  smsList.erase(smsList.begin());
  return smsList;
}


std::vector<SMS> ArduinoCellular::getReadSMS(){
    String rawMessages = sendATCommand("+CMGL=\"REC READ\"");
    if(rawMessages.indexOf("OK") == -1){
        return std::vector<SMS>();
    } else if (rawMessages.indexOf("ERROR") != -1){
        return std::vector<SMS>();
    } else {
        return parseSMSData(rawMessages);
    }
}

std::vector<SMS> ArduinoCellular::getUnreadSMS(){
    String rawMessages = sendATCommand("+CMGL=\"REC UNREAD\"");
    if(rawMessages.indexOf("OK") == -1){
        return std::vector<SMS>();
    } else if (rawMessages.indexOf("ERROR") != -1){
        return std::vector<SMS>();
    } else {
        return parseSMSData(rawMessages);
    }
}