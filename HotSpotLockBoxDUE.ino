// /*
//  The circuit:
//   * LCD RS pin to digital pin 12
//   * LCD Enable pin to digital pin 11
//   * LCD D4 pin to digital pin 5
//   * LCD D5 pin to digital pin 4
//   * LCD D6 pin to digital pin 3
//   * LCD D7 pin to digital pin 2
//   * LCD R/W pin to ground
//   * 10K resistor:
//   * ends to +5V and ground
//   * wiper to LCD VO pin (pin 3)

// */

// // include the library code:
// #include <LiquidCrystal.h>
// #include <AltSoftSerial.h>
// #include "SerialCommunication.hpp"


// #define MAX_LEN 100
// // initialize the library by associating any needed LCD interface pin
// // with the arduino pin number it is connected to
// const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// AltSoftSerial mySerial; 

// char receive_buf[MAX_LEN];

// char send_buf[MAX_LEN];

// void blockReadSerial(){
//     while(mySerial.available() <= 0){};
//     readSerial();
// };


// bool readSerial(){
//     bool read= false;
//     while(mySerial.available() > 0){
//         static int num_read = 0;
//         char c = mySerial.read();
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
//         mySerial.println(payload);
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



// void setup() {
//     // set up the LCD's number of columns and rows:
//     Serial.begin(9600);
//     while(!Serial);
//     Serial.println("BEGIN HARDWARE SETUP");
//     lcd.begin(16, 2);
//     // initialize the serial communications:
//     mySerial.begin(9600);
//     Serial.println("HARDWARE SETUP COMPLETE");
    


// }

// void loop() {
//     Serial.println("Waiting for serial");
//     mySerial.readStringUntil('\n').toCharArray(receive_buf, MAX_LEN);
//     Serial.println("Recieved");
//     Serial.print(receive_buf);
//     if(receive_buf == READ_LOGINS){
//         Serial.print("READING LOGINS");
//         //SSID1
//         strcpy(send_buf, "DEADBEEF\n");
//         sendWaitForACK(send_buf);
//         //PASS1
//         strcpy(send_buf, "DEADBEEF\n");
//         sendWaitForACK(send_buf);
//         //SSID2
//         strcpy(send_buf, "Testing\n");
//         sendWaitForACK(send_buf);
//         //PASS2
//         strcpy(send_buf, "12345678\n");
//         sendWaitForACK(send_buf);
//         //WAIT FOR ACK
//     }else if(receive_buf == PRINT_LCD){
//         Serial.print("PRINT TO LCD");
//         lcd.clear();
//         blockReadSerial();
//         lcd.println(receive_buf);
//         mySerial.println(ACK);
//     }else if(receive_buf == WRITE_LOGINS){
//         //TODO WRITE TO EEPROM
//         //SSID1
//         blockReadSerial();
//         Serial.println(receive_buf);
//         mySerial.println(ACK);
//         //PASS1
//         blockReadSerial();
//         mySerial.println(ACK);
//         //SSID2
//         blockReadSerial();
//         mySerial.println(ACK);
//         //PASS2
//         blockReadSerial();
//         mySerial.println(ACK);
//     }
// }








