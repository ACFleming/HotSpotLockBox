// // // #include <Arduino.h>                              // required before wiring_private.h
// // // #include <wiring_private.h>

// // // // Serial2 pin and pad definitions (in Arduino files Variant.h & Variant.cpp)
// // // #define PIN_SERIAL2_RX       (1ul)                // Pin description number for PIO_SERCOM on D1
// // // #define PIN_SERIAL2_TX       (0ul)                // Pin description number for PIO_SERCOM on D0
// // // #define PAD_SERIAL2_TX       (UART_TX_PAD_0)      // SERCOM pad 0 TX
// // // #define PAD_SERIAL2_RX       (SERCOM_RX_PAD_1)    // SERCOM pad 1 RX

// // // // Instantiate the Serial2 class
// // // Uart Serial2(&sercom3, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX);

// // // void setup()
// // // {
// // //   Serial2.begin(115200);          // Begin Serial2 
// // //   pinPeripheral(0, PIO_SERCOM);   // Assign pins 0 & 1 SERCOM functionality
// // //   pinPeripheral(1, PIO_SERCOM);
// // // }

// // // void loop()
// // // {
// // //   if (Serial2.available())        // Check if incoming data is available
// // //   {
// // //     byte byteRead = Serial2.read();    // Read the most recent byte
// // //     Serial2.write(byteRead);           // Echo the byte back out on the serial port
// // //   }
// // // }

// // // void SERCOM3_Handler()    // Interrupt handler for SERCOM3
// // // {
// // //   Serial2.IrqHandler();
// // // }


// String ret;

// void setup(){
//     Serial1.begin(9600);
//     pinMode(LED_BUILTIN, OUTPUT);
// }

// void loop(){
//     if(Serial1.available()){
//         delay(100);
//         ret  = Serial1.readStringUntil('\n');
//     }
//     if(ret=="on"){
//         digitalWrite(LED_BUILTIN, HIGH);
//     }
//     if(ret=="off"){
//         digitalWrite(LED_BUILTIN, LOW);
//     }
// }