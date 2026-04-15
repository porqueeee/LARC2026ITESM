#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motors.h"
#include "IMU.h"
#include "PID.h"  
#include "config.h"
#include "Line.h"

//Todas las funciones de movimiento terminan con un stop() de esta misma clase que llama al motors.stop()

class Movement {
public:
    Movement() : targetHeading(0), headingPID(1.0, 0.0, 0.0, -100, 100) {}  // Inicializar PID con valores por defecto
    void init();
    
    // Movimientos con corrección por PID, dependen del tiempo
    //El PID se resetea y también el target heading
    void moveForwardStraight(int speed, unsigned long time);
    void moveBackwardStraight(int speed, unsigned long time);
    void moveLeftStraight(int speed ,unsigned long time);
    void moveRightStraight(int speed ,unsigned long time);

    //Movimientos normales (para pruebas), llaman a las funciones de Motors por una cantidad 
    //fija de tiempo , no tiene ninguna clase de corrección
    void moveForward(int speed, unsigned long time);
    void moveBackward(int speed, unsigned long time);
    void moveLeft(int speed ,unsigned long time);
    void moveRight(int speed ,unsigned long time);
    
    //Movimientos con corrección por PID, dependiente del sensor de línea
    void moveForwardUntilBackLine(int speed);

    //Movimiento a la izquierda con corrección por PID, se detiene cuando esquiva un objeto
    void moveLeftUntilClear(int speed);

    //Movimiento a la derecha con corrección por PID, 
    void moveRightUntilRightLine(int speed);


    // Moverte al siguiente grano de café
    // siguiendo la línea
    /*
    void moveToNextBean(int speed, int level=1);

    //Moverte a las cajas de depósito
    void moveToDepositBox(int speed, int boxNumber);
    */

    // Parada
    void stop();
    
    // Configuración PID
    void setHeadingPIDGains(float kp, float ki, float kd);  // NUEVO
    
private:
    float targetHeading;
    PID headingPID;  // NUEVO
    

    //Define el ángulo actual como el nuevo "heading"
    void updateTargetHeading();
    //int calculateHeadingCorrection();

    //Llama al PID y calcula un offset para la velocidad
    float calculateHeadingCorrectionPID();  // NUEVO
};

extern Movement movement;

#endif