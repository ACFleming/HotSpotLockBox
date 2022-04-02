#ifndef HOTSPOT_H
#define HOTSPOT_H

#include <SPI.h>
#include <WiFi101.h>

const int BUTTON_PIN = 7; // the number of the pushbutton pin

//Class for storing the Hotspot details
class HotSpot{
private:
    char* network_name;
    char* password;
    int locker_number;
    bool locked;
    bool connection_status;

public:
    HotSpot();
    HotSpot(char* username, char* password, int locker_num);
    void setLoginDetails(char* username, char*password);
    int getLockerNumber();
    bool isOccupied();
    char* getUsername();
    bool isLocked();
    void lock();
    void unlock();
    bool connectToHotSpot();
    bool isConnected();
    
};



#endif