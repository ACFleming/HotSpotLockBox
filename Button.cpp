#include "Button.hpp"


Button::Button(int p){
    Button:Button(p,HIGH);
}


Button::Button(int p, int s){
    this->pin = p;
    this->state = s;

}

void Button::setupButton(){
    Serial.println(this->pin);
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

int Button::getPin(){
    return this->pin;
}

void Button::setPin(int p){
    this->pin = pin;
}

