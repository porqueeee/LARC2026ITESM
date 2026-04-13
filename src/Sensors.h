#include <Adafruit_BNO055.h>
#include <Arduino.h>
#include <Wire.h>

struct IMUData {
    float heading;
    float pitch;
    float roll;
};

class Sensors {
public:
    void init();
    void updateAll();

    // IMU
    IMUData getIMUData();
    float getHeading();
    event_t;
    
private:
    IMUData imuData;
    
    Adafruit_BNO055 bno;
};

extern Sensors IMU;

