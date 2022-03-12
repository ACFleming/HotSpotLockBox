#include <SPI.h>
#include <WiFi101.h>
#include "HotSpot.hpp"


int keyIndex = 0;                // your network key Index number (needed only for WEP)

int LED1 = 5;
int LED2 = 7;


int connected = 0;

bool button_pressed = false;


//Only 2 logins available at a time

HotSpot user1;
HotSpot user2;





void setup()
{

  //HARDWARE SETUP



  //Set up serial port
  Serial.begin(9600);
  delay(100);
  Serial.println("BEGIN HARDWARE SETUP");

  //LED setup
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  //LCD SETUP


  //MOTOR SETUP


  //WIFI SHIELD SETUP
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi 101 Shield not present"); //TODO change to LCD print
    while (true);
  }
  Serial.println("WiFi 101 Shield  present");





  Serial.println("HARDWARE SETUP COMPLETE");
}






void loop()
{


  Serial.println("BEGIN SOFWARE SETUP");
  //SOFTWARE SETUP
  
  //Read Logins
  char ssid1[] = "DEADBEEF";     // the name of your network
  char pass1[] = "DEADBEEF";     // the Wifi radio's status
  char ssid2[] = "TelstraEDFA9F";     // the name of your network
  char pass2[] = "rnemzruand";     // the Wifi radio's status

  
  HotSpot user1 =  HotSpot(ssid1, pass1, 1);
  HotSpot user2 =  HotSpot(ssid2, pass2, 2);
  

  Serial.println(user1.getUsername());
  Serial.println(user2.getUsername());

  Serial.println("SOFTWARE SETUP COMPLETE");

  //Main Loop
  while (true) {
    delay(100);
    button_pressed = false;

    //Accepting New Users
    if (button_pressed) {

              
    //Looking for registered users
    } else {
      Serial.println("Looking for connections!");
      if (connected == 0) { 
        if(user1.connectToHotSpot() == true){
          connected = 1;
        }
      }

      if (connected == 0) {
        if(user2.connectToHotSpot()== true){
          connected = 2;
        }
      }


    }

    //Displaying status
    Serial.print("Connnection State: ");
    Serial.println(connected);
    if (connected == 1) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
    } else if (connected == 2) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    } else {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
    }


  }

}
