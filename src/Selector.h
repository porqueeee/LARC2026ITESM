#ifndef SERVO_H 
#define SERVO_H 

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

class Selector{
    public:
    void init();
    void grab(String color);

    private:
    Servo servo1;
    Servo servo2;
};

extern Selector selector;

#endif