

#include "Button.hpp"


Button::Button(int pin){
    Button:Button(pin,HIGH);
}


Button::Button(int pin, int state){
    this->pin = pin;
    this->state = state;

}

void Button::setupButton(){
    pinMode(this->pin, INPUT_PULLUP);
}

int Button::isPressed(){
    this->getState();
    return this->state==HIGH ? true : false;
}

int Button::isReleased(){
    this->getState();
    return this->state==LOW ? true : false;
}

int Button::getState(){
    this->state = digitalRead(this->pin);
    return this->state;
}

