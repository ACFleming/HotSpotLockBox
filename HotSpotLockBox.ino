#include <SPI.h>
#include <WiFi101.h>
#include "HotSpot.hpp"
#include "LCD.hpp"
#include "Motor.hpp"
#include "Button.hpp"



#define INIT_LOGIN 0
#define MAIN_LOGIN 1
#define STOP_LOGIN 2 
#define INIT_REGISTER 3
#define WAIT_REGISTER 4
#define MAIN_REGISTER 5
#define STOP_REGISTER 6



//Only 2 logins available at a time

Motor motor1;
Motor motor2;

Servo servo1;

HotSpot user1;
HotSpot user2;

char line0[21];
char line1[21];



const int LED1 = 4;
const int LED2 = 5;
const int MOTOR1 = 2;
const int MOTOR2 = 3;
const int SWITCH1 = 14;

int servo_pos;

int connected;


int curr_state;

int status = WL_IDLE_STATUS;


const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LCD lcd(rs, en, d4, d5, d6, d7);



WiFiServer server (80);
WiFiClient client;
String http_buf;
char* register_password;


String toString(const IPAddress& address){
  return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
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





    // digitalWrite(LED1, HIGH);
    // digitalWrite(LED2, LOW);
    // delay(500);
    // digitalWrite(LED2, HIGH);
    // digitalWrite(LED1, LOW);
    // delay(500);
    // digitalWrite(LED1, HIGH);
    // digitalWrite(LED2, LOW);
    // delay(500);
    // digitalWrite(LED2, HIGH);
    // digitalWrite(LED1, LOW);
    // delay(500);

    //LCD SETUP
    lcd.begin(16, 2);
    // turn on the cursor:
    lcd.cursor();

    //MOTOR SETUP

    motor1.attach(MOTOR1);  
    delay(100);
    motor1.setToAngle(0);
    motor1.setToAngle(90); 

    // servo1.attach(4);
    // servo1.write(45);

    motor2.attach(MOTOR2);
    delay(100);
    motor2.setToAngle(0);
    motor2.setToAngle(90);

    //BUTTOM SETUP
    Serial.println("BUTTON SETUP");
    pinMode(SWITCH1, INPUT_PULLUP);
    
    // b1.setPin(14);
    // Serial.print("Button pin: ");
    // Serial.println(b1.getPin());

    // b1.setupButton();


    //WIFI SHIELD SETUP
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi 101 Shield not present"); //TODO change to LCD print
        lcd.setLine("WiFi 101 Shield not present", 0);
        lcd.show();
        while (true);
    }
    Serial.println("WiFi 101 Shield  present");
    lcd.setLine("WiFi present", 0);
    lcd.show();




    Serial.println("HARDWARE SETUP COMPLETE");
}






void loop()
{


    Serial.println("BEGIN SOFWARE SETUP");
    //SOFTWARE SETUP

    curr_state = 0;

    register_password = (char *)"";


    


    
    

    

    Serial.println(user1.getUsername());
    Serial.println(user2.getUsername());

    Serial.println("SOFTWARE SETUP COMPLETE");

    //Main Loop
    while (true) {
        delay(500);
        
        Serial.print("Current state: ");
        Serial.print(curr_state);
        Serial.print(" Digital read: ");
        Serial.print(digitalRead(SWITCH1));
        Serial.print(" Server status: ");
        Serial.print(status);
        Serial.println();
        if(curr_state == MAIN_LOGIN && digitalRead(SWITCH1)==LOW){ //Stop login and init registering
            Serial.println("STOPPING LOGIN");
            curr_state = STOP_LOGIN;
        }else if( (curr_state == MAIN_REGISTER || curr_state == WAIT_REGISTER) && digitalRead(SWITCH1) == HIGH ){
            curr_state = STOP_REGISTER;
            Serial.println("STOPPING REGISTER");
        }


        if(curr_state == INIT_LOGIN){
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, HIGH);
            //TODO read in login details
            char ssid1[] = "DEADBEEF\0";     // the name of your network
            char pass1[] = "DEADBEEF\0";     // the Wifi radio's status
            char ssid2[] = "Testing\0";     // the name of your network
            char pass2[] = "12345678\0";     // the Wifi radio's status

            //Create users from login details
            Serial.println("STRLEN");
            Serial.println(strlen(ssid1));
            if(strlen(ssid1) > 0 && strlen(pass1) > 0 ){
                user1 =  HotSpot(ssid1, pass1, 1);
            }else{
                user1 = HotSpot();
            }
            if(strlen(ssid2) > 0 && strlen(pass2) > 0 ){
                user2 =  HotSpot(ssid2, pass2, 2);
            }else{
                user2 = HotSpot();
            }
            curr_state = MAIN_LOGIN;
            Serial.println("Back to the top");  
            continue;
            

        }else if(curr_state == MAIN_LOGIN){

            Serial.println("Looking for connections!");
            switch (connected)
            {
            case 0: //not connected
                lcd.setBothLines("Looking for", "Connections");
                lcd.show();
               
                Serial.println("Attempt connection to user 1");
                Serial.print("User 1 locker number: ");
                Serial.println(user1.getLockerNumber());     
                if(user1.getLockerNumber() != -1 && user1.connectToHotSpot() == true){
                    connected = 1;
                    break;
                }
                Serial.println("Attempt connection to user 2");
                if(user2.getLockerNumber() != -1 && user2.connectToHotSpot() == true){
                    connected = 2;
                    break;
                }
                connected = 0; 
                break;                
            case 1: //user1 is connected
                Serial.println("Checking user1");
                if(user1.isConnected()){
                    connected = 1;
                }else{
                    connected = 0;
                }
                break;
            case 2: //user2 is connected
                Serial.println("Checking 2");
                if(user2.isConnected()){
                    connected = 2;
                }else{
                    connected = 0;
                }
                break;
            default:
                Serial.println("Invalid state!");
                break;
            }
            //Displaying status
            
            if (connected == 1) {
                //TODO Motor go brrr
                //Open door 1
                //Close door 2
                lcd.setBothLines("Connected to: ", user1.getUsername());
                
            } else if (connected == 2) {
                //TODO Motor go brr
                //Open door 2
                //Close door 1
                lcd.setBothLines("Connected to: ", user1.getUsername());
            } else {
                //TODO Motor go brr
                //Close door 1
                //Close door 2
                lcd.setBothLines("Not connected", "");
            }
            lcd.show();
            Serial.println("Back to the top");  
            continue;
            
        }else if (curr_state == STOP_LOGIN){
            Serial.println("Disconnecting");
            WiFi.disconnect();
            WiFi.end();
            lcd.setBothLines("Changing to", "register mode");
            lcd.show();
            delay(5000);
            curr_state = INIT_REGISTER;
            Serial.println("Back to the top");  
            continue;
            



        }else if (curr_state == INIT_REGISTER){
            /* code */
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, LOW);
            lcd.setBothLines("Connect to SSID", "Register");
            lcd.show();
            delay(1000);
            status = WiFi.beginAP("Register");
            Serial.println("AM I LISTENING??");
            Serial.println(status);
            if(status != WL_AP_LISTENING){
                Serial.println(status);
                lcd.setLine("ERROR",0);
                lcd.show();
            }

            
            server.begin();
            delay(10000);
            Serial.println("Server begun");

            curr_state = WAIT_REGISTER;
            Serial.println("Back to the top");  
            continue;


        }else if(curr_state == WAIT_REGISTER){
            
            
            
            if(status != WiFi.status()){
                status = WiFi.status();
                if(status == WL_AP_CONNECTED){
                    Serial.println("New connection!"); 
                    byte remoteMac[6];
                    Serial.print("Device connected to AP, MAC address: ");
                    WiFi.APClientMacAddress(remoteMac);
                    printMacAddress(remoteMac);
                    lcd.setBothLines("Connect to", "192.168.1.1");
                    lcd.show();
                    curr_state = MAIN_REGISTER;
                    IPAddress ip = WiFi.localIP();
                    Serial.print("http://");
                    Serial.println(ip);
                    delay(3000);
                    

                }
            }
            Serial.println("Back to the top");  
            continue;
            
            
            
        }else if (curr_state == MAIN_REGISTER){
            
            WiFiClient client = server.available();   // listen for incoming clients

            
            if (client) {                             // if you get a client,
                Serial.println("new client");           // print a message out the serial port
                String currentLine = "";                // make a String to hold incoming data from the client
                while (client.connected()) {            // loop while the client's connected
                    if (client.available()) {             // if there's bytes to read from the client,
                        char c = client.read();             // read a byte, then
                        Serial.write(c);                    // print it out the serial monitor
                        if (c == '\n') {                    // if the byte is a newline character

                            // if the current line is blank, you got two newline characters in a row.
                            // that's the end of the client HTTP request, so send a response:
                            if (currentLine.length() == 0) {
                                // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                                // and a content-type so the client knows what's coming, then a blank line:
                                client.println("HTTP/1.1 200 OK");
                                client.println("Content-type:text/html");
                                client.println();

                                // the content of the HTTP response follows the header:
                                client.print("yahoo <a href=\"/H\">here</a> turn the LED on<br>");
                                client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");

                                // The HTTP response ends with another blank line:
                                client.println();
                                // break out of the while loop:
                                break;
                            }else {      // if you got a newline, then clear currentLine:
                                currentLine = "";
                            }
                        }
                        else if (c != '\r') {    // if you got anything else but a carriage return character,
                        currentLine += c;      // add it to the end of the currentLine
                        }

                        // Check to see if the client request was "GET /H" or "GET /L":
                        if (currentLine.endsWith("GET /H")) {
                        digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
                        }
                        if (currentLine.endsWith("GET /L")) {
                        digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
                        }
                    }
                }
            // close the connection:
            client.stop();
            Serial.println("client disconnected");
            }
            //TODO service webpage
            Serial.println("Back to the top");  
            continue;
            
        }else if(curr_state == STOP_REGISTER){ //TODO
            //write logins to flash
            Serial.println("Back to the top");  
            continue;
        }
        
    }
    

    Serial.println("LOOPY");

    
}


