#include "ClientIO.hpp"

String readResponseLine(WiFiClient client){
    String buff = "";
    while(client.available()){
        char c = client.read();
        if(c == '\n'){
            return buff;
        }else if(c != '\r'){
            buff += c;
        }
    }
    return buff;
}

bool containsGetRequest(String haystack){
    String needle = "GET";
    for(int i = 0; i < needle.length(); i++){
        if(haystack[i] != needle[i]){
            return false;
        }
    }
    return true;  
}

void writeRegisterHTML(WiFiClient client){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    
    client.println();

    //HTTP content
    client.print("yahoo <a href=\"/H\">here</a> turn the LED on<br>");
    client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");

    client.print("<form id=\"login-form\" action=\"\" method=\"post\">");
    client.print("<input type=\"text\" name=\"username\" id=\"username-field\" placeholder=\"Username\">");
    client.print("<input type=\"password\" name=\"password\" id=\"password-field\" placeholder=\"Password\">");
    client.print("<input type=\"submit\" value=\"Login\" id=\"login-form-submit\">");
    client.print("</form>");

    client.println();


}

bool parseUsernamePassword(String content, char* username, char* password){
    const char* haystack = String2charStar(content);
    if(strstr(haystack, "%") != NULL){ //if % is present, someone was trying to do funky stuff with the submssion
        username="";
        password="";
        return false;
    }
    //getting username
    int first_equals = content.indexOf('=');
    int ampersand = content.indexOf('&');
    int second_equals = content.indexOf('=',ampersand);
    Serial.println(first_equals);
    Serial.println(ampersand);
    Serial.println(second_equals);
    String u = content.substring(first_equals+1, ampersand);
    String p = content.substring(second_equals+1);
    Serial.println(u);
    Serial.println(p);
    // u.toCharArray(username, u.length());
    // p.toCharArray(password, p.length());
    // u += '\0';
    // p +='\0';
    return true;

    


}

const char* String2charStar(String s){
    char* cs;
    memset(cs, 0, 100);
    s.toCharArray(cs, 100);
    const char* ret = cs;
    return ret;

}