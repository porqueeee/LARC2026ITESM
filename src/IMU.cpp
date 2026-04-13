#include "IMU.h"

IMU imu;

void IMU::init() {
    // Inicializar I2C
    Wire.begin();
    Wire.setClock(400000); // 400kHz
    
    bno.startBNO(200, false);
    Serial.println("IMU inicializada");
    bno.saveOffsets(100);
    delay(1000);
}

int IMU::getHeading() {
    return bno.getRLHeadingAuto(100);
}