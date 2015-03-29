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
#pragma once
#define NUM_BYTES 2

class SerialReader{
public:
    SerialReader();
    void setup();
    void update();

   ofSerial * serial;
    int sensorPadValue;
};
#endif /* defined(__http_example__SerialReader__) */
