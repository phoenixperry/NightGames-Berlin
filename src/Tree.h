//
//  Tree.h
//  http_example
//
//  Created by Phoenix Perry on 22/04/15.
//
//

#ifndef __http_example__Tree__
#define __http_example__Tree__

#include <stdio.h>
#pragma once
#include <stdio.h>
#include "SerialReader.h"
#include "ofMain.h"
#include <stdlib.h>
#include "ofxAudioUnit.h"
#define NUM_SENSORS_TREE 2
class Tree{
public:
    bool treeSetup = false;
    //    ofEvent <int> calibrated;
    //    ofEvent <int> startCalibration;
    //timer for calibration
    float duration = 10000;
    
    bool calibrateMode = true;
    vector<int> padsLow;
    vector<int>padsHigh;
    vector<int>* pads;
    bool calibrating = false;
    ofxAudioUnitMixer mixer;
    vector<ofxAudioUnit> filters;
    vector<ofxAudioUnitTap>taps;
    vector<ofxAudioUnitFilePlayer> clips;
    ofxAudioUnitOutput output;
    float currentTime, endTime;
    Tree();
    ~Tree();

    void keyReleased(ofKeyEventArgs &key);
    void update(int pad7, int pad8);
    void draw();
    
    int value =0;
    
    int current = -1;
    char keyPress =' ';
    
    
    
    // int &getNumSensors();
    //   vector<ofxAudioUnitTap>& getTaps();
};



#endif /* defined(__http_example__Tree__) */
