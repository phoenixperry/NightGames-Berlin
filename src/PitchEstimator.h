//
//  PitchEstimator.h
//  http_example
//
//  Created by Phoenix Perry on 15/03/15.
//
//

#ifndef __http_example__PitchEstimator__
#define __http_example__PitchEstimator__

#include <stdio.h>
#include "ofxMaxim.h"
#include "ofMain.h"
class pitchEstimator : public ofBaseApp{
    
public:
    
    ~pitchEstimator();
    void setup();
    void update();
    void draw();
    
    void audioOut 	(float * input, int bufferSize, int nChannels); /* output method */
    void audioIn 	(float * input, int bufferSize, int nChannels); /* input method */
    
    int		initialBufferSize; /* buffer size */
    int		sampleRate;
    
    ofSoundStream soundStream;
    
    // begin maximilian stuff
    
    double wave,wave1, wave2, sample,outputs[2];
    //ofxMaxiOsc sines[13];
    ofxMaxiOsc sine, sine1, sine2;
    
    int bin_number, bin_number1, bin_number2;
    float largests[3];
    
    ofxMaxiFilter lowpass, highpass;
    
    ofxMaxiFFT fft;
    ofxMaxiFFTOctaveAnalyzer octaveAnalyzer;
    ofxMaxiMix mix;
    
    float *inputL, *inputR;
    
    float estimatedPitch[3];
    
};

#endif /* defined(__http_example__PitchEstimator__) */
