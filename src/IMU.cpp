#include "IMU.h"

IMU imu; 

void IMU::init() {
    // Inicializar I2C
    Serial.println("Imu init");
    Wire.begin();
    Wire.setClock(400000); // 400kHz


    bno.startBNO(200, false);
    while(!bno.isCalibrated()){	//Solo calibra giroscopio, le moví a la librería
        bno.serialPrintCalibStat();
        delay(1000);
    }

    Serial.println("IMU Calibrada");
    bno.saveOffsets(100);
    delay(1000);
}

int IMU::getHeading() {
    int heading=bno.getRLHeadingAuto(100);
    //Serial.println(heading);
    return heading; //el 100 es la dirección física de los offsets generados durante la calibración
}