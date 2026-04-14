#include "Arduino.h"
#include "IMU.h"
#include "Movement.h"
#include "PID.h"
#include "SensorColor.h"
<<<<<<< Updated upstream
#include "Line.h"

//Todo lo del movimiento - Movement incluye PID, Motors, IMU y config
Movement robot; //Crea un objeto de la clase Movement  

SensorColor Color; //crea un objeto de la clase Sensor Color
=======
#include "Sensors.h"
#include "IMU.h"
>>>>>>> Stashed changes


void setup() {
    //cambio de frecuencia timer 3 TCCR3B = (TCCR3B & 0b11111000) | 0x01;
    //cambio de frecuencia timer 4 TCCR4B = (TCCR4B & 0b11111000) | 0x01;
    Serial.begin(9600);
    Serial.println("Comunicación serial iniciada");
    robot.init(); //inicializa motores, pid y IMU  
    robot.moveForwardUntilBackLine(100);
    Serial.print("Línea encontrada");


    //robot.moveRightStraight(100,2000);
    //robot.moveForwardStraight(100,2000);
    //robot.moveLeftStraight(100,200);


}

void loop() {

}