#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>

class SensorColor {
public:
    SensorColor(); 
    bool begin();  
    void leerColor();  
    void imprimir();
    void definir();
    void setupI();   
private:
    Adafruit_TCS34725 tcs;
    
    uint16_t r_raw, g_raw, b_raw, c_raw; 
    
    // Valor de referencia C para la calibración
    uint16_t c_blanco = 0; 
    
    uint8_t r_8bit, g_8bit, b_8bit;
    
    double hue, saturation, value;
    
    void rawToNormalizado(); 
    void rgbToHsv();
    void calibrarBlanco();
};