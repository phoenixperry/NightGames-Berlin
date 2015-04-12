#pragma once

#include "ofMain.h"
#include "Spark_core_manager.h"
#include "Clouds.h"
#include "SerialReader.h"
#include <vector>
#include "Hut.h"
using namespace std;
//AudioStreamBasicDescription ASBD = {
//    .mSampleRate       = 44100,
//    .mFormatID         = kAudioFormatLinearPCM,
//    .mFormatFlags      = kAudioFormatFlagsAudioUnitCanonical,
//    
//    .mChannelsPerFrame = 4, // <- change this to 24 in your case
//    .mFramesPerPacket  = 1,
//    
//    .mBitsPerChannel   = sizeof(AudioUnitSampleType) * 8,
//    .mBytesPerPacket   = sizeof(AudioUnitSampleType),
//    .mBytesPerFrame    = sizeof(AudioUnitSampleType)
//};

class ofApp : public ofBaseApp{
  	public:
		void setup();
		void update();
		void draw();
		void keyReleased(int key);
	   
    Clouds *clouds;
    pitchEstimator *p;
    Spark_core_manager *spark_clouds;
    Spark_core_manager *spark_rock;
    //SerialReader * serial;
    
    //sounds
    ofSoundPlayer cloud_sound_1;
    Hut *hut;
    vector<ofxAudioUnit> *hutFilters;
    ofxAudioUnitOutput output;
  //  ofxAudioUnitMixer  mixer;
};
