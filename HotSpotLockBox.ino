#include <SPI.h>
#include <WiFi101.h>
#include <FlashStorage_SAMD.h>
#include "HotSpot.hpp"
#include "LCD.hpp"
#include "Motor.hpp"
#include "Button.hpp"
#include "ClientIO.hpp"



#define INIT_LOGIN 0
#define MAIN_LOGIN 1
#define STOP_LOGIN 2 
#define INIT_REGISTER 3
#define WAIT_REGISTER 4
#define MAIN_REGISTER 5
#define STOP_REGISTER 6


#define HOME_PAGE 20
#define REGISTER_PAGE 21
#define UNREGISTER_PAGE 22



//Only 2 logins available at a time

Motor motor1;
Motor motor2;

Servo servo1;

HotSpot user1 = HotSpot();
HotSpot user2 = HotSpot();

char line0[21];
char line1[21];

String ssid1 = "";
String pass1 = "";
String ssid2 = "";
String pass2 = "";



const int LED1 = 4;
const int LED2 = 5;
const int MOTOR1 = 2;
const int MOTOR2 = 3;
const int SWITCH1 = 14;

int servo_pos;

int connected;
int display_page = HOME_PAGE;
int parse_result;

int curr_state;

int status = WL_IDLE_STATUS;


const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LCD lcd(rs, en, d4, d5, d6, d7);



WiFiServer server (80);
WiFiClient client;
String http_buf;
String content_buf;
char* register_password;


// String toString(const IPAddress& address){
//   return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
// }'


void toCString(String s, char* cs){
    int i;
    for(i = 0; i < s.length(); i++){
        cs[i] = s.charAt(i);
    }
    cs[i] = '\0';
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
    motor1.setToAngle(0);
    motor1.attach(MOTOR1);  
    motor1.setToAngle(50);
    motor1.setToAngle(10);
    motor1.setToAngle(90);
    motor1.setToAngle(0);
    delay(100);


    // servo1.attach(4);
    // servo1.write(45);
    motor2.setToAngle(0);
    motor2.attach(MOTOR2);
    motor2.setToAngle(50);
    motor2.setToAngle(10);
    motor2.setToAngle(90);
    motor2.setToAngle(0);
    delay(100);


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

    ssid1 = "DEADBEEF";     // the name of your network
    pass1 = "DEADBEEF";     // the Wifi radio's status
    ssid2 = "";     // the name of your network
    pass2 = "";     // the Wifi radio's status

    if(ssid1.length() > 0 && pass1.length() > 0 ){
        Serial.println("LOADING USER1");
        user1 =  HotSpot(ssid1, pass1, 1);
    }else{
        user1 = HotSpot();
    }
    if(ssid2.length() > 0 && pass2.length() > 0 ){
        Serial.println("LOADING USER2");
        user2 =  HotSpot(ssid2, pass2, 2);
    }else{
        user2 = HotSpot();
    }

    
    

    

    Serial.println(user1.getUsername());
    Serial.println(user2.getUsername());

    Serial.println("SOFTWARE SETUP COMPLETE");

    //Main Loop
    while (true) {
        delay(500);
        
        // Serial.print("Current state: ");
        // Serial.print(curr_state);
        // Serial.print(" Digital read: ");
        // Serial.print(digitalRead(SWITCH1));
        // Serial.print(" Server status: ");
        // Serial.print(status);
        // Serial.println();
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
            Serial.println(user1.getUsername());
            Serial.println(user2.getUsername());




            //Create users from login details


            curr_state = MAIN_LOGIN;
            // Serial.println("Back to the top");  
            continue;
            

        }else if(curr_state == MAIN_LOGIN){

            Serial.println("Looking for connections!");
            switch (connected)
            {
            case 0: //not connected
                lcd.setBothLines("Looking for", "Connections");
                lcd.show();
               
                Serial.println("Attempt connection to user 1");    
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
                motor1.setToAngle(90);
                motor2.setToAngle(0);
                //Open door 1
                //Close door 2
                lcd.setBothLines("Connected to: ", user1.getUsername());
                
            } else if (connected == 2) {
                //TODO Motor go brr
                motor1.setToAngle(0);
                motor2.setToAngle(90);
                //Open door 2
                //Close door 1
                lcd.setBothLines("Connected to: ", user2.getUsername());
            } else {
                motor1.setToAngle(0);
                motor2.setToAngle(0);
                //TODO Motor go brr
                //Close door 1
                //Close door 2
                lcd.setBothLines("Not connected", "");
            }
            lcd.show();
            // Serial.println("Back to the top");  
            continue;
            
        }else if (curr_state == STOP_LOGIN){
            Serial.println("Disconnecting");
            WiFi.disconnect();
            WiFi.end();
            lcd.setBothLines("Changing to", "register mode");
            lcd.show();
            delay(5000);
            curr_state = INIT_REGISTER;
            // Serial.println("Back to the top");  
            continue;
            



        }else if (curr_state == INIT_REGISTER){
            /* code */
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, LOW);

            status = WiFi.beginAP("Register");
            if(status != WL_AP_LISTENING){
                Serial.println(status);
                lcd.setLine("ERROR",0);
                lcd.show();
            }

            


            curr_state = WAIT_REGISTER;
            // Serial.println("Back to the top");  
            continue;


        }else if(curr_state == WAIT_REGISTER){
            
            lcd.setBothLines("Connect to", "SSID: Register");
            lcd.show();
            delay(1000);
            
            if(status != WiFi.status()){
                status = WiFi.status();
                if(status == WL_AP_CONNECTED){
                    Serial.println("New connection!"); 
                    byte remoteMac[6];
                    Serial.print("Device connected to AP, MAC address: ");
                    WiFi.APClientMacAddress(remoteMac);
                    printMacAddress(remoteMac);
                    lcd.setBothLines("Go to", "192.168.1.1");
                    lcd.show();
                    curr_state = MAIN_REGISTER;
                    IPAddress ip = WiFi.localIP();
                    Serial.print("http://");
                    Serial.println(ip);
                    server.begin();
                    delay(5000);
                    Serial.println("Server begun");
                    

                }
            }
            // Serial.println("Back to the top");  
            continue;
            
            
            
        }else if (curr_state == MAIN_REGISTER){
            
            WiFiClient client = server.available();   // listen for incoming clients
            if(WiFi.status() != WL_AP_CONNECTED){
                curr_state = WAIT_REGISTER;
                continue;
            }
            // Serial.println("Waiting for client");
           
            if (client) {                             
                Serial.println("Client connected");  
                bool read_content = false;       
                http_buf = "";
                content_buf = "";
                                
                while (client.connected()) {            
                    http_buf = readResponseLine(client);          
                    Serial.println(http_buf);
                    if (http_buf.length() == 0) {
                        
                        if(read_content){
                            Serial.println("Content");
                            content_buf = readResponseLine(client);
                            Serial.println(content_buf);
                            String username;
                            String password1;
                            String password2;
                            parse_result = parseUsernamePassword(content_buf, username, password1, password2);
                            if(parse_result ==-1){
                                Serial.println("Passwords didnt match");
                            }
                            if(parse_result ==-2){
                                Serial.println("invalid characters in post request");
                            }

                            Serial.print("Username: ");
                            Serial.println(username);
                            Serial.print("Password: ");
                            Serial.println(password1);
                            // char u[100];
                            // toCString(username, u);
                            // Serial.println(strlen(u));
                            // char p[100];
                            // toCString(password1,p);
                            // Serial.println(strlen(p));
                            if(display_page == REGISTER_PAGE){
                                if(parse_result!= 0){
                                    Serial.println("Parse Error");
                                }else if(username==user1.getUsername() || username==user2.getUsername()){ //Username is already used
                                    Serial.println("cant register ssid. Name already used");
                                    parse_result = -3;
                                }else if(user1.isFree()){ 
                                    user1 = HotSpot(username,password1,1);
                                    parse_result=1;
                                    ssid1 = username;
                                    pass1 = password1;
                                    // Serial.println(ssid1);
                                    // Serial.println(u);
                                    // Serial.println(pass1);
                                    // Serial.println(p);
                                    // strncpy(ssid1,u, sizeof(u));
                                    // strncpy(pass1,p,sizeof(p));
                                    
                                }else if(user2.isFree()){
                                    user2 = HotSpot(username,password1,2);
                                    parse_result=2;
                                    ssid2 = username;
                                    pass2 = password1;
                                    // Serial.println(ssid2);
                                    // Serial.println(u);
                                    // Serial.println(pass2);
                                    // Serial.println(p);
                                    // strncpy(ssid2,u, sizeof(u));
                                    // strncpy(pass2,p,sizeof(p));
                                }else{ //No lockers free
                                    Serial.println("No locker is free");
                                    parse_result = -4;
                                }

                            }
                            if(display_page == UNREGISTER_PAGE){
                                if(parse_result!= 0){
                                    Serial.println("Parse Error");
                                }else if(username!= user1.getUsername() && username != user2.getUsername()){ //Username is not stored
                                    Serial.println("cant unregister ssid. Name not found");
                                    parse_result = -5;
                                }else if(user1.checkLoginDetails(username,password1)){
                                    Serial.println("Unregistered 1");
                                    user1 = HotSpot();
                                    parse_result = 0;
                                }else if(user2.checkLoginDetails(username,password1)){
                                    Serial.println("Unregistered 2");
                                    user2 = HotSpot();
                                    parse_result=0;
                                }else if(user1.isFree() && user2.isFree()){
                                    Serial.println("nothing to unregister");
                                    parse_result = -6;
                                }
                            }
                            Serial.println(user1.getUsername());
                            Serial.println(user2.getUsername());

                            
                        }
                        // writeHomeHTML(client);
                        if(display_page == REGISTER_PAGE ){
                            writeRegisterHTML(client, user1.isFree(), user2.isFree(), parse_result);
                        }else if(display_page == UNREGISTER_PAGE){
                            writeUnregisterHTML(client, user1.isFree(), user2.isFree(), parse_result);
                        }else{
                            writeHomeHTML(client, user1.isFree(), user2.isFree());
                        }
                        
                        break;
                    }
                    if(http_buf.startsWith("GET /register")){
                        display_page = REGISTER_PAGE;
                        parse_result=21;
                    }else if(http_buf.startsWith("GET /unregister")){
                        display_page = UNREGISTER_PAGE;
                        parse_result=21;
                    }else if(http_buf.startsWith("GET / ")){
                        display_page = HOME_PAGE;
                        parse_result=21;
                    }

                    if(http_buf.startsWith("Content")){            //Contains post request content
                        read_content = true;
                    }
                    
                    
                }
            // close the connection:
            client.stop();
            Serial.println("Client end request");
            }
            //TODO service webpage
            // Serial.println("Back to the top");  
            continue;
            
        }else if(curr_state == STOP_REGISTER){ //TODO
            //write logins to flash
            // Serial.println("Back to the top");
            Serial.println("Disconnecting");
            WiFi.disconnect();
            WiFi.end();
            lcd.setBothLines("Changing to", "login mode");
            lcd.show();
            delay(5000);
            curr_state = INIT_LOGIN;
            continue;
        }
        
    }
    

    Serial.println("LOOPY");

    
}


