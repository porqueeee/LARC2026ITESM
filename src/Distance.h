#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include "config.h"

class Distance{
    public:
    void init();
    float readSensor(int trig, int echo);
    bool obstacle(int trig1, int echo1, int trig2, int echo2);
    long ultrasonic1;
    long ultrasonic2;

};


extern Distance distance;

#endif