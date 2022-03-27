// int counter = 0;



// char receive_buf[100];
// char send_buf[100];


// void serialInputFlush(){
//     while (Serial1.available() > 0) {
//         Serial1.read();
//     }
// }


// void serialOutputFlush(){
//     Serial1.flush();
// }


// int serialReceive(){
//     memset(receive_buf, 0, 100);
//     int count_read = -1;
//     if(Serial1.available() > 0){
//          count_read = Serial1.readBytesUntil('\n', receive_buf, 100);
//     }
//     if(count_read == -1){
//         return count_read;
//     }
//     receive_buf[count_read] = '\0';
// }


// bool serialHandshakeInit(){
//     while(true){
//         Serial1.write("B1\n");
//         int count = serialReceive();
//         if(count > 0){
//                 digitalWrite(7, HIGH);
//                 delay(100);
//                 digitalWrite(7, LOW);
//         }
//         delay(500);
//         if(receive_buf == "B2"){
//             break;
//         }
//     }
//     return true;
    

// }


// void setup(){
//     Serial1.begin(9600);
//     delay(500);
//     pinMode(LED_BUILTIN, OUTPUT);
//     pinMode(5, OUTPUT);
//     pinMode(7, OUTPUT);
//     digitalWrite(5, HIGH);
//     serialHandshakeInit();
//     delay(500);
//     digitalWrite(5, LOW);
// }

// void loop(){
//     while(Serial1.available() <=0){};
//     int count_read = serialReceive();
//     delay(100);
//     Serial.println(receive_buf);
//     counter = (counter +1 )%16;
//     Serial.println(counter);
//     if(receive_buf=="on"){
//         digitalWrite(LED_BUILTIN, HIGH);
//         digitalWrite(5, LOW);
//         Serial1.write("going high\n");
//     }else if(receive_buf=="off"){
//         digitalWrite(LED_BUILTIN, LOW);
//         digitalWrite(5, HIGH);
//         Serial1.write("going low\n");
//     }
// }