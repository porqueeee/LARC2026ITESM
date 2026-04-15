
#include "Movement.h"
Movement movement;
extern IMU imu;  
extern LineSensor Line;

void Movement::init() {
    // 1. Inicializar periféricos primero
    motors.init();
    imu.init(); 
    Line.init();
    
    // 2. Inicializar PID de rumbo
    // Kp, Ki, Kd, OutputMin, OutputMax
    //Definición del PID:
    headingPID = PID(4.0, 0.0, 0.0, -50, 50);
    headingPID.setSetpoint(0);
    
    // 3. Fijar el setpoint inicial
    updateTargetHeading();
}

//cambia los valores del pid, hasta el momento no se ha utilizado
void Movement::setHeadingPIDGains(float kp, float ki, float kd) {
    //el PID tiene constantes por default, esto es para adaptarlo durante el código
    headingPID.setGains(kp, ki, kd);
    Serial.print("Heading PID configurado: Kp=");
    Serial.print(kp);
    Serial.print(", Ki=");
    Serial.print(ki);
    Serial.print(", Kd=");
    Serial.println(kd);
}

void Movement::updateTargetHeading() {
    targetHeading = imu.getHeading();
    //targetHeading=0;
}


//control proporcional, todo se hace en esta función
/*int Movement::calculateHeadingCorrection() {
    float currentHeading = imu.getHeading();
    float error = targetHeading - currentHeading;
    
    // Normalizar error a -180 a 180
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    
    // PID simple (solo proporcional)
    int correction = (int)(error * 4.0); //Control con KP
    return constrain(correction, -50, 50);
}*/

// NUEVA FUNCIÓN: Corrección PID completa - se guarda en PID.h y PID.cpp
//trabaja con los mismos datos, pero agrega el control integral y derivado.
//debería poder reemplaxar a calculateHeadingCorrection() sin problemas una vez calibrada.
float Movement::calculateHeadingCorrectionPID() {
    float currentHeading = imu.getHeading();
    // Le pasamos la lectura directa al PID, él se encarga de la matemática
    return headingPID.compute(currentHeading);
}


//PID +  DETECCIÓN DE LÍNEA
void Movement::moveForwardUntilBackLine(int speed) {
    headingPID.reset();
    while (true) {
        bool left = Line.readLine(rearLeft);
        bool right = Line.readLine(rearRight);

        if(left || right){
            if (left){
                Serial.print("Izquierda");
                Serial.println(" ");
            }
            if (right){
                Serial.print("Derecha");
                Serial.println(" ");
            }
            break;
        }
        else{

            float correction=calculateHeadingCorrectionPID();
            motors.moveForward(speed, correction);
            delay(10);
        }
    }
    moveBackward(brakespeed,20);
    stop();
}

void Movement::moveRightUntilRightLine(int speed) {
    headingPID.reset();
    updateTargetHeading();
    while (true) {
        if(Line.readLine(rearRight)==true){
            break;
        }
        else{
            //El pid se calcula dentro de este cliclo while
            float correction=calculateHeadingCorrectionPID();
            motors.moveRight(speed, correction);
            delay(10);
        }
    }
    moveLeft(brakespeed,braketime);
    stop();
}

//Es lo mismo que moveForwardUntilBackLine pero con los sensores de línea de enfrente
void Movement::moveForwardUntilFrontLine(int speed){
    headingPID.reset();
    while (true) {
        bool left = Line.readLine(frontLeft);
        bool right = Line.readLine(frontRight);

        if(left || right){
            if (left){
                Serial.print("Izquierda");
                Serial.println(" ");
            }
            if (right){
                Serial.print("Derecha");
                Serial.println(" ");
            }
            break;
        }
        else{

            float correction=calculateHeadingCorrectionPID();
            motors.moveForward(speed, correction);
            delay(10);
        }
    }
    moveBackward(brakespeed,20);
    stop();
}

void Movement::moveLeftUntilClear(int speed){
    // no lleva delay porque leer el ultrasónico es muy tardado
    headingPID.reset();
    updateTargetHeading();

    while(true){
        stop(); //Detiene los motores
        if(Line.readDistance(FL_TRIG,FL_ECHO)){ //Lee el sensor ultrasónico
            //usa el pid de la función moveLeftStraight
            moveLeftStraight(defaultspeed,500); //Se mueve con PID por cantidad de tiempo
        }
        else{
            break;
        }
    }

    moveRight(brakespeed,braketime);
    stop();
}

//PID INTEGRADO :) Hasta el momento con kp=4 ki=0 y kd=0
void Movement::moveForwardStraight(int speed, unsigned long time) {
    headingPID.reset();
    updateTargetHeading();
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        float correction=calculateHeadingCorrectionPID();
        motors.moveForward(speed, correction);
        delay(10);
    }
    stop();
}

void Movement::moveBackwardStraight(int speed, unsigned long time) {
    headingPID.reset();
    updateTargetHeading();
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        float correction=calculateHeadingCorrectionPID();
        motors.moveBackward(speed, correction);
        delay(10);
    }
    stop();
}

void Movement::moveLeftStraight(int speed, unsigned long time) {
    headingPID.reset();
    updateTargetHeading();
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        float correction=calculateHeadingCorrectionPID();
        motors.moveLeft(speed,correction);
        delay(10);
    }
    stop();
}

void Movement::moveRightStraight(int speed, unsigned long time) {
    headingPID.reset();
    updateTargetHeading();
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        float correction=calculateHeadingCorrectionPID();
        motors.moveRight(speed,correction);
        delay(10);
    }
    stop();
}  

//
// Funciones de movimiento par apruebas (sin p ni pid)
//
void Movement::moveForward(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        motors.moveForward(speed, 0);
        delay(10);
    }
    stop();
}

void Movement::moveBackward(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        motors.moveBackward(speed,0);
        delay(10);
    }
    stop();
}

void Movement::moveLeft(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        motors.moveLeft(speed,0);
        delay(10);
    }
    stop();
}

void Movement::moveRight(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        motors.moveRight(speed,0);
        delay(10);
    }
    stop();
}  


void Movement::stop() {
    motors.stop();
    Serial.println("Robot detenido");
}

void Movement::evilstop(int speed) {
    motors.evilstop(speed);
}