#ifndef BUTTON
#define BUTTON


//Class for a button where pressed is HIGH and released is LOW
class Button
{
private:
    int state;
    int pin;
    
    
public:
    Button(int pin);
    Button(int pin, int state);
    void setupButton();
    ~Button();
    int getState();
    int isPressed();
    int isReleased();
};

#endif