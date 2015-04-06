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
    float duration = 2000;
    bool bullshitPress = false;
    bool welcomeMessage = true; 
    bool calibrate_state = true;
    bool run_state=false;
    SerialReader *serial_reader;
    
    
    int padsLow[NUM_SENSORS];
    int padsHigh[NUM_SENSORS];
    int pads[NUM_SENSORS];
    bool calibrate_pad[NUM_SENSORS];
    
    ofxAudioUnitMixer mix;
    void startCalibrationProcess(int &e);
    vector<ofxAudioUnit> filters;
    vector<ofxAudioUnitTap>taps;
    vector<ofxAudioUnitFilePlayer> clips;

    float currentTime, endTime;
  
    Hut();
    void calibrate();
    void keyReleased(ofKeyEventArgs &key);
    void update();
    void draw();
    char subState = 'A';
    int value =0;
    void init();
    int current = -1;
    char keyPress = ' ';
};
#endif /* defined(__http_example__Hut__) */
