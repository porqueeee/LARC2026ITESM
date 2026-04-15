#include "SensorColor.h"
#include "ColorConverterLib.h" 

// Define el objeto global del sensor

SensorColor sensorC; 
  
SensorColor::SensorColor()
// Inicialización de variables
: tcs(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_4X), r_raw(0), g_raw(0), b_raw(0), c_raw(0), 
  r_8bit(0), g_8bit(0), b_8bit(0), hue(0.0), saturation(0.0), value(0.0) {}


bool SensorColor::begin() {
    
    if (tcs.begin()) {
        Serial.println("TCS34725 encontrado!");
        // Opcional: Encender el LED
        // tcs.setInterrupt(false); 
        return true;
    } else {
        Serial.println("No se detecta el TCS34725.");
        return false;
    }
}

void SensorColor::setupI() {
  Serial.begin(9600);
  Serial.println("");  
  

  if (!tcs.begin()) {
    Serial.println(" conexiones .");
    while (1); 
  }
  
  delay(2000);
  Serial.println("calibrar...");
  delay(5000);
  calibrarBlanco();
}
// Implementación de la función de calibración
void SensorColor::calibrarBlanco() {
    // Lectura para establecer el punto blanco de referencia
    tcs.getRawData(&r_raw, &g_raw, &b_raw, &c_raw);
    // Se usa el valor C_raw como el valor máximo de referencia (c_blanco)
    c_blanco = c_raw; 
    Serial.print("Calibración de Blanco (C_blanco) establecida en: ");
    Serial.println(c_blanco);
}


void SensorColor::leerColor() {
    // 1. Lectura de valores RAW (16 bits) del sensor
    tcs.getRawData(&r_raw, &g_raw, &b_raw, &c_raw);
    
    // 2. Conversión normalizada a 8 bits (0-255)
    rawToNormalizado();
    
    // 3. Conversión de RGB (8 bits) a HSV
    rgbToHsv();
}

void SensorColor::rawToNormalizado() {
    
    // Evita la división por cero y asegura que la calibración se haya realizado
    if (c_blanco == 0 || c_raw == 0) { 
        r_8bit = g_8bit = b_8bit = 0;
        return;
    }

    // FÓRMULA DE NORMALIZACIÓN:
    float ratio_r = (float)r_raw / c_blanco;
    float ratio_g = (float)g_raw / c_blanco;
    float ratio_b = (float)b_raw / c_blanco;

    // Escalar al rango 0-255 y asegurar que no excedan 255
    r_8bit = constrain((int)(ratio_r * 255.0), 0, 255);
    g_8bit = constrain((int)(ratio_g * 255.0), 0, 255);
    b_8bit = constrain((int)(ratio_b * 255.0), 0, 255);
}

void SensorColor::rgbToHsv() {
    ColorConverter::RgbToHsv(r_8bit, g_8bit, b_8bit, hue, saturation, value);
}

void SensorColor::imprimir() {
    Serial.print("-----------------------------\n");
    // Imprimimos H multiplicado por 360 para mostrar el tono en grados (0° - 360°)
    Serial.print("HSV: H="); 
    Serial.print(hue * 360.0, 1); 
    Serial.print(" S="); 
    Serial.print(saturation, 2); 
    Serial.print(" V="); 
    Serial.println(value, 2);
}

String SensorColor::definir() {
    double hue_grados = hue * 360.0;
    String colorActual = "Desconocido";

    //Evaluar Negro, Diferenciar del Verde
    
    if (value < 0.08 && hue_grados> 138 ) { 
        colorActual = "Negro";
    }
    else if (hue_grados >= 345.0 || hue_grados <= 15.0) {
        colorActual = "Rojo";
    } 
    else if (hue_grados > 15.0 && hue_grados <= 45.0) {
        colorActual = "Naranja";
    }  
    else if (hue_grados > 45.0 && hue_grados <= 90.0) {
        colorActual = "Amarillo";
    }
    else if (hue_grados > 90.0 && hue_grados <= 160.0)  {
        if (saturation >= 0.45) {
            colorActual = "Verde";
        } else {
            colorActual = "Negro"; 
        }
    } 
    else if (hue_grados > 160.0 && hue_grados <= 260.0) {
        colorActual = "Azul";
    } 
    Serial.println(colorActual);
/*
    if (colorActual != ultimoColor) {
        if (colorActual != "Desconocido") { 
            Serial.print("Nuevo color detectado: ");
            Serial.println(colorActual);
        }
        ultimoColor = colorActual; // Guardamos el color actual en la memoria
    }
    */
    return colorActual;
}
