#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motors.h"
#include "IMU.h"
#include "PID.h"  
#include "config.h"
#include "Line.h"

class Movement {
public:
    Movement() : targetHeading(0), headingPID(1.0, 0.0, 0.0, -100, 100) {}  // Inicializar PID con valores por defecto
    void init();
    
    // Movimientos con corrección por PID, dependen del tiempo
    //El PID se resetea en cada movimiento pero el set heading siempre es 0
    void moveForwardStraight(int speed, unsigned long time);
    void moveBackwardStraight(int speed, unsigned long time);
    void moveLeftStraight(int speed ,unsigned long time);
    void moveRightStraight(int speed ,unsigned long time);

    //Movimientos normales (para pruebas)
    void moveForward(int speed, unsigned long time);
    void moveBackward(int speed, unsigned long time);
    void moveLeft(int speed ,unsigned long time);
    void moveRight(int speed ,unsigned long time);
    
    //Movimientos con corrección por PID, dependientes del sensor de línea
    void moveForwardUntilBackLine(int speed);
    void moveBackwardUntilFrontLine(int speed);    
    void moveRightUntilRightLine(int speed);
    void moveLeftUntilLeftLine(int speed);

    void moveLeftUntilClear(int speed);

    /* Movimiento siguiendo la línea
    void moveForwardWithLine(int speed);
    void moveBackwardWithLine(int speed);
    void moveLeftWithLine(int speed);
    void moveRightWithLine(int speed);

    void moveRightUntilRightLineFollowingLine(int speed);
    void moveForwardUntilFrontLineFollowingLine(int speed);
    void moveLeftUntilLeftLineFollowingLine(int speed);
    void moveBackwardUntilBackLineFollowingLine(int speed);
    */

    // Rodear alberca
    void moveLeftUntilObstacleClear(int speed);
    void moveRightUntilObstacleClear(int speed);
    void moveForwardUntilObstacleClear(int speed);
    void moveBackwardUntilObstacleClear(int speed);

    // Moverte al siguiente grano de café
    // siguiendo la línea
    void moveToNextBean(int speed, int level=1);

    //Moverte a las cajas de depósito
    void moveToDepositBox(int speed, int boxNumber);

    // Parada
    void stop();
    
    // Configuración PID
    void setHeadingPIDGains(float kp, float ki, float kd);  // NUEVO
    
private:
    float targetHeading;
    PID headingPID;  // NUEVO
    
    void updateTargetHeading();
    int calculateHeadingCorrection();
    float calculateHeadingCorrectionPID();  // NUEVO
};

extern Movement movement;

#endif