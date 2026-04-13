#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "config.h"

class Motors {
public:
    void init();
    void moveForward(int speed,int output);
    void moveBackward(int speed);
    void moveLeft(int speed);
    void moveRight(int speed);
    void stop();
    
private:
    void setMotor(int in1, int speed, int pwm);
    void setSpeed(int speed);
};

extern Motors motors;

#endif