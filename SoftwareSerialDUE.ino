#include <AltSoftSerial.h>

AltSoftSerial mySerial;

void setup()  
{
  mySerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
} 
void loop()  
{ 
    mySerial.write("on\n");
    digitalWrite(LED_BUILTIN,HIGH);
    delay (1000);
    mySerial.write("off\n");
    digitalWrite(LED_BUILTIN, LOW);
    delay (500);
}