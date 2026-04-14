#include <BohleBots_BNO055.h>
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
    IMUData getIMUData();
    float getHeading();
    float getRLHeadingAuto();

private:
    IMUData imuData;
    BNO bno;
};

extern Sensors IMU;

