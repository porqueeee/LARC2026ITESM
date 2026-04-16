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


//devuelve true si se detecta una línea
bool LineSensor::readLine(int pin){
    line=analogRead(pin); 
    if(line>LINE_THRESHOLD){
        return true;
    }
    else{
        return false;
    }
}

//devuelve true si se detecta un objeto a menos de 40cm
bool LineSensor::readDistance(int trig, int echo, int trig2, int echo2){
    t=0;
    //Toma 10 medidas del ultrasónico
    for(int i=0; i<10;i++){
        digitalWrite(trig, LOW);
        digitalWrite(trig2, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        digitalWrite(trig2, HIGH);
        delayMicroseconds(10);          //Enviamos un pulso de 10us
        digitalWrite(trig, LOW);
        digitalWrite(trig2, LOW);
        
        float dist= pulseIn(echo, HIGH)/58;
        float dist1= pulseIn(echo, HIGH)/58;
        
        if(dist>0 && dist<500){
            d+=d; // suma las distancias obtenidas
            t=t+1; //lleva cuenta de cuantos numeros guarda
        }

        if(dist1>0 && dist1<500){
            d+=d;
            t=t+1;
        }

        delay(1);    
    }

    d = d/t; 
    Serial.print("Dist: ");
    Serial.println(d);
    return (d<DIST_THRESHOLD);

    
}