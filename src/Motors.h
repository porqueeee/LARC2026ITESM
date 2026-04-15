#ifndef MOTORS_H
#define MOTORS_H

/////////////////////////////
///////NO CAMBIAR ///////////
////////////////////////////

#include <Arduino.h> 
#include "config.h"

class Motors {
public:
    void init();
    void moveForward(int speed,int output);
    void moveBackward(int speed, int output);
    void moveLeft(int speed, int output);
    void moveRight(int speed, int output);
    void print(int speed, int output);
    void stop();
    
private:
    void setMotor(int in1, int speed, int pwm);
    void setSpeed(int speed);
};

extern Motors motors;

#endif