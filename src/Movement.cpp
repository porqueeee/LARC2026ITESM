#include "Movement.h"

Movement movement;
extern IMU imu;  

void Movement::init() {
    // 1. Inicializar periféricos primero
    motors.init();
    imu.init(); 
    
    // 2. Inicializar PID de rumbo
    // Kp, Ki, Kd, OutputMin, OutputMax
    //Definición del PID:
    headingPID = PID(2.0, 0.0, 0.0, -80, 80);
    
    // 3. Fijar el setpoint inicial
    updateTargetHeading();
}

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
    //targetHeading = imu.getHeading();
    targetHeading=0;
}


//control proporcional, todo se hace en esta función
int Movement::calculateHeadingCorrection() {
    float currentHeading = imu.getHeading();
    float error = targetHeading - currentHeading;
    
    // Normalizar error a -180 a 180
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    
    // PID simple (solo proporcional)
    int correction = (int)(error * 4.0); // Kp = 2.0
    return constrain(correction, -50, 50);
}

// NUEVA FUNCIÓN: Corrección PID completa - se guarda en PID.h y PID.cpp
//trabaja con los mismos datos, pero agrega el control integral y derivado.
//debería poder reemplaxar a calculateHeadingCorrection() sin problemas una vez calibrada.
float Movement::calculateHeadingCorrectionPID() {
    float currentHeading = imu.getHeading();
    float error = targetHeading - currentHeading;
    
    // Normalizar error a -180 a 180
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    
    return headingPID.compute(error);
}


//Todas estas funciones se mueven por 5 segundos, le quiero cambiar para que el tiempo sea configurable
//La velocidad de las llantas también afecta cuanto tardas en llegar a un lugar, podría intentar usar el acelerómetro 
//calibrar el tiempo con base a la velocidad o ignorar el problema y depender de los ultrasónicos como paro de emergencia

void Movement::moveForwardStraight(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        float correction=calculateHeadingCorrection();
        motors.moveForward(speed, correction);
        delay(10);
    }
    motors.stop();
}

void Movement::moveBackwardStraight(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        motors.moveBackward(speed,calculateHeadingCorrectionPID());
        delay(10);
    }
    motors.stop();
}


void Movement::moveLeftStraight(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        motors.moveLeft(speed,calculateHeadingCorrectionPID());
        delay(10);
    }
    motors.stop();
}

void Movement::moveRightStraight(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < 5000) {
        motors.moveRight(speed,calculateHeadingCorrectionPID());
        delay(10);
    }
    motors.stop();
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
    motors.stop();
}

void Movement::moveBackward(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        motors.moveBackward(speed,0);
        delay(10);
    }
    motors.stop();
}

void Movement::moveLeft(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
        motors.moveLeft(speed,0);
        delay(10);
    }
    motors.stop();
}

void Movement::moveRight(int speed, unsigned long time) {
    unsigned long startTime = millis();
    while (millis() - startTime < 5000) {
        motors.moveRight(speed,0);
        delay(10);
    }
    motors.stop();
}  

/*
void Movement::moveRightStraightPID(int speed) {
    updateTargetHeading();
    headingPID.setSetpoint(0);
    headingPID.reset();
    
    unsigned long startTime = millis();
    
    while (millis() - startTime < 6000) {
        sensors.updateAll();
        
        float correction = calculateHeadingCorrectionPID();
        motors.moveDirection(speed, 0, (int)correction);
        delay(10);
    }
    motors.stop();
}
*/

void Movement::stop() {
    motors.stop();
    Serial.println("Robot detenido");
}