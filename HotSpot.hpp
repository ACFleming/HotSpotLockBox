#ifndef HOTSPOT
#define HOTSPOT

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
    bool isLocked();
    void lock();
    void unlock();
    bool connectToHotspot();
    bool isConnected();
    
};



#endif