//
//  SerialReader.h
//  http_example
//
//  Created by Phoenix Perry on 24/03/15.
//
//

#ifndef __http_example__SerialReader__
#define __http_example__SerialReader__

#include <stdio.h>
#include "ofMain.h"
#include <iostream>
#pragma once
#define NUM_BYTES 2
#define NUM_PADS 12
using namespace std;
class SerialReader{
public:
    SerialReader();
    void setup();
    void update();

   ofSerial * serial;
    int sensorPadValue;
    string serialData;
    
//    int pads[NUM_PADS] = {0,1,2,3,4,5,6,7,8,9,10} ;
    int pad1, pad2, pad3, pad4, pad5, pad6, pad7, pad8, pad9, pad10, pad11, pad0=0;
};
#endif /* defined(__http_example__SerialReader__) */
