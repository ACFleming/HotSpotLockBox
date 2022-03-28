#ifndef MOTOR_H
#define MOTOR_H
#include <Servo.h>
#include "Arduino.h"


class Motor: public Servo{
    private:
        int curr_angle = 90;
        int clamp(int a);
    public:
        void setToAngle(int a);

};

#endif