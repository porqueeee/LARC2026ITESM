#include "Selector.h"

Selector selector;

void Selector::init(){

    //pines de los servos
    servo1.attach(13);
    servo2.attach(12);

    servo1.write(90);
    servo2.write(90);
}