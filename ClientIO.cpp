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



bool errorDetails(WiFiClient client, int error_type){
    if(error_type == -1){
        client.println("<p style=\"color :red; \"> Passwords did not match</p>");

    }else if(error_type == -2){
        client.println("<p style=\"color :red; \"> Invalid characters in form</p>");
    }else if(error_type == -3){
        client.println("<p style=\"color :red; \"> Registration Failed. Network name already taken</p>");
    }else if(error_type == -4){
        client.println("<p style=\"color :red; \"> Unregistration Failed. Network name not recognised</p>");
    }
}

void detailsForm(WiFiClient client){
    client.println("<form id=\"login-form\" action=\"\" method=\"post\">");    
    client.println("<label>Network name (SSID):</label>");
    client.println("<input type=\"text\" name=\"username\" id=\"username-field\" placeholder=\"Username\">");
    client.println("<br>");
    client.println("<label>Network password:</label>");
    client.println("<input type=\"password\" name=\"password\" id=\"password-field\" placeholder=\"Password\">");
    client.println("<br>");
    client.println("<label>Retype password: </label>");
    client.println("<input type=\"password\" name=\"password2\" id=\"password-field\" placeholder=\"Password\">");
    client.println("<input type=\"submit\" value=\"Login\" id=\"login-form-submit\">");
    client.println("<br>");
    client.println("<br>");
    client.println("</form>");
}

void lockerAvailability(WiFiClient client, bool locker1_free, bool locker2_free){
    client.println("<br>");
    client.println("Locker 1: ");
    if(locker1_free){
        client.println("Free");
    }else{
        client.println("Owned");
    }
    client.println("<br>");
    client.println("Locker 2: ");
    if(locker2_free){
        client.println("Free");
    }else{
        client.println("Owned");
    }
}

void registerHref(WiFiClient client){
    client.println("<a href=\"/register\">Click to register</a>");
}

void unregisterHref(WiFiClient client){
    client.println("<a href=\"/unregister\">Click to unregister</a>");
}

void registerTitle(WiFiClient client){
    client.println("<h1>Fill in the details to register your Hotspot to a locker</h1>");
    client.println("<h2>You will be assigned the next available number</h2>");
}

void unregisterTitle(WiFiClient client){
    client.println("<h1>Fill in the details to unregister your Hotspot from a locker</h1>");
    client.println("<h2>Your locker will be open to new registrations</h2>");
}

void registerSuccess(WiFiClient client,int new_locker_num){
    client.println("<h1>Register Successful</h1>");
    client.println("<h2>Your locker number is</h2>");
    client.println(new_locker_num);

}

void unregisterSuccess(WiFiClient client){
    client.println("<h1>Unregister Successful</h1>");
    client.println("<h2>Your locker is open to new registrations</h2>");

}

void writeRegisterHTML(WiFiClient client){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    
    client.println();

    registerTitle(client);
    detailsForm(client);
    unregisterHref(client);

    client.println();


}

void writeRegisterHTML(WiFiClient client, bool locker1_free, bool locker2_free, int error_type){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    
    client.println();
    errorDetails(client, error_type);
    registerTitle(client);
    detailsForm(client);
    unregisterHref(client);
    lockerAvailability(client, locker1_free, locker2_free);
    
    client.println();


}



void writeUnregisterHTML(WiFiClient client){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    
    client.println();

    unregisterTitle(client);
    detailsForm(client);
    registerHref(client);
    client.println();
}


void writeUnregisterHTML(WiFiClient client, bool locker1_free, bool locker2_free, int error_type){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    
    client.println();
    errorDetails(client, error_type);
    unregisterTitle(client);
    detailsForm(client);
    registerHref(client);
    lockerAvailability(client, locker1_free, locker2_free);
    client.println();
}

void writeHomeHTML(WiFiClient client){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    registerHref(client);
    client.println("<br>");
    unregisterHref(client);
    client.println();  

}


void writeHomeHTML(WiFiClient client,  bool locker1_free, bool locker2_free){
    //HTTP header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

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