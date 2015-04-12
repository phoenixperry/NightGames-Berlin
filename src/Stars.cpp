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

    for(int i = 0; i < NUM_LIGHT_SENSORS/2; i++)
    {
        filters[i].setup(kAudioUnitType_FormatConverter, kAudioUnitSubType_Varispeed);
        
        ofxAudioUnitFilePlayer filePlayer;
        clips[i].setFile(ofFilePath::getAbsolutePath("sound/hut"+ofToString(i+1)+".aif"));
        clips[i].loop();
        // clips[i].connectTo(filters.at(i)).connectTo(taps.at(i)).connectTo(mixer, i);
        clips[i].connectTo(filters.at(i)).connectTo(taps.at(i));
    }
        ofSetVerticalSync(true);
}


//vector<ofxAudioUnitTap>& Stars::getTaps(){
//    
//    return taps;
//}
Stars::~Stars(){

}
