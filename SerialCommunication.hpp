#ifndef SERCOM
#define SERCOM





class SerialCommunciation{
private:
    char* payload;

public:
    SerialCommunciation(char* payload);
    char* getPayload();
    
};


#endif