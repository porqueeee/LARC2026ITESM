#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "config.h"

class LineSensor{
    public:

    //Inicializa todos los sensores
    void init();
    //Lee el sensor de línea
    bool readLine(int pin);
    //guarda el valor del analog read de línea
    int line;

    //Lee sensor ultrasónico
    bool readDistance(int trig, int echo);

};

extern LineSensor Line;


#endif 