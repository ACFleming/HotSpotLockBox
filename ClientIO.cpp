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


void detailsForm(WiFiClient client){
    client.print("<form id=\"login-form\" action=\"\" method=\"post\">");    
    client.print("<label>Network name (SSID):</label>");
    client.print("<input type=\"text\" name=\"username\" id=\"username-field\" placeholder=\"Username\">");
    client.print("<br>");
    client.print("<label>Network password:</label>");
    client.print("<input type=\"password\" name=\"password\" id=\"password-field\" placeholder=\"Password\">");
    client.print("<br>");
    client.print("<label>Retype password: </label>");
    client.print("<input type=\"password\" name=\"password2\" id=\"password-field\" placeholder=\"Password\">");
    client.print("<input type=\"submit\" value=\"Login\" id=\"login-form-submit\">");
    client.print("<br>");
    client.print("<br>");
    client.print("</form>");
}

void lockerAvailability(WiFiClient client, bool locker1_free, bool locker2_free){
    client.print("Locker 1: ");
    if(locker1_free){
        client.print("Free");
    }else{
        client.print("Owned");
    }
    client.print("Locker 2: ");
    if(locker2_free){
        client.print("Free");
    }else{
        client.print("Owned");
    }
}

void registerHref(WiFiClient client){
    client.print("<a href=\"/register\">Click to register</a>");
}

void unregisterHref(WiFiClient client){
    client.print("<a href=\"/unregister\">Click to unregister</a>");
}

void registerTitle(WiFiClient client){
    client.print("<h1>Fill in the details to register your Hotspot to a locker</h1>");
    client.print("<h2>You will be assigned the next available number</h2>");
}

void unregisterTitle(WiFiClient client){
    client.print("<h1>Fill in the details to unregister your Hotspot from a locker</h1>");
    client.print("<h2>Your locker will be open to new registrations</h2>");
}

void registerSuccess(WiFiClient client,int new_locker_num){
    client.print("<h1>Register Successful</h1>");
    client.print("<h2>Your locker number is</h2>");
    client.print(new_locker_num);

}

void unregisterSuccess(WiFiClient client){
    client.print("<h1>Unregister Successful</h1>");
    client.print("<h2>Your locker is open to new registrations</h2>");

}



void writeRegisterHTML(WiFiClient client, bool locker1_free, bool locker2_free){
    //HTTP header
    client.print("HTTP/1.1 200 OK");
    client.print("Content-type:text/html");
    
    client.println();

    registerTitle(client);
    detailsForm(client);
    unregisterHref(client);
    lockerAvailability(client, locker1_free, locker2_free);
    client.println();


}




void writeUnregisterHTML(WiFiClient client, bool locker1_free, bool locker2_free){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    
    client.println();

    unregisterTitle(client);
    detailsForm(client);
    registerHref(client);
    lockerAvailability(client, locker1_free, locker2_free);
    client.println();
}


void writeHomeHTML(WiFiClient client,  bool locker1_free, bool locker2_free){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    registerHref(client);
    unregisterHref(client);
    lockerAvailability(client, locker1_free, locker2_free);
    client.println();  

}


int parseUsernamePassword(String content, String &username, String &password, String& password2){

    if(content.indexOf("%") != -1){ //if % is present, someone was trying to do funky stuff with the submssion
        username="";
        password="";
        password2="";
        return -2;
    }
    //getting username
    int equals1 = content.indexOf('=');
    int and1 = content.indexOf('&');
    int equals2 = content.indexOf('=',and1);
    int and2 = content.indexOf('&', equals2);
    int equals3 = content.indexOf('=',and2);


    username = content.substring(equals1+1, and1);
    password = content.substring(equals2+1, and2);
    password2 = content.substring(equals3+1);
    Serial.println(username);
    Serial.println(password);
    Serial.println(password2);
    if(password != password2){     //passwords dont match
        username="";
        password="";
        password2="";
        return -1;
    }

    return 1;

    


}

char* String2charStar(String s){
    char* cs;
    memset(cs, 0, 100);
    s.toCharArray(cs, 100);

    return cs;

}