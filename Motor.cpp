#include "Motor.hpp"


int Motor::clamp(int a){
    if(a < 0){
        return 0;
    }
    if(a > 180){
        return 180;
    }
    return a;
}

void Motor::setToAngle(int a){
    int target = this->clamp(a);
    if(this->curr_angle < target){
        
        while(this->curr_angle < target){
            this->curr_angle++;
            this->write(curr_angle);
            delay(15);
        }
    }else if(this->curr_angle > target){
        
        while(this->curr_angle > target){
            this->curr_angle--;
            this->write(curr_angle);
            delay(15);
        }
    }
}

