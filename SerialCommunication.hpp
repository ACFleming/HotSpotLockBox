#ifndef SERCOM
#define SERCOM


enum msgType{
    data_request,
    data_response,
    message_to_display
};



class SerialCommunciation{
private:
    msgType type;
    char* payload;

public:
    SerialCommunciation(msgType type, char* payload);
    msgType getType();
    char* getPayload();
    
};


#endif