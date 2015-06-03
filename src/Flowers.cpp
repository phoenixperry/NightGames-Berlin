//
//  Flowers.cpp
//  http_example
//
//  Created by Phoenix Perry on 24/05/15.
//
//

#include "Flowers.h"
#define NUMBER_OF_KEYS 10

Flowers::Flowers(SerialReader *serial_){
    serial = serial_;
}


void Flowers::update(){
    int num1 = serial->pad12;
    int num2 = serial->pad13;
    int num3 = serial->pad14;
    int average = num1 + num2 + num3/3;
   
}
