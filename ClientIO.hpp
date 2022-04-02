#ifndef CLIENTIO_H
#define CLIENTIO_H

#include <WiFi101.h>

//Functions to simplify ClientIO
String readResponseLine(WiFiClient client);
bool containsGetRequest(String s);

void writeRegisterHTML(WiFiClient client);
void writeRegisterHTML(WiFiClient client, bool locker1_free, bool locker2_free);
void writeUnregisterHTML(WiFiClient client);
void writeUnregisterHTML(WiFiClient client, bool locker1_free, bool locker2_free);
void writeHomeHTML(WiFiClient client);
void writeHomeHTML(WiFiClient client,  bool locker1_free, bool locker2_free);
void detailsForm(WiFiClient client);
void registerHref(WiFiClient client);
void unregisterHref(WiFiClient client);

char* String2charStar(String s);
int parseUsernamePassword(String content, String &username, String &password, String& password2);




#endif