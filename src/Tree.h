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
//#include "ofxAudioUnit.h"
#include "OscData.h"

class Tree{
public:

    vector<float> pads;
    bool calibrating = false;
    Tree(SerialReader *serial_reader_);
    ~Tree();
    SerialReader *serial_reader;
    void keyReleased(ofKeyEventArgs &key);
    void update();
    void draw();
    OscData* oscData;
    int numSensors = 3;
    void setHealth();

    float health;
    vector<float>* nums;
    void sendHealth();
    void sendToWekinator(vector<float>& pads);
};



#endif /* defined(__http_example__Tree__) */
