#include "Arduino.h"
#include "SensorColor.h"
#include "Sensors.h"

Sensors IMU;
float Data;

void setup() {
    Serial.begin(9600);
    IMU.init();
    Serial.print("Jala :)");
}

void loop() {
    IMU.updateAll();
    Data=IMU.getHeading();
    Serial.print(Data);
    delay(500);
}