#include "Selector.h"

Selector selector;

void Selector::init(){

    //pines de los servos
    servo1.attach(13); //Servo clasificador
    servo2.attach(12); //servo para agarrar pelotas

    servo1.write(90);
    servo2.write(90);
}

void Selector::grab(String color){
    //granos maduros
    if(color == "Rojo" || color=="Naranja" || color=="Amarillo"){
        servo1.write(110);
        servo2.write(0);
        delay(2000);
        servo2.write(90);   

    }
    //granos sobremaduros
    if(color == "Negro"|| color=="Azul"){
        servo1.write(70);
        servo2.write(0);
        delay(2000);
        servo2.write(90);

    }
}