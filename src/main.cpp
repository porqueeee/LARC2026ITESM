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
    //robot.moveForwardStraight(100,1000)

    //robot.moveRightStraight(100,2000);
    //robot.moveForwardStraight(100,2000);
    //robot.moveLeftStraight(100,200);


}

void RunRobot(){
    switch(currentState) {
        case INIT:
            //no sirve realmente porque quiero inicializar todo en el setup
            // para hacer pruebas, pero así está lindo
            currentState = EXIT_BOX;
            break;

        case EXIT_BOX:
            //Se mueve hacia adelante hasta que detecta la línea trasera, frena en seco
            Serial.print("Exit Box");
            robot.moveForwardUntilBackLine(100);
            delay(1500);
            currentState = ALIGN_RIGHT;
            break;

        case ALIGN_RIGHT:
            //Se mueve hacia la derecha hasta llegar a la línea, frena en seco
            Serial.print("Align Right");
            robot.moveRightUntilRightLine(defaultspeed);
            currentState=CLEAR_OBSTACLES;

        case CLEAR_OBSTACLES:
            Serial.print("Clear obstacles");
            robot.moveLeftUntilClear(defaultspeed);
            currentState=COMPLETE;

        case REALIGN_RIGHT:
        //Se mueve hacia la derecha hasta llegar a la línea, frena en seco
            Serial.print("Realign Right");
            robot.moveRightUntilRightLine(defaultspeed);
            currentState=COLLECT_LINE;

        case COLLECT_LINE:
        //Se mueve hacia adelante hasta llegar a la línea del árbol
            Serial.print("Get to collect line");
            robot.moveForwardUntilFrontLine(defaultspeed);
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
    TestSquare();
    //robot.moveLeftUntilClear(defaultspeed);
    //Serial.print("Clear! :)");
    //delay(1000);
    //robot.evilstop(defaultspeed);
}