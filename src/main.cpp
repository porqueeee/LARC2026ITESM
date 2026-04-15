#include "Arduino.h"
#include "IMU.h"
#include "Movement.h"
#include "PID.h"
#include "SensorColor.h"
#include "Line.h"

//Todo lo del movimiento - Movement incluye PID, Motors, IMU y config
Movement robot; //Crea un objeto de la clase Movement  

SensorColor Color; //crea un objeto de la clase Sensor Color

RobotState currentState = INIT; // Estado inicial del robot

#include "IMU.h"


void setup() {
    //cambio de frecuencia timer 3 TCCR3B = (TCCR3B & 0b11111000) | 0x01;
    //cambio de frecuencia timer 4 TCCR4B = (TCCR4B & 0b11111000) | 0x01;
    Serial.begin(9600);
    Serial.println("Programa Inicializado");
    robot.init(); //inicializa motores, pid y IMU  
    //robot.moveForwardStraight(100,1000

    //robot.moveRightStraight(100,2000);
    //robot.moveForwardStraight(100,2000);
    //robot.moveLeftStraight(100,200);


}

void RunRobot(){
    switch(currentState) {
        case INIT:
            currentState = EXIT_BOX;
            break;

        case EXIT_BOX:
            Serial.print("Exit Box");
            robot.moveForwardUntilBackLine(100);
            delay(1500);
            currentState = ALLING_RIGHT;
            break;

        case ALLING_RIGHT:
            Serial.print("Allign Right");
            robot.moveRightUntilRightLine(defaultspeed);
            currentState=CLEAR_OBSTACLES;

        case CLEAR_OBSTACLES:
            Serial.print("Clear obstacles");
            robot.moveLeftUntilClear(defaultspeed);
            currentState=COMPLETE;
        case COMPLETE:
            robot.stop();
            break;
        default:
            break;
    }
}

void TestSquare(){
    robot.moveLeft(defaultspeed,700);
    delay(200);
    robot.moveRight(defaultspeed, 700);
    delay(200);
    robot.moveForward(defaultspeed,700);
    delay(200);
    robot.moveBackward(defaultspeed,700);
    delay(2000);
}

void TestSquareStraight(){
    robot.moveLeftStraight(defaultspeed,700);
    delay(200);
    robot.moveRightStraight(defaultspeed, 700);
    delay(200);
    robot.moveForwardStraight(defaultspeed,700);
    delay(200);
    robot.moveBackwardStraight(defaultspeed,700);
    delay(2000);
}


void loop() {
    
    //RunRobot();
    //robot.moveLeftUntilClear(80);
    //robot.moveRightUntilRightLine(100);
    //robot.moveLeftStraight(defaultspeed,1000);
    //TestSquareStraight();
    robot.moveLeftUntilClear(defaultspeed);
    Serial.print("Clear! :)");
    delay(1000);

}