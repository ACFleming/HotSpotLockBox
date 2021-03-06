#include "HotSpot.hpp"

HotSpot::HotSpot(){
    this->locker_number = -1;
    this->network_name = (char*)"DEADBEEF";
    this->password = (char*)"DEADBEEF";
    this->connection_status = false;
}

int HotSpot::getLockerNumber(){
    return this->locker_number;
}

bool HotSpot::isFree(){
    return this->locker_number==-1;
}

HotSpot::HotSpot(String username, String password, int locker_num){
    this->locker_number = locker_num;
    this->network_name = username;
    this->password = password;
    this->connection_status = false;

}

void HotSpot::setLoginDetails(String username, String password){
    this->network_name = username;
    this->password = password;
}

String HotSpot::getUsername(){
    return this->network_name;
}


bool HotSpot::isConnected(){
    if(WiFi.RSSI() > -100){
        this->connection_status = true;
        Serial.println("Connected!");
    }else{
        this->connection_status = false;
        Serial.println("Disconnected!");
    }
    return this->connection_status;
}



bool HotSpot::connectToHotSpot(){
    if(this->connection_status == false){
        Serial.print("Attempting to connect to SSID: ");//TODO change to LCD print
        Serial.println(this->network_name);//TODO change to LCD print
        WiFi.setTimeout(2000);
        
        WiFi.begin(this->network_name, this->password);
        delay(100);
        Serial.print("Signal strength (RSSI):");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
        if(WiFi.RSSI() > -100){
            this->connection_status = true;
            Serial.println("Connected!");
        }
        


    }else{
        Serial.print("Already connected! ");
        Serial.println(WiFi.getTime());
        
    }
    return this->connection_status;
}

bool HotSpot::checkLoginDetails(String username, String password){
    Serial.print("u1 ");
    Serial.print(this->network_name);
    Serial.print(" u2 ");
    Serial.println(username);
    Serial.print("p1 ");
    Serial.print(this->password);
    Serial.print(" p2 ");
    Serial.println(password);

    if(username == this->network_name && this->password == password){
        return true;
    }
    return false;
}