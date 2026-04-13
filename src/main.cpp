#include "Arduino.h"
#include "IMU.h"
#include "Movement.h"
#include "PID.h"
#include "SensorColor.h"

//Todo lo del movimiento - Movement incluye PID, Motors, IMU y config
Movement robot; //Crea un objeto de la clase Movement  

SensorColor Color; //crea un objeto de la clase Sensor Color


void setup() {
    Serial.begin(9600);
    Serial.println("Comunicación serial iniciada");
    robot.init(); //inicializa motores, pid y IMU  
    robot.moveForwardStraight(127, 5000); //Se mueve hacia adelante con control P, a mitad de velocidad

}

void loop() {

}