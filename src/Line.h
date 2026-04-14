#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "config.h"

class LineSensor{
    public:
    void init();
    bool readLine(int pin);
    int line;
    float readDistance(int trig, int echo);

};

extern LineSensor Line;


#endif 