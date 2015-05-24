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
#include "OscData.h"
#define NUM_SENSORS_TREE 2
class Tree{
public:
    vector<int> padsLow;
    vector<int>padsHigh;
    vector<int> pads;
    bool calibrating = false;
    Tree(SerialReader *serial_reader_, OscData *oscData_);
    ~Tree();
    SerialReader *serial_reader;
    void keyReleased(ofKeyEventArgs &key);
    void update();
    void draw();
    OscData *oscData; 
 
};



#endif /* defined(__http_example__Tree__) */
