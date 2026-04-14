#include "Line.h"


void LineSensor::init(){
    pinMode(frontLeft,INPUT);
    pinMode(frontRight,INPUT);
    pinMode(rearLeft,INPUT);
    pinMode(rearRight,INPUT);
}

bool LineSensor::readLine(int pin){
    line=analogRead(pin); 
    if(line>LINE_THRESHOLD){
        Serial.print("Línea detectada");
        return true;
    }
    else{
        return false;
    }
}