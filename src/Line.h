#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "config.h"

class LineSensor{
    public:
    void init();
    bool readLine(int pin);
    int line;

};

extern LineSensor Line;


#endif 