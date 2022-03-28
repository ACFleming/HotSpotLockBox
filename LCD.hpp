#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>

class LCD : public LiquidCrystal{
private:
    char line0[21];
    char line1[21]; 
    

public:
    LCD(int rs, int en, int d4, int d5, int d6, int d7): LiquidCrystal(rs,en,d4,d5,d6,d7) {};
    void show();
    void setLine(const char* s, int line);
    void setLine(String s, int line);
};

#endif