#include <SPI.h>
#include <WiFi101.h>
#include "HotSpot.hpp"
#include "HotSpot.hpp"]
#include <LiquidCrystal.h>


int keyIndex = 0;                // your network key Index number (needed only for WEP)

int LED1 = 5;
int LED2 = 7;


int connected = 0;

bool button_pressed = false;


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//Only 2 logins available at a time



HotSpot user1;
HotSpot user2;

char line0[21];
char line1[21];

void LCDShow(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line0);
    lcd.setCursor(0,1);
    lcd.print(line1);
}

void setLCDLine(char* s, int line=0){
   
   
    if(line == 1){
        memset(line1, 0, 21);
        strcpy(line1, s);
    }else{
        memset(line0, 0, 21);
        strcpy(line0,s);
    }
   
}

   
void setLCDLine(String s, int line = 0){
    if(line == 1){
        s.toCharArray(line1, s.length());
    }else{
        s.toCharArray(line0, s.length());
    }
}






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
    lcd.begin(16, 2);
    // turn on the cursor:
    lcd.cursor();

    //MOTOR SETUP


    //WIFI SHIELD SETUP
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi 101 Shield not present"); //TODO change to LCD print
        setLCDLine("WiFi 101 Shield not present", 0);
        LCDShow();
        while (true);
    }
    Serial.println("WiFi 101 Shield  present");
    setLCDLine("WiFi present", 0);
    LCDShow();





    Serial.println("HARDWARE SETUP COMPLETE");
}






void loop()
{


  Serial.println("BEGIN SOFWARE SETUP");
  //SOFTWARE SETUP
  
  //Read Logins
  char ssid1[] = "DEADBEEF";     // the name of your network
  char pass1[] = "DEADBEEF";     // the Wifi radio's status
  char ssid2[] = "Testing";     // the name of your network
  char pass2[] = "12345678";     // the Wifi radio's status

  
  HotSpot user1 =  HotSpot(ssid1, pass1, 1);
  HotSpot user2 =  HotSpot(ssid2, pass2, 2);
  

  Serial.println(user1.getUsername());
  Serial.println(user2.getUsername());

  Serial.println("SOFTWARE SETUP COMPLETE");

  //Main Loop
  while (true) {
    delay(300);
    button_pressed = false;

    //Accepting New Users
    if (button_pressed) {

              
    //Looking for registered users
    } else {
        Serial.println("Looking for connections!");
        setLCDLine("Connected to: ", 0);
        LCDShow();
        switch (connected)
        {
        case 0:
            //Attempting to connect to the first nextwork
            Serial.println("Connecting 1");
            if(user1.connectToHotSpot() == true){
                connected = 1;
            
            //Attempting to connect to the second network
            Serial.println("Connecting 2");
            }else if(user2.connectToHotSpot() == true){
                connected = 2;
            
            }
            break;
            
            
        case 1:
            Serial.println("Checking 1");
            if(user1.isConnected()){
                connected = 1;
            }else{
                connected = 0;
            }
            break;
        case 2:
            Serial.println("Checking 2");
            if(user2.isConnected()){
                connected = 2;
            }else{
                connected = 0;
            }
            break;
        default:
            Serial.println("DEFAULT! No connections?? Invalid state!");
            break;
        }

    }

    //Displaying status
    Serial.print("Connnection State: ");
    Serial.println(connected);
    
    if (connected == 1) {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        setLCDLine("1", 1);
    } else if (connected == 2) {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        setLCDLine("2", 1);
    } else {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        setLCDLine("0", 1);
    }
    LCDShow();


  }

}
