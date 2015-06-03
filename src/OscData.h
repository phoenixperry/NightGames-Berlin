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
    OscData(int port_number);

    vector<float>* getData(string inputString);
    ofxOscSender sender;

    void sendData(vector<float>&data,string outputString);
    void sendData(float &num, string outputString);
    ofxOscReceiver receiver;
    vector<float>* nums;
};
#endif /* defined(__http_example__OscData__) */
