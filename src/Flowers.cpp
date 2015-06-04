//
//  Flowers.cpp
//  http_example
//
//  Created by Phoenix Perry on 24/05/15.
//
//

#include "Flowers.h"
#define NUMBER_OF_KEYS 10

Flowers::Flowers(SerialReader *serial_):padsAverage(average){

    serial = serial_;
    average = 0;
    padsAverage = average;
    oscData = new OscData(9000, 8001);
    pads = new vector<float>;

}
void Flowers::update(){
    average= serial->pad12;
    sendToWekinator(average, "/flowers/inputs");
    pads = oscData->getData("/flowers/outputs");
    
    vector<float>::const_iterator it;
    int num = 0;
    padsAverage =0;
    for (it = pads->begin(); it != pads->end(); it++)
    {
        padsAverage = padsAverage+*it;
        num++;
       
    }
    padsAverage = padsAverage/num;
   // cout << padsAverage << " flower data from wekinator" << endl;
}

float& Flowers::getFood(){
    //return is an reference
    return padsAverage;
}

void Flowers::sendToWekinator(float &padsAverage_, string inputToWekinator) {
    oscData->sendData(padsAverage_, inputToWekinator);
    //cout << average << " flower data to wekinator" << endl;
    
}

