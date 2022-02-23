/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button
 */
 

#include "Button.hpp"

// constants won't change. They're used here to set pin numbers:
const int BUTTON_PIN = 7;       // the number of the pushbutton pin

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;                // the current reading from the input pin
Button b = Button(BUTTON_PIN);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  // pinMode(BUTTON_PIN, INPUT_PULLUP);
  // // pinMode(BUTTON_PIN)

  b.setupButton();
  
}

void loop() {
  // read the state of the switch/button:
  currentState = b.getState();

  
  if(b.isPressed())
    Serial.println("The button is pressed");
  else if(b.isReleased())
    Serial.println("The button is released");

  // save the the last state
  lastState = currentState;
}
