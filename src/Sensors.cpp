#include "Sensors.h"
Sensors Sensors;

void Sensors::init() {

    // Inicializar I2C
    Wire.begin();
    
    
    // Inicializar IMU
    Serial.print("Inicializando IMU BNO055... ");
    if (!bno.begin()) {
        Serial.println("ERROR! No se pudo inicializar BNO055");
    } else {
        Serial.println("OK!");
        bno.setExtCrystalUse(true);
    }
    
    delay(100);
}

void Sensors::updateAll() {

    // Actualizar IMU
    Sensors::event_t event;
    bno.getEvent(&event);
    imuData.heading = event.orientation.x;
    imuData.pitch = event.orientation.y;
    imuData.roll = event.orientation.z;
}

IMUData Sensors::getIMUData() {
    return imuData;
}

float Sensors::getHeading() {
    return imuData.heading;
}