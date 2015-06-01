//
//  Flowers.h
//  http_example
//
//  Created by Phoenix Perry on 24/05/15.
//
//

#ifndef __http_example__Flowers__
#define __http_example__Flowers__

#include <stdio.h>
#include "ofMain.h"
#include "SerialReader.h" 
#include "OscData.h" 
#include "ofxTonic.h" 
using namespace Tonic;


class Flowers{
private:
    ofxTonicSynth synth;
    int scaleDegree;
    void trigger();
    void setScaleDegreeBasedOnMouseX();
public:
    Flowers(SerialReader *serial_, OscData *oscData_, ofBaseApp *app);
    void update();
    
    SerialReader *serial;
    OscData *oscData;
    void audioRequested(float *output, int buffersize, int nChannels);
    
    float lightLevel;
    vector<float>ardVals;
    
    ofSoundPlayer note1;
    ofSoundPlayer note2;
    ofSoundPlayer note3;
    ofSoundPlayer note4;
    
    ofSoundPlayer player; 
    
    void audioOut(float * input, int bufferSize, int nChannels);
   	
    ofSoundStream soundStream;
    void audioRequested();

};
 
#endif /* defined(__http_example__Flowers__) */
