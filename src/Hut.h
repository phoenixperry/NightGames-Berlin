//
//  Hut.h
//  http_example
//
//  Created by Phoenix Perry on 4/4/15.
//
//

#ifndef __http_example__Hut__
#define __http_example__Hut__
#pragma once
#include <stdio.h>
#include "SerialReader.h"
#include "ofxAudioUnit.h"
#include "ofMain.h"
#include <stdlib.h>

#define NUM_SENSORS 7
class Hut{
public:
//    ofEvent <int> calibrated;
//    ofEvent <int> startCalibration;
    //timer for calibration
    float duration = 8000;
    SerialReader *serial_reader;
    
    bool calibrateMode = true; 
    vector<int> padsLow;
    vector<int>padsHigh;
    vector<int>* pads;
    bool calibrating = false;
    ofxAudioUnitMixer mixer;
    vector<ofxAudioUnit> filters;
    vector<ofxAudioUnitTap>taps;
    vector<ofxAudioUnitFilePlayer> clips;
    
    
    //ofxAudioUnit varispeed;
    //ofxAudioUnit lowpass;
 //   ofxAudioUnitFilePlayer filePlayer;
    ofxAudioUnitOutput output;
    //ofxAudioUnitTap tap;
    
    
    float currentTime, endTime;
  
    Hut();
    void keyReleased(ofKeyEventArgs &key);
    void update();
    void draw();
 
    int value =0;
 
    int current = -1;
    char keyPress =' ';
};
#endif /* defined(__http_example__Hut__) */
