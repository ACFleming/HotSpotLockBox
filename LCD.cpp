#include "LCD.hpp"



void LCD::show(){
    this->clear();
    this->setCursor(0,0);
    this->print(line0);
    this->setCursor(0,1);
    this->print(line1);
}

void LCD::setLine(const char* s, int line=0){
   
   
    if(line == 1){
        memset(this->line1, 0, 21);
        strcpy(this->line1, s);
    }else{
        memset(this->line0, 0, 21);
        strcpy(this->line0,s);
    }
   
}

   
void LCD::setLine(String s, int line = 0){
    if(line == 1){
        s.toCharArray(this->line1, s.length());
    }else{
        s.toCharArray(this->line0, s.length());
    }
}