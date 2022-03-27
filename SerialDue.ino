#include <AltSoftSerial.h>
#include <LiquidCrystal.h>

AltSoftSerial mySerial;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String s = "waiting";

char receive_buf[100];
char send_buf[100];

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

void serialInputFlush(){
    while (mySerial.available() > 0) {
        mySerial.read();
    }
}


void serialOutputFlush(){
    mySerial.flush();
}


int serialReceive(){
    memset(receive_buf, 0, 100);
    int count_read = -1;
    if(mySerial.available() > 0){
         count_read = mySerial.readBytesUntil('\n', receive_buf, 100);
    }
    if(count_read == -1){
        return count_read;
    }
    receive_buf[count_read] = '\0';
    
}

bool serialHandshakeAccept(){
    while(true){
        serialReceive();
        delay(500);
        itoa(strlen(receive_buf), receive_buf, 10);
        setLCDLine(receive_buf, 0);
        LCDShow();
        if(strlen(receive_buf) == 2){
            setLCDLine("B2", 1);
            LCDShow();
            mySerial.write("B2\n");
            break;
        }

    }
    return true;
}

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // initialize the serial communications:
    Serial.begin(9600);
    mySerial.begin(9600);
    serialInputFlush();
    serialOutputFlush();
    pinMode(LED_BUILTIN, OUTPUT);
    setLCDLine("Hello", 0);
    LCDShow();
    serialHandshakeAccept();
    setLCDLine("Mate", 1);
    LCDShow();


}



void loop()  
{ 
    mySerial.write("on\n");
    digitalWrite(LED_BUILTIN,HIGH);
    while(mySerial.available() <=0){};
    int count_read = serialReceive();
    Serial.println(receive_buf);
    Serial.print("Read in: ");
    Serial.println(count_read);
    if(count_read > 0){
        setLCDLine(receive_buf,0 );
        LCDShow();
        delay(100);
    }
    serialInputFlush();
    serialOutputFlush();
    delay (1000);
    mySerial.write("off\n");
    digitalWrite(LED_BUILTIN, LOW);
    while(mySerial.available() <=0){};
   
    count_read = serialReceive();
    Serial.println(receive_buf);
    Serial.print("Read in: ");
    Serial.println(count_read);
    if(count_read > 1){
        setLCDLine(receive_buf,1 );
        LCDShow();
        delay(100);
    }
    serialInputFlush();
    serialOutputFlush();
    delay(1000);
}
