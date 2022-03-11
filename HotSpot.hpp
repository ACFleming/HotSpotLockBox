#ifndef HOTSPOT
#define HOTSPOT

#include <SPI.h>
#include <WiFi101.h>

const int BUTTON_PIN = 7; // the number of the pushbutton pin

//Class for storing the Hotspot details
class HotSpot{
private:
    String network_name;
    String password;
    int locker_number;
    bool locked;
    bool connection_status;

public:
    HotSpot();
    HotSpot(String username, String password, int locker_num);
    int getLockerNumber();
    bool isLocked();
    void lock();
    void unlock();
    bool connectToHotspot();
    
};



#endif