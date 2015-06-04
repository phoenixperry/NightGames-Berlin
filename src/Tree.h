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

    vector<float>pads;

    Tree(SerialReader *serial_reader_);
    ~Tree();
    SerialReader *serial_reader;

    void update();
    void draw();
    OscData* oscData;
    OscData* filteredOsc;
    
    int numSensors = 2;
    
    void setHealth();

    float health =0.0f;
    vector<float>* nums;
    void sendHealth();
    void sendToWekinator(vector<float>& pads, string inputToWekinator);
    vector<float> * padsFiltered;
};



#endif /* defined(__http_example__Tree__) */
