//
//  Rock.h
//  http_example
//
//  Created by Phoenix Perry on 29/03/15.
//
//

#ifndef __http_example__Rock__
#define __http_example__Rock__
#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Spark_core_manager.h"
#include "ofxAudioUnit.h"
class Rock{
public:
//    
    Rock(Spark_core_manager *spark_);
    Spark_core_manager *spark;
//    Rock();
    ofxAudioUnit filter;
    ofxAudioUnitTap tap;
    ofxAudioUnitOutput output;
    ofxAudioUnitMixer mix;
    ofxAudioUnitFilePlayer clip;
    void update();
//    int data=0;
    string data;
};

#endif /* defined(__http_example__Rock__) */
