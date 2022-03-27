// #include <SPI.h>
// #include <WiFi101.h>
// #include "HotSpot.hpp"
// #include "SerialCommunication.hpp"

// int keyIndex = 0;                // your network key Index number (needed only for WEP)

// int LED1 = 5;
// int LED2 = 7;

// int BUILTIN_OUTPUT = HIGH;

// int connected = 0;

// bool button_pressed = false;


// //Only 2 logins available at a time

// HotSpot user1;
// HotSpot user2;

// #define MAX_LEN 100


// char* ssid1;
// char* pass1;
// char* ssid2;
// char* pass2;


// char receive_buf[MAX_LEN];

// char send_buf[MAX_LEN];

// void blockReadSerial(){
//     while(Serial1.available() <= 0){};
//     readSerial();
// };


// bool readSerial(){
//     bool read= false;
//     while(Serial1.available() > 0){
//         static int num_read = 0;
//         char c = Serial1.read();
//         num_read++;
//         read = true;
//         if(c != '\n' && num_read < MAX_LEN){
//             receive_buf[num_read] = c;
//         }else{
//             receive_buf[num_read]= '\0';
//         }
//     }
//     Serial.println(receive_buf);
//     if(strlen(receive_buf) > 1){
//         read = false;
//     }
//     Serial.println("DONE READING");
//     return read; 
// }

// void toggleLED(int pin_number){
//     static int pin_state = LOW;
//     if(pin_state == LOW){
//         digitalWrite(pin_number,HIGH);
//         pin_state = HIGH;
//     }else{
//         digitalWrite(pin_number,LOW);
//         pin_state = LOW;
//     }
// }

// bool checkResponse(char* expected){
//     if(receive_buf != expected){
//         return false;
//     }
//     return true;
// }


// void sendWaitForACK(char* payload){
//     Serial.println("WAITING FOR ACK");
//     bool read = false;
//     while(true){
        
//         toggleLED(LED_BUILTIN);
//         Serial.print("Sending ");
//         Serial.println(payload);
//         Serial1.println(payload);
//         delay(100);
//         Serial.println("Reading");
//         readSerial();        
//         if(checkResponse(ACK)){
//             Serial.println("Received!");
//             break;
//         }
//         Serial.println("ACK Failed!");

//         delay(500);
//     }
    

// };


// void LCDPrint(char* s){
//     sendWaitForACK(PRINT_LCD);
//     delay(100);
//     sendWaitForACK(s);

// }




// void readLogins(){
//     sendWaitForACK(READ_LOGINS);
//     //SSID1
//     Serial.println("SSID1");
//     blockReadSerial();
    
//     Serial.println(receive_buf);
//     strcmp(ssid1, receive_buf);
//     Serial1.println(ACK);
    
    
//     //PASS1
//     Serial.println("PASS1");
//     blockReadSerial();
//     Serial.println(receive_buf);
//     strcmp(pass1, receive_buf);
//     Serial1.println(ACK);

//     //SSID2
//     Serial.println("SSID2");
//     blockReadSerial();
//     Serial.println(receive_buf);
//     strcmp(ssid2, receive_buf);
//     Serial1.println(ACK);

//     //PASS2
//     Serial.println("PASS2");
//     blockReadSerial();
//     Serial.println(receive_buf);
//     strcmp(ssid1, receive_buf);
//     Serial1.println(ACK);
// }


// void writeLogins(){
//     sendWaitForACK(WRITE_LOGINS);
//     delay(100);
//     //SSID1
//     sendWaitForACK(ssid1);
//     delay(100);
//     //PASS1
//     sendWaitForACK(pass1);
//     delay(100);
//     //SSID2
//     sendWaitForACK(ssid2);
//     delay(100);
//     //PASS2
//     sendWaitForACK(pass2);
//     delay(100);

// }

// void setup()
// {

//     //HARDWARE SETUP



//     //Set up serial port
//     Serial.begin(9600);
//     while(!Serial);

//     delay(100);
//     Serial.println("BEGIN HARDWARE SETUP");

//     //Set up 2nd serial port
//     Serial1.begin(9600);
    
//     delay(100);


//     //LED setup
//     pinMode(LED1, OUTPUT);
//     pinMode(LED2, OUTPUT);
//     pinMode(LED_BUILTIN, OUTPUT);

//     digitalWrite(LED_BUILTIN, HIGH);
//     delay(500);
//     digitalWrite(LED_BUILTIN, LOW);
//     delay(500);
//     digitalWrite(LED_BUILTIN, HIGH);
//     delay(500);
//     digitalWrite(LED_BUILTIN, LOW);
//     delay(500);




//     //WIFI SHIELD SETUP
//     if (WiFi.status() == WL_NO_SHIELD) {
//         Serial.println("WiFi 101 Shield not present"); //TODO change to LCD print
//         while (true);
//     }
//     Serial.println("WiFi 101 Shield  present");





//     Serial.println("HARDWARE SETUP COMPLETE");
// }






// void loop()
// {


//     Serial.println("BEGIN SOFWARE SETUP");
//     //SOFTWARE SETUP
    
//     //Read Logins



//     // strcpy(ssid1, "DEADBEEF");
//     // strcpy(pass1, "DEADBEEF"); 
//     // strcpy(ssid2, "Testing");
//     // strcpy(pass2, "12345678");
//     Serial.println("READING LOGINS");
//     readLogins();


    
//     HotSpot user1 =  HotSpot(ssid1, pass1, 1);
//     HotSpot user2 =  HotSpot(ssid2, pass2, 2);
    

//     Serial.println(user1.getUsername());
//     Serial.println(user2.getUsername());
//     LCDPrint(user1.getUsername());


//     Serial.println("SOFTWARE SETUP COMPLETE");

//     //Main Loop
//     while (true) {
//         delay(300);
//         button_pressed = false;

//         //Accepting New Users
//         if (button_pressed) {

                
//         //Looking for registered users
//         } else {
//             Serial.println("Looking for connections!");
//             switch (connected)
//             {
//             case 0:
//                 //Attempting to connect to the first nextwork
//                 Serial.println("Connecting 1");
//                 if(user1.connectToHotSpot() == true){
//                     connected = 1;
                
//                 //Attempting to connect to the second network
//                 Serial.println("Connecting 2");
//                 }else if(user2.connectToHotSpot()== true){
//                     connected = 2;
                
//                 }
//                 break;
                
                
//             case 1:
//                 Serial.println("Checking 1");
//                 if(user1.isConnected()){
//                     connected = 1;
//                 }else{
//                     connected = 0;
//                 }
//                 break;
//             case 2:
//                 Serial.println("Checking 2");
//                 if(user2.isConnected()){
//                     connected = 2;
//                 }else{
//                     connected = 0;
//                 }
//                 break;
//             default:
//                 Serial.println("DEFAULT! No connections?? Invalid state!");
//                 break;
//             }

//         }

//         //Displaying status
//         Serial.print("Connnection State: ");
//         Serial.println(connected);
//         if (connected == 1) {
//             digitalWrite(LED1, HIGH);
//             digitalWrite(LED2, LOW);
//         } else if (connected == 2) {
//             digitalWrite(LED1, LOW);
//             digitalWrite(LED2, HIGH);
//         } else {
//             digitalWrite(LED1, LOW);
//             digitalWrite(LED2, LOW);
//         }


//     }

// }
