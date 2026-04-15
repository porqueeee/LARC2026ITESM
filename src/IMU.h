#ifndef IMU_H 
#define IMU_H 

#include <Arduino.h>
#include <Wire.h>
#include <BohleBots_BNO055.h>
#include "config.h"

class IMU {
public:
    void init();
    int getHeading();
private:
    BNO bno;
};

extern IMU imu;

#endif