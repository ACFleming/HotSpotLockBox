#include <SPI.h>
#include <WiFi101.h>
#include "HotSpot.hpp"


int keyIndex = 0;                // your network key Index number (needed only for WEP)

int LED1 = 5;
int LED2 = 7;


int connected = 0;

bool button_pressed = false;


//Only 2 logins available at a time

HotSpot *user1 = NULL;
HotSpot *user2 = NULL;

int* test_pointer = NULL;



void setup()
{

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

  //Set up serial port
  // int x = 8;
  *test_pointer = 8; 

  Serial.begin(9600);
  delay(100);
  Serial.println("BEGIN SETUP");
  //Set up Wifi shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi 101 Shield not present"); //TODO change to LCD print
    while (true);
  }
  Serial.println("WiFi 101 Shield  present");


  //Read Logins
  char ssid1[] = "TelstraEDFA9F";     // the name of your network
  char pass1[] = "rnemzruand";     // the Wifi radio's status
  
  user1 = new HotSpot(ssid1, pass1, 1);




  Serial.println("SETUP COMPLETE");
}






void loop()
{
  char ssid1[] = "TelstraEDFA9F";     // the name of your network
  char pass1[] = "rnemzruand";     // the Wifi radio's status
  while (true) {
    delay(100);
    button_pressed = false;
    if (button_pressed) {

    } else {
      Serial.println("Looking for connections!");
      if (connected == 0) {
        Serial.print("Looking to connect to ");
        Serial.println(ssid1);
        int status = WiFi.begin(ssid1, pass1);
        // connected = user1->connectToHotspot();
        delay(1000);
        Serial.println(status);
        if (status == WL_CONNECTED) {
          connected = 1;
          Serial.println("CONNECTED");
          Serial.println(WiFi.RSSI());

        }

      }

      if (connected == 0) {
        // connected = user2->connectToHotspot();
        connected = 2;
      }


    }
    Serial.print("Connnection State: ");
    Serial.println(connected);
    Serial.print("TEST ");
    Serial.println(*test_pointer);
    if (connected == 1) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
    } else if (connected == 2) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    } else {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    }


  }

}
