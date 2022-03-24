// #include <SPI.h>
// #include <WiFi101.h>
// #include "HotSpot.hpp"
// #include <SoftwareSerialTX.h>


// int keyIndex = 0;                // your network key Index number (needed only for WEP)

// int LED1 = 5;
// int LED2 = 7;

// int BUILTIN_OUTPUT = HIGH;

// int connected = 0;

// bool button_pressed = false;


// //Only 2 logins available at a time

// HotSpot user1;
// HotSpot user2;





// void setup()
// {

//     //HARDWARE SETUP



//     //Set up serial port
//     Serial.begin(9600);
//     delay(100);
//     Serial.println("BEGIN HARDWARE SETUP");

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

//     //LCD SETUP


//     //MOTOR SETUP


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


//   Serial.println("BEGIN SOFWARE SETUP");
//   //SOFTWARE SETUP
  
//   //Read Logins
//   char ssid1[] = "DEADBEEF";     // the name of your network
//   char pass1[] = "DEADBEEF";     // the Wifi radio's status
//   char ssid2[] = "Testing";     // the name of your network
//   char pass2[] = "12345678";     // the Wifi radio's status

  
//   HotSpot user1 =  HotSpot(ssid1, pass1, 1);
//   HotSpot user2 =  HotSpot(ssid2, pass2, 2);
  

//   Serial.println(user1.getUsername());
//   Serial.println(user2.getUsername());

//   Serial.println("SOFTWARE SETUP COMPLETE");

//   //Main Loop
//   while (true) {
//     if(BUILTIN_OUTPUT == HIGH){
//         BUILTIN_OUTPUT = LOW;
//     }else{
//         BUILTIN_OUTPUT = HIGH;
//     }
//     digitalWrite(LED_BUILTIN, BUILTIN_OUTPUT);
//     delay(300);
//     button_pressed = false;

//     //Accepting New Users
//     if (button_pressed) {

              
//     //Looking for registered users
//     } else {
//         Serial.println("Looking for connections!");
//         switch (connected)
//         {
//         case 0:
//             //Attempting to connect to the first nextwork
//             Serial.println("Connecting 1");
//             if(user1.connectToHotSpot() == true){
//                 connected = 1;
            
//             //Attempting to connect to the second network
//             Serial.println("Connecting 2");
//             }else if(user2.connectToHotSpot()== true){
//                 connected = 2;
            
//             }
//             break;
            
            
//         case 1:
//             Serial.println("Checking 1");
//             if(user1.isConnected()){
//                 connected = 1;
//             }else{
//                 connected = 0;
//             }
//             break;
//         case 2:
//             Serial.println("Checking 2");
//             if(user2.isConnected()){
//                 connected = 2;
//             }else{
//                 connected = 0;
//             }
//             break;
//         default:
//             Serial.println("DEFAULT! No connections?? Invalid state!");
//             break;
//         }

//     }

//     //Displaying status
//     Serial.print("Connnection State: ");
//     Serial.println(connected);
//     if (connected == 1) {
//         digitalWrite(LED1, HIGH);
//         digitalWrite(LED2, LOW);
//     } else if (connected == 2) {
//         digitalWrite(LED1, LOW);
//         digitalWrite(LED2, HIGH);
//     } else {
//         digitalWrite(LED1, LOW);
//         digitalWrite(LED2, LOW);
//     }


//   }

// }
