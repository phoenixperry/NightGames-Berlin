//
//  Stars.h
//  http_example
//
//  Created by Phoenix Perry on 4/11/15.
//
//

#ifndef __http_example__Stars__
#define __http_example__Stars__
#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "Spark_core_manager.h"

#define NUM_LIGHT_SENSORS 2
class Stars{
public:
    vector<ofxAudioUnit> filters;
    vector<ofxAudioUnitTap> taps;
    vector<ofxAudioUnitFilePlayer> clips;

    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output; 
    Spark_core_manager *spark;
    Stars(Spark_core_manager *spark_);
    //Stars();
    //void newResponse(ofxHttpResponse & response);
    vector<int> sensors;
    void update();
    void draw();
    float * stars_average;
    float holder =0; // just holds current average
//    vector<ofxAudioUnitTap>& getTaps();
    
    ~Stars();
//    void mouseDragged(ofKeyEventArgs )
};

#endif /* defined(__http_example__Stars__) */
