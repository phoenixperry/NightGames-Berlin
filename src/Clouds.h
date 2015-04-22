
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
#include "ofxAudioUnit.h"

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
    void update_star_data(float val);
   // ~Clouds();
   // void setupSpark(Spark_core_manager *spark_);
    
    //effects
    ofxAudioUnit reverb;
    ofxAudioUnit delay;
    ofxAudioUnit filter;
    
    
    ofxAudioUnitMixer mix;
    ofxAudioUnitTap tap1, tap2, tap3, tap4, tap5;
    ofxAudioUnitFilePlayer clouds1;
    ofxAudioUnitFilePlayer clouds2;
    ofxAudioUnitFilePlayer clouds3;
    ofxAudioUnitFilePlayer clouds4;
    ofxAudioUnitFilePlayer clouds5;
    
    ofxAudioUnitOutput output;
    ofxAudioUnitMixer mixer;
    
    float currentTime, startTime;
    float duration = 10;
    bool fade = false;
    
    const static int NUM_SENSORS = 5;				//Number of the samples
    float vol[NUM_SENSORS];					//Volumes of the samples
    float stars_average=0;
    vector<ofxAudioUnit> filters;
    vector<ofxAudioUnitTap>taps;
    vector<ofxAudioUnitFilePlayer> clips;
    
   // other apprach 

};

#endif /* defined(__http_example__Clouds__) */
