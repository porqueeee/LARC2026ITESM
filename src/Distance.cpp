#include "Distance.h"

Distance distance;

void Distance::init(){
    pinMode(FL_TRIG,OUTPUT);
    pinMode(FL_ECHO,INPUT);
    digitalWrite(FL_TRIG,LOW);
    
    pinMode(FR_TRIG,OUTPUT);
    pinMode(FR_ECHO,INPUT);
    digitalWrite(FR_TRIG,LOW);

}

//devuelve true si se detecta un objeto a menos de 40cm
bool Distance::obstacle(int trig1, int echo1, int trig2, int echo2){
    ultrasonic1=0;
    ultrasonic2=0;
    ultrasonic1=readSensor(trig1, echo1);
    Serial.print(ultrasonic1);
    ultrasonic2=readSensor(trig2,echo2);
    Serial.println(ultrasonic2);
    return(ultrasonic1<DIST_THRESHOLD || ultrasonic2<DIST_THRESHOLD);
}


//lee un ultrasónico hasta que obtiene un valor decente
float Distance::readSensor(int trig, int echo){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    float dist= pulseIn(echo, HIGH,30000)/58; 
    if(dist>0 && dist<500){
        return dist;
    }
    else{
        //return LineSensor::readSensor(trig, echo); //lo más probable es que en algun punto se quede atrapado:(
        //algo para checar que esté jalando el sensor
    }
}