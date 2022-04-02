#include "LCD.hpp"



void LCD::show(){
    this->clear();
    this->setCursor(0,0);
    this->print(line0);
    this->setCursor(0,1);
    this->print(line1);
}



   
void LCD::setLine(String s, int line = 0){
    if(line == 1){
        this->line1 = s;
    }else{
        this->line0 = s;
    }
}



void LCD::setBothLines(String s1, String s2){
    this->setLine(s1,0);
    this->setLine(s2,1);
}