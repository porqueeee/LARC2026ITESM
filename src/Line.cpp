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
bool LineSensor::readDistance(int trig, int echo){
    t=0;
    //Toma 10 medidas del ultrasónico
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
    Serial.print("Dist: ");
    Serial.println(d);
    return (d<DIST_THRESHOLD);

    
}