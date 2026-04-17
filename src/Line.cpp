#include "Line.h"

LineSensor Line;

void LineSensor::init(){
    pinMode(frontLeft,INPUT);
    pinMode(frontRight,INPUT);
    pinMode(rearLeft,INPUT);
    pinMode(rearRight,INPUT);

    //pines del ultrasónico 
    pinMode(FL_ECHO, INPUT);
    pinMode(FL_TRIG, OUTPUT);
    digitalWrite(FL_TRIG, LOW);
}


//devuelve true si se detecta una línea
int LineSensor::readLine(int pin){
    line=analogRead(pin); 
    //if(line>LINE_THRESHOLD){
      //  return true;
    //}
    //else{
      //  return false;
    //}
    return line;
}