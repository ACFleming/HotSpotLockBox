#include <SPI.h>
#include <WiFi101.h>
#include "HotSpot.hpp"


// int keyIndex = 0;                // your network key Index number (needed only for WEP)

// int led =  LED_BUILTIN;
// bool connected = false;


// char ssid[] = "TelstraEDFA9F";     // the name of your network
// char pass[] = "rnemzruand";     // the Wifi radio's status  


// HotSpot user1;
// HotSpot user2;

// WiFiServer server(80);



// // constants won't change. They're used here to set pin numbers:
// const int BUTTON_PIN = 2;       // the number of the pushbutton pin
// int pressed = 0;

// Button b = Button(BUTTON_PIN);



// void setup()
// {

//     Serial.begin(9600);
//     while (!Serial) {
//         ; // wait for serial port to connect. Needed for native USB port only
//     }

    
//     if (WiFi.status() == WL_NO_SHIELD) {
//         Serial.println("WiFi 101 Shield not present"); //TODO change to LCD print
//         while (true);
//     }

//     b.setupButton();
    

//     //READ STORED LOGINS
    
//     // initialize digital pin LED_BUILTIN as an output.
//     pinMode(LED_BUILTIN, OUTPUT);
// }






// void loop()
// {
//     while(true){
//         digitalWrite(LED_BUILTIN, HIGH);
//         Serial.println("LOOP");
//         delay(1000);
//         if(! connected){
//             Serial.println("NOT CONNECTED");
            
//             user1 = HotSpot(String(ssid), String(pass), 0);
//             connected = user1.connectToHotspot();
            
//         }else{
//             Serial.println("CONNECTED. Begin server");
//             server.begin();
//         }
        
//         digitalWrite(LED_BUILTIN, LOW);
//         Serial.println("HERE");
//         delay(100);
//         // if(b.isPressed()){
//         //     pressed++;
//         // };
//         Serial.print(" Pressed? ");
//         Serial.println(b.isPressed());
//         Serial.print(" Released? ");
//         Serial.println(b.isReleased());
//     }
    
// }

#include "Button.hpp"

// constants won't change. They're used here to set pin numbers:


int button_low = 0;
int button_high = 0;
// Variables will change:
int lastState = HIGH; // the previous state from the input pin
int currentState;    // the current reading from the input pin
Button b = Button(BUTTON_PIN);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
//   b.setupButton();
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);
  Serial.print("CURRENT STATE: ");
  Serial.println(currentState);
  
  if(lastState == LOW && currentState == HIGH)
    // Serial.println("The state changed from LOW to HIGH");
    button_high++;
  if(lastState == HIGH && currentState == LOW)
    // Serial.println("The state changed from HIGH to LOW");
    button_low++;
  // // save the last state
  lastState = currentState;
  delay(100);
  Serial.print("BH: ");
  Serial.print(button_high);
  Serial.print(" BL:  ");
  Serial.print(button_low);
  Serial.println();
}