#include "Line.h"

LineSensor Line;

long t;
long d;

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

float LineSensor::readDistance(int trig, int echo){
    t=0;
    for(int i=0; i<10;i++){
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);          //Enviamos un pulso de 10us
        digitalWrite(trig, LOW);
        t = t + pulseIn(echo, HIGH,30000); //obtenemos el ancho del pulso
        delay(1);
         
    }
    d = (t/10)/58; 
    return d;

    
}