#include "Arduino.h"
#include "IMU.h"
#include "Movement.h"
#include "PID.h"
#include "Line.h"
#include "SensorColor.h"

//Todo lo del movimiento - Movement incluye PID, Motors, IMU y config
Movement robot; //Crea un objeto de la clase Movement  

RobotState currentState = INIT; // Estado inicial del robot, se usa en el case switch

#include "IMU.h"

LineSensor line;

Distance ultrasonic;

SensorColor sensorColor;


void setup() {

    Serial.begin(9600);
    Serial.println("Programa Inicializado");
    robot.init(); //inicializa motores, pid y IMU  
}


//TODO LO DEL ROBOT
void RunRobot(){
    switch(currentState) {
        case INIT:
            //no sirve realmente porque quiero inicializar todo en el setup
            // para hacer pruebas, pero así puedo incorporar lo de los botones luego
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
            currentState=BEAN;
        
        case BEAN:
            Serial.print("Getting beans");
            robot.agarrarGrano();
            currentState=COMPLETE;

        case COMPLETE:
            robot.stop();
            break;

        default:
            break;
    }
}

//Prueba dos sensores ultrasónicos (no la he probado)
void TestUltrasonic(){
    ultrasonic.obstacle(FL_TRIG,FL_ECHO, FR_TRIG, FR_ECHO);
    //delay(100);
}

//Prueba todos los de línea a la vez (Si jala)
void TestLine(){
    Serial.print(line.readLine(rearLeft));
    Serial.print(line.readLine(frontLeft));
    Serial.print(line.readLine(rearRight));
    Serial.println(line.readLine(frontRight));
    delay(100);
}

//Prueba los movimientos sin PID
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

//Prueba los movimientos con PID
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
    //TestSquare();
    //TestLine();
    //TestUltrasonic();
    //robot.moveLeftUntilClear(defaultspeed);
    //Serial.print("Clear! :)");
    //delay(1000);
    //robot.evilstop(defaultspeed);

    robot.moveForwardUntilBackLine(100);
}