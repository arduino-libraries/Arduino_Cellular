

#include "ArduinoCellular.h"

#if defined(ARDUINO_ARCH_MBED)
  #include "Watchdog.h"
#endif

unsigned long ArduinoCellular::getTime() {
    int year, month, day, hour, minute, second;
    float tz;
    Modem.getNetworkTime(&year, &month, &day, &hour, &minute, &second, &tz);
    return Time(year, month, day, hour, minute, second).getUNIXTimestamp();
}

ArduinoCellular::ArduinoCellular() {
}

ArduinoCellular::~ArduinoCellular() {
    cleanup();
}

void ArduinoCellular::begin() {
    Modem.init();
 
    String modemInfo = this ->sendATCommand("I");
    if(modemInfo.indexOf("EC200A") > 0){
        this->model = ModemModel::EC200;
    } else if (modemInfo.indexOf("EG25") > 0){
        this->model = ModemModel::EG25;
    } else {
        this->model = ModemModel::Unsupported;
    }

    // Set GSM module to text mode
    Modem.sendAT("+CMGF=1");
    Modem.waitResponse();

    Modem.sendAT(GF("+CSCS=\"GSM\""));
    Modem.waitResponse();

    // Send intrerupt when SMS has been received
    Modem.sendAT("+CNMI=2,1,0,0,0");
    Modem.waitResponse();

#if defined(ARDUINO_CELLULAR_BEARSSL)
    ArduinoBearSSL.onGetTime(ArduinoCellular::getTime);
#endif

}

bool ArduinoCellular::connect(String apn, bool waitForever) {
    connect(apn,String(""),String(""), waitForever);
}


bool ArduinoCellular::connect(String apn, String username, String password, bool waitForever){
    SimStatus simStatus = getSimStatus();

    if(simStatus == SimStatus::SIM_LOCKED){
        if(this->debugStream != nullptr){
            this->debugStream->println("SIM locked, cannot connect to network.");
        }
       
       return false;
    }

    if(simStatus != SimStatus::SIM_READY) {
        if(this->debugStream != nullptr){
            this->debugStream->println("SIM not ready, cannot connect to network.");
        }
        return false;
    }

    if(!awaitNetworkRegistration(waitForever)){
        return false;
    }

    if(apn.length() == 0){
        if(this->debugStream != nullptr){
            this->debugStream->println("No APN specified, not connecting to GPRS");
        }
        return true;       
    }

    if(connectToGPRS(apn.c_str(), username.c_str(), password.c_str())){
        auto response = this->sendATCommand("+QIDNSCFG=1,\"8.8.8.8\",\"8.8.4.4\"");
        
        if(response.indexOf("OK") != -1){
            return true;
        } else {
            if(this->debugStream != nullptr){
                this->debugStream->println("Failed to set DNS.");
            }
            return false;
        }

    }
    
    return false;
}


Geolocation ArduinoCellular::getGPSLocation(unsigned long timeout){
    if (model == ModemModel::EG25){
        float latitude = 0.00000;
        float longitude = 0.00000;
        unsigned long startTime = millis();

        while((latitude == 0.00000 || longitude == 0.00000) && (millis() - startTime < timeout)) {
            Modem.getGPS(&latitude, &longitude);
            delay(1000);
        }
        
        Geolocation loc;
        loc.latitude = latitude;
        loc.longitude = longitude;

        return loc;
    } else {
        if(this->debugStream != nullptr){
            this->debugStream->println("Unsupported modem model");
        }
        return Geolocation();
    }
}

Time ArduinoCellular::getGPSTime(){
    int year, month, day, hour, minute, second;
    Modem.getGPSTime(&year, &month, &day, &hour, &minute, &second);
    return Time(year, month, day, hour, minute, second);
}

Time ArduinoCellular::getCellularTime(){
    int year = 1970;
    int month = 1;
    int day = 1;
    int hour = 0;
    int minute = 0;
    int second = 0;
    float tz;
    if (Modem.NTPServerSync() == 0) {
      Modem.getNetworkTime(&year, &month, &day, &hour, &minute, &second, &tz);
    }
    return Time(year, month, day, hour, minute, second);
}


void ArduinoCellular::sendSMS(String number, String message){
    Modem.sendAT("+CMGF=1"); 
    Modem.waitResponse(1000);
    Modem.sendAT(GF("+CMGS=\""), number, GF("\""));
    if (Modem.waitResponse(GF(">")) != 1) { }
    Modem.stream->print(message);  // Actually send the message
    Modem.stream->write(static_cast<char>(0x1A));  // Terminate the message
    Modem.stream->flush();
    auto response = Modem.waitResponse(10000L);
    
    if(this->debugStream != nullptr){
        this->debugStream->println("Response: " + String(response));
    }
  }


IPAddress ArduinoCellular::getIPAddress(){
    return Modem.localIP();
}

int ArduinoCellular::getSignalQuality(){
    return Modem.getSignalQuality();
}

TinyGsmClient ArduinoCellular::getNetworkClient(){
    return ManagedTinyGsmClient(Modem);
}

HttpClient ArduinoCellular::getHTTPClient(const char * server, const int port){
    return HttpClient(* new ManagedTinyGsmClient(Modem), server, port);
}

#if defined(ARDUINO_CELLULAR_BEARSSL)
HttpClient ArduinoCellular::getHTTPSClient(const char * server, const int port){
    auto gsmClient = std::make_unique<ManagedTinyGsmClient>(Modem);
    auto sslClient = std::make_unique<BearSSLClient>(*gsmClient);
    auto& sslRef = *sslClient;
    
    managedGsmClients.push_back(std::move(gsmClient));
    managedSslClients.push_back(std::move(sslClient));
    return HttpClient(sslRef, server, port);
}

BearSSLClient ArduinoCellular::getSecureNetworkClient(){
    return BearSSLClient(* new ManagedTinyGsmClient(Modem));
}
#endif

void ArduinoCellular::cleanup() {
    /*
    It's necessary to to manage the lifetime of the clients created by the library
    because the HttpClient and also BearSSLClient classes expect callers to manage the lifetime of the clients.
    For convenience, the library provides factory functions that allocate these objects on behalf of the caller.
     */
    managedSslClients.clear();  // Destroys BearSSLClient instances
    managedGsmClients.clear();  // Destroys ManagedTinyGsmClient instances
}

size_t ArduinoCellular::getManagedClientCount() const {
    return managedSslClients.size();
}

bool ArduinoCellular::isConnectedToOperator(){
    return Modem.isNetworkConnected();
}

bool ArduinoCellular::connectToGPRS(const char * apn, const char * gprsUser, const char * gprsPass){
    if(this->debugStream != nullptr){
        this->debugStream->println("Connecting to 4G network...");
    }
    while(!Modem.gprsConnect(apn, gprsUser, gprsPass)) {
        if(this->debugStream != nullptr){
            this->debugStream->print(".");
        }
        delay(2000);
    }
    return true;
}

bool ArduinoCellular::isConnectedToInternet(){
    return Modem.isGprsConnected();
}

SimStatus ArduinoCellular::getSimStatus(){
    int simStatus = Modem.getSimStatus();
    if(this->debugStream != nullptr){
        this->debugStream->println("SIM Status: " + String(simStatus));
    }

    if (simStatus == 0) {
        return SimStatus::SIM_ERROR;
    } else if (simStatus == 1) {
        return SimStatus::SIM_READY;
    } else if (simStatus == 2) {
        return SimStatus::SIM_LOCKED;
    } else if (simStatus == 3) {
        return SimStatus::SIM_ANTITHEFT_LOCKED;
    } else {
        return SimStatus::SIM_ERROR;
    }
}

bool ArduinoCellular::unlockSIM(String pin){
    int simStatus = Modem.getSimStatus();
    if(simStatus == SIM_LOCKED) {
        if(this->debugStream != nullptr){
            this->debugStream->println("Unlocking SIM...");
        }
        return Modem.simUnlock(pin.c_str());
    }
    else if(simStatus == SIM_ERROR || simStatus == SIM_ANTITHEFT_LOCKED) {
        return false;
    }
    /* SIM is ready */
    return true;
}

bool ArduinoCellular::awaitNetworkRegistration(bool waitForever){
    if(this->debugStream != nullptr){
        this->debugStream->println("Waiting for network registration...");
    }
    while (!Modem.waitForNetwork(waitForNetworkTimeout)) {
        
        if(!waitForever) {
            return false;
        }

        if(this->debugStream != nullptr){
            this->debugStream->print(".");
        }
        #if defined(ARDUINO_ARCH_MBED)
            if(mbed::Watchdog::get_instance().is_running()) {
                mbed::Watchdog::get_instance().kick();
            }
        #endif
        delay(2000);
    }
    return true;
}

bool ArduinoCellular::enableGPS(bool assisted){
    if(this->debugStream != nullptr){
        this->debugStream->println("Enabling GPS...");
    }

    String response;

    if(assisted){
        response = sendATCommand("+QGPSCFG=\"agpsposmode\",33488767", 10000);
    } else {
        // Sets the 23rd bit to 1 to enable standalone GPS
        response = sendATCommand("+QGPSCFG=\"agpsposmode\",8388608", 10000);
    }

    if(response.indexOf("OK") == -1){
        if(this->debugStream != nullptr){
            this->debugStream->println("Failed to set GPS mode.");
            this->debugStream->println("Response: " + response);
        }
        return false;
    }

    return Modem.enableGPS();
}

String ArduinoCellular::sendATCommand(const char * command, unsigned long timeout){
    String response;
    Modem.sendAT(command); 
    Modem.waitResponse(timeout, response);
    return response;
}

Time parseTimestamp(const String &timestampStr) {
  int hour, minute, second, day, month, year, offset;
  
  int commaIndex = timestampStr.indexOf(',');
  String date = timestampStr.substring(0, commaIndex);
  String time = timestampStr.substring(commaIndex + 1, timestampStr.indexOf('+'));
  String offsetStr = timestampStr.substring(timestampStr.indexOf('+') + 1);

  int firstSlashIndex = date.indexOf('/');
  int secondSlashIndex = date.lastIndexOf('/');
  year = date.substring(0, firstSlashIndex).toInt() + 2000;
  month = date.substring(firstSlashIndex + 1, secondSlashIndex).toInt();
  day = date.substring(secondSlashIndex + 1).toInt();

  int firstColonIndex = time.indexOf(':');
  int secondColonIndex = time.lastIndexOf(':');
  hour = time.substring(0, firstColonIndex).toInt();
  minute = time.substring(firstColonIndex + 1, secondColonIndex).toInt();
  second = time.substring(secondColonIndex + 1).toInt();

  offset = offsetStr.toInt();

  return Time(year, month, day, hour, minute, second, offset);
}

// Parses a single SMS entry from the data
SMS parseSMSEntry(const String& entry, const String& message) {
  SMS sms;
  int firstQuoteIndex = entry.indexOf('"');
  int secondQuoteIndex = entry.indexOf('"', firstQuoteIndex + 1);
  int thirdQuoteIndex = entry.indexOf('"', secondQuoteIndex + 1);
  int fourthQuoteIndex = entry.indexOf('"', thirdQuoteIndex + 1);
  int commaIndexBeforeTimestamp = entry.lastIndexOf(',', entry.lastIndexOf(',') - 1);

  String command = "+CMGL: ";
  // Index is between "+CMGL: " and first "," symbol
  sms.index = entry.substring(entry.indexOf(command) + command.length(), entry.indexOf(',')).toInt();

  // Extracting number and raw timestamp
  sms.sender = entry.substring(thirdQuoteIndex + 1, fourthQuoteIndex);
  String rawTimestamp = entry.substring(commaIndexBeforeTimestamp + 2, entry.indexOf('+', commaIndexBeforeTimestamp) + 3);

  // Parse the timestamp
  sms.timestamp = parseTimestamp(rawTimestamp);
  
  sms.message = message;
  return sms;
}

// Function to split a string into lines based on a delimiter character
// Filters out empty lines
std::vector<String> splitStringByLines(const String& input, char delimiter = '\n') {
    std::vector<String> lines;
    int startIndex = 0;
    while (startIndex < input.length()) {
        int endIndex = input.indexOf(delimiter, startIndex);
        if (endIndex == -1)
            endIndex = input.length();
        String line = input.substring(startIndex, endIndex);
        // Remove trailing \r if it exists
        if (line.endsWith("\r")) {
            line.remove(line.length() - 1);
        }
        lines.push_back(line);
        startIndex = endIndex + 1;
    }
    return lines;
}

// Splits the entire message string into individual SMS entries and parses them
std::vector<SMS> parseSMSData(const String& data) {
    std::vector<SMS> smsList = std::vector<SMS>();    
    std::vector<String> lines = splitStringByLines(data);

    // Remove first line if it's empty
    if (lines.size() > 0 && lines[0] == "") {
        lines.erase(lines.begin());
    }

    // Remove last 2 lines if second to last line is "OK"
    if (lines.size() >= 2 && lines.back() == "OK") {
        lines.erase(lines.end() - 2, lines.end());
    }
    
    for(int i = 0; i < lines.size(); i ++){
        if (lines[i].startsWith("+CMGL:")) {
            String entry = lines[i];
            String message = "";
            // Loop through the lines until the next +CMGL line and extract the message by concatenating the lines
            for (int j = i + 1; j < lines.size(); j++) {
                if (lines[j].startsWith("+CMGL:")) {
                    i = j - 1;
                    break;
                }
                message += lines[j] + "\n";
            }
            // Remove the trailing newline character from the message
            message.remove(message.length() - 1);

            SMS sms = parseSMSEntry(entry, message);
            smsList.push_back(sms);
        }
    }

  return smsList;
}

String ArduinoCellular::sendUSSDCommand(const char * command){
    return Modem.sendUSSD(command);
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

bool ArduinoCellular::deleteSMS(uint16_t index){
    String command = "+CMGD=" + String(index);
    String response = sendATCommand(const_cast<char *>(command.c_str()));
    return response.indexOf("OK") != -1;
}

void ArduinoCellular::setDebugStream(Stream &stream){
    this->debugStream = &stream;
}
