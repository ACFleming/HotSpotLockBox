#ifndef CLIENTIO_H
#define CLIENTIO_H

#include <WiFi101.h>

//Functions to simplify ClientIO
String readResponseLine(WiFiClient client);
bool containsGetRequest(String s);
void writeRegisterHTML(WiFiClient client);
const char* String2charStar(String s);
bool parseUsernamePassword(String content, char* username, char* password);




#endif