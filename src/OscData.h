//
//  OscData.h
//  http_example
//
//  Created by Phoenix Perry on 23/05/15.
//
//

#ifndef __http_example__OscData__
#define __http_example__OscData__

#include <stdio.h>
#include "ofxOsc.h"

class OscData{
public:
    OscData();
    void setup();
    void update(); 
    ofxOscSender sender;
    void sendData(vector<int>&data,string interaction);
    
    ofxOscReceiver receiver;

};
#endif /* defined(__http_example__OscData__) */
