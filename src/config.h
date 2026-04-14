#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>



// ============================================
// PINES DE MOTORES
// ============================================
///fornt right
#define MOTOR_FL_IN1 22 
#define MOTOR_FL_PWM 2
                            
// Motor Front Left
#define MOTOR_FR_IN1 24
#define MOTOR_FR_PWM 3

// Motor Rear Left
#define MOTOR_RL_IN1 26
#define MOTOR_RL_PWM 6

// Motor Rear Right
#define MOTOR_RR_IN1 28
#define MOTOR_RR_PWM 7


// ============================================
// PINES DE SENSOR DE LÍNEA (TCRT5000)
// ============================================
#define frontLeft A1
#define frontRight A2
#define rearLeft A3
#define rearRight A4
// Sensores de línea
#define LINE_THRESHOLD 150
#define LINE_DETECTED true
#define LINE_NOT_DETECTED false

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
// CONSTANTES DE CALIBRACIÓN
// ============================================


// Velocidades
#define BASE_SPEED 100
#define SLOW_SPEED 60
#define TURN_SPEED 100
#define ALIGN_SPEED 60

// Distancias (mm)
#define DISTANCE_POOL_MIN 100
#define DISTANCE_POOL_MAX 800
#define DISTANCE_OBSTACLE_STOP 150
#define DISTANCE_TREE_APPROACH 200

// Tiempos
#define EXIT_BOX_TIME 2000
#define ALIGN_TIMEOUT 5000
#define COLLECTION_TIMEOUT 30000

// ============================================
// POSICIONES DE SERVOS (0-180 grados)
// ============================================
// Brazo
#define ARM_RETRACTED 10
#define ARM_LOW_LEVEL 60
#define ARM_MID_LEVEL 90
#define ARM_HIGH_LEVEL 120

// ============================================
// THRESHOLDS DE COLOR
// ============================================
// Ripe beans (red, orange, yellow)
#define RIPE_R_MIN 150
#define RIPE_R_MAX 255
#define RIPE_G_MIN 50
#define RIPE_G_MAX 200
#define RIPE_B_MIN 0
#define RIPE_B_MAX 100

// Green beans
#define GREEN_R_MIN 0
#define GREEN_R_MAX 100
#define GREEN_G_MIN 100
#define GREEN_G_MAX 255
#define GREEN_B_MIN 0
#define GREEN_B_MAX 100

// Overripe beans (blue, black)
#define OVERRIPE_B_MIN 100
#define OVERRIPE_B_MAX 255

// ============================================
// ESTADOS DEL ROBOT
// ============================================
*/
enum RobotState {
    INIT,
    EXIT_BOX,
    ALLING_RIGHT,
    NAVIGATE_TO_TREEZONE,
    COLLECT_LINE,
    RETURN_TO_BASE,
    DEPOSIT_BEANS,
    COMPLETE,
    ERROR
};
/*
// ============================================
// TIPOS DE GRANOS
// ============================================
enum BeanType {
    NONE,
    RIPE,
    GREEN,
    OVERRIPE
};

// ============================================
// DIRECCIONES DE MOVIMIENTO
// ============================================
enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
*/

#endif