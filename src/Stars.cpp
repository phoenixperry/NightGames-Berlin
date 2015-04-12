//
//  Stars.cpp
//  http_example
//
//  Created by Phoenix Perry on 4/11/15.
//
//

#include "Stars.h"
Stars::Stars(){
    filters.resize(NUM_LIGHT_SENSORS);
    taps.resize(NUM_LIGHT_SENSORS);
    clips.resize(NUM_LIGHT_SENSORS);
    mixer.setInputBusCount(NUM_LIGHT_SENSORS/2);
    
    for (int i=0; i<NUM_LIGHT_SENSORS/2; i++) {
        ofxAudioUnitTap tap;
        ofxAudioUnit varispeed;
        varispeed.setup(kAudioUnitType_FormatConverter, kAudioUnitSubType_Varispeed);
        filters[i] = varispeed;
        taps[i] = tap;
    }
    
    
    for(int i = 0; i < NUM_LIGHT_SENSORS/2; i++)
    {
        
        ofxAudioUnitFilePlayer filePlayer;
        clips[i].setFile(ofFilePath::getAbsolutePath("sound/stars"+ofToString(i+1)+".aif"));
        clips[i].loop();
        clips[i].connectTo(filters.at(i)).connectTo(taps.at(i)).connectTo(mixer,i);
  
    }
        ofSetVerticalSync(true);
    mixer.connectTo(output);
    mixer.setInputVolume(1.0f, 2);
    mixer.setOutputVolume(1.0f);
    output.start(); 
}


//vector<ofxAudioUnitTap>& Stars::getTaps(){
//    
//    return taps;
//}
Stars::~Stars(){

}
