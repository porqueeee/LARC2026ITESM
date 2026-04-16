#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define brakespeed 100
#define braketime 20
#define defaultspeed 200

// ============================================
// PINES DE MOTORES NO MOVER NUNCA >:(
// ============================================
// Motor Front Left
#define MOTOR_FR_IN1 7 //controla velocidad y enable
#define MOTOR_FR_PWM 6 //controla dirección

///front right

#define MOTOR_FL_IN1 9
#define MOTOR_FL_PWM 8
                            
// Motor Rear Right
#define MOTOR_RR_IN1 46
#define MOTOR_RR_PWM 44



// Motor Rear Left
#define MOTOR_RL_IN1 4
#define MOTOR_RL_PWM 5


// ============================================
// PSENSOR DE LÍNEA (TCRT5000)
// ============================================
#define frontLeft A1
#define frontRight A2
#define rearRight A3
#define rearLeft A4

// Sensores de línea
#define LINE_THRESHOLD 150

// ============================================
// SENSOR ULTRASÓNICO
// ============================================
#define FL_TRIG 29
#define FL_ECHO 31

#define FR_TRIG 35
#define FR_ECHO 33

#define RR_TRIG 27
#define RR_ECHO 25

#define RL_TRIG 37
#define RL_ECHO 39


#define DIST_THRESHOLD 40


/* ============================================
// PINES DE SERVOS (via PCA9685)
// ============================================
#define SERVO_ARM 0
#define UPPER_GRAB 13
#define LOWER_GRAB 2
#define SERVO_CAROUSEL 3
#define SERVO_GRIPPER 4

// ============================================
// BOTÓN DE INICIO
// ============================================
#define START_BUTTON 20

// ============================================
// POSICIONES DE SERVOS (0-180 grados)
// ============================================
// Brazo
#define ARM_RETRACTED 10
#define ARM_LOW_LEVEL 60
#define ARM_MID_LEVEL 90
#define ARM_HIGH_LEVEL 120

// ============================================
// ESTADOS DEL ROBOT
// ============================================
*/
enum RobotState {
    INIT,
    EXIT_BOX,
    ALIGN_RIGHT,
    CLEAR_OBSTACLES,
    REALIGN_RIGHT,
    COLLECT_LINE,
    COMPLETE,
    ERROR
};


#endif