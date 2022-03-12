#include "HotSpot.hpp"

HotSpot::HotSpot(){
    this->locker_number = -1;
    this->network_name = (char*)"DEADBEEF";
    this->password = (char*)"DEADBEEF";
    this->connection_status = WL_IDLE_STATUS;
}


HotSpot::HotSpot(char* username, char* password, int locker_num){
    this->locker_number = locker_num;
    this->network_name = username;
    this->password = password;
    this->connection_status = false;

}

void HotSpot::setLoginDetails(char* username, char* password){
    this->network_name = username;
    this->password = password;
}


bool HotSpot::isConnected(){
    return this->connection_status;
}



bool HotSpot::connectToHotspot(){
    if(this->connection_status == false){
        Serial.print("Attempting to connect to SSID: ");//TODO change to LCD print
        Serial.println(this->network_name);//TODO change to LCD print
        
        this->connection_status = WiFi.begin(this->network_name, this->password);
        delay(1000);
        Serial.print("Connected! Signal strength (RSSI):");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
        if(WiFi.RSSI() > -100){
            this->connection_status = true;
        }
        


    }else{
        Serial.print("Already connected! ");
        Serial.println(WiFi.getTime());
        delay(1000);
    }
    return this->connection_status;
}