//
//  Clouds.h
//  http_example
//
//  Created by Phoenix Perry on 08/03/15.
//
//

#ifndef __http_example__Clouds__
#define __http_example__Clouds__
#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Spark_core_manager.h" 
#include "PitchEstimator.h"
//#include "aubioAnalyzer.h"
class Clouds {

public:
    Clouds(Spark_core_manager *spark_, pitchEstimator *p_);
    pitchEstimator *p;
    Spark_core_manager *spark;
    
    void newResponse(ofxHttpResponse & response);

    void setup();
    void update();
    void draw();
    void triggerLed(string color);
   // void setupSpark(Spark_core_manager *spark_);

};

#endif /* defined(__http_example__Clouds__) */
