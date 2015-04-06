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

#define NUM_SENSORS 6
class Hut{
public:
//    ofEvent <int> calibrated;
//    ofEvent <int> startCalibration;
    //timer for calibration
    float duration = 1000;
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


    char currentPress;
    float currentTime, endTime;
  
    int calibrateNum =0;
    Hut();
    void calibrate();
    void keyReleased(ofKeyEventArgs &key);
    void update();
    void draw();
    char subState = 'A';
    
 
    char keyPress=' ';
    int world_record=0;
    int current_data=0;
    
    void padCalibrated(int &e); 
   
};
#endif /* defined(__http_example__Hut__) */
