#include "Motors.h"

/////////////////////////////
///////NO CAMBIAR ///////////
////////////////////////////

Motors motors;

void Motors::init() {
    // Configurar pines de motores como salida
    pinMode(MOTOR_FL_IN1, OUTPUT);
    pinMode(MOTOR_FL_PWM, OUTPUT);
    
    pinMode(MOTOR_FR_IN1, OUTPUT);
    pinMode(MOTOR_FR_PWM, OUTPUT);
    
    pinMode(MOTOR_RL_IN1, OUTPUT);
    pinMode(MOTOR_RL_PWM, OUTPUT);
    
    pinMode(MOTOR_RR_IN1, OUTPUT);
    pinMode(MOTOR_RR_PWM, OUTPUT);
    
    stop();
}


// el pin in1 funciona como "enable", la dirección y velocidad se controlan con pwm
//el usuario ingresa un valor entre -127 y 127, negativo significa hacia atrás, positivo hacia adelante, 0 es frenado
//para mayor seguridad el frenado también apaga el pin enable 

void Motors::setMotor(int in1, int speed, int pwm) {
    speed = constrain(speed, -127, 127);

    if (speed == 0) {
        analogWrite(pwm, 0);
        digitalWrite(in1, LOW); 
        return;
    }

    if (speed > 0) {
        digitalWrite(in1, HIGH); 
    } else {
        digitalWrite(in1, HIGH); 
    }
    analogWrite(pwm, speed +127);
    
} 

//Está bien
void Motors::moveForward(int speed,int output) {
    setMotor(MOTOR_FL_IN1, 0, MOTOR_FL_PWM);
    setMotor(MOTOR_FR_IN1, (speed+output), MOTOR_FR_PWM);
    setMotor(MOTOR_RL_IN1, 0, MOTOR_RL_PWM);
    setMotor(MOTOR_RR_IN1, (speed-output), MOTOR_RR_PWM);
    print(speed,output);
}

void Motors::moveBackward(int speed, int output) {
    setMotor(MOTOR_FL_IN1, 0, MOTOR_FL_PWM);
    setMotor(MOTOR_FR_IN1, -(speed-output), MOTOR_FR_PWM);
    setMotor(MOTOR_RL_IN1, 0, MOTOR_RL_PWM);
    setMotor(MOTOR_RR_IN1, -(speed+output), MOTOR_RR_PWM);
    print(speed,output);
}

//mal
void Motors::moveLeft(int speed, int output) {
    setMotor(MOTOR_FL_IN1, (speed-output), MOTOR_FL_PWM);
    setMotor(MOTOR_FR_IN1, 0, MOTOR_FR_PWM);
    setMotor(MOTOR_RL_IN1, (speed+output), MOTOR_RL_PWM);
    setMotor(MOTOR_RR_IN1, 0, MOTOR_RR_PWM);
    print(speed,output);
}

//Ya está bien
void Motors::moveRight(int speed, int output) {
    setMotor(MOTOR_FL_IN1, -(speed+output), MOTOR_FL_PWM);
    setMotor(MOTOR_FR_IN1, 0, MOTOR_FR_PWM);
    setMotor(MOTOR_RL_IN1, -(speed-output), MOTOR_RL_PWM);
    setMotor(MOTOR_RR_IN1, 0, MOTOR_RR_PWM);
    print(speed,output);
}

void Motors::stop() {
    setMotor(MOTOR_FL_IN1, 0, MOTOR_FL_PWM);
    setMotor(MOTOR_FR_IN1, 0, MOTOR_FR_PWM);
    setMotor(MOTOR_RL_IN1, 0, MOTOR_RL_PWM);
    setMotor(MOTOR_RR_IN1, 0, MOTOR_RR_PWM);
}

void Motors::evilstop(int speed) {
    setMotor(MOTOR_FL_IN1, speed, MOTOR_FL_PWM);
    setMotor(MOTOR_FR_IN1, speed, MOTOR_FR_PWM);
    setMotor(MOTOR_RL_IN1, speed, MOTOR_RL_PWM);
    setMotor(MOTOR_RR_IN1, speed, MOTOR_RR_PWM);
}

void Motors::print(int speed, int output){
    /*Serial.print("MIN: ");
    Serial.print(speed+output);
    Serial.print("MAX: ");
    Serial.println(speed-output);*/
}
