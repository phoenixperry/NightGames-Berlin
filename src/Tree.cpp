//
//  Tree.cpp
//  http_example
//
//  Created by Phoenix Perry on 22/04/15.
//
//

#include "Tree.h"
//
//  Hut.cpp
//  http_example
//
//  Created by Phoenix Perry on 4/4/15.
//
//

#include "Hut.h"
#include "vector.h"

Tree::Tree(){
    filters.resize(NUM_SENSORS_TREE);
    taps.resize(NUM_SENSORS_TREE);
    clips.resize(NUM_SENSORS_TREE);
    
    pads = new vector<int>(NUM_SENSORS_TREE);

    for(int i=0; i <= NUM_SENSORS_TREE; i++)
    {
        padsLow.push_back(1000);
        padsHigh.push_back(0);
        pads->push_back(500);
    }
    
    mixer.setInputBusCount(NUM_SENSORS_TREE);
    //audio setup
    
    for (int i=0; i<NUM_SENSORS_TREE; i++) {
        ofxAudioUnitTap tap;
        ofxAudioUnit varispeed;
        varispeed.setup(kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
        varispeed.loadCustomPreset("audioPresets/lowpass_start.aupreset");
        
        filters[i] = varispeed;
        taps[i] = tap;
    }
    
    for (int i=0; i<NUM_SENSORS_TREE; i++) {
        ofxAudioUnitFilePlayer filePlayer;
        
        clips[i].setFile(ofFilePath::getAbsolutePath("sound/tree"+ofToString(i+1)+".wav"));
        clips[i].loop();
        clips[i].connectTo(filters.at(i)).connectTo(taps.at(i)).connectTo(mixer, i);
    }
    mixer.connectTo(output);
    mixer.setInputVolume(0.5, 2);
    mixer.setOutputVolume(0.1f);
    output.start();
    
    ofSetVerticalSync(true);
}

void Tree::update(int pad7, int pad8){
     if(!calibrateMode) ofBackground(0, 255, 0);
    //updating the pads from the tree
   if(calibrateMode ==true)
       
       // account for the fact setup might not of run yet
   {pads->at(0)= pad7;
       pads->at(1) = pad8;}
    
    //audio update
    
    
}
void Tree::draw(){
    ofBackground(255, 255, 255);
    currentTime = ofGetElapsedTimeMillis();
    if(calibrateMode){
        ofBackground(0, 0, 255);
        for(int i =0; i < clips.size(); i++)
        {AudioUnitSetParameter(mixer, kMultiChannelMixerParam_Volume, kAudioUnitScope_Input, i, 0.0, 0);}
        
        if(current ==-1){
            ofDrawBitmapString("Hello! (=^･ｪ･^=)\nWelcome to calibration mode for the TREE.\nYou can change the number of seconds you calibrate for with the duration variable.\n\nTo start, press 0 to calibrate the 0 pad.\n\nWatch the console for further instructions!!\n", 100,100);
        }
        
        if(current > -1)
        {
            
            if(currentTime < endTime){
                
                value = pads->at(current);
                //cout << current << "I am current hut pad and pad value is "<< pads->at(current) <<endl;
                if( value < padsLow.at(current)){
                    padsLow[current] = value;
                    
                }
                if(value > padsHigh.at(current)){
                    padsHigh.at(current) = value;
                }
            }
            if(currentTime > endTime)
            {
                
                cout << "done calibrating " << current << "low is "<< padsLow.at(current)<< " high is "<< padsHigh.at(current)<<endl;
                if(current < NUM_SENSORS_TREE)
                {
                    cout << "press" << current +1 << " to continue"<< endl;
                    calibrating = false;
                }
            }
            
            if(current == NUM_SENSORS_TREE){
                cout << "There are no more! Done calibrating all " << NUM_SENSORS_TREE<<" sensors! " <<endl;
                current = -1;
                for (int i =0; i<NUM_SENSORS_TREE; i++) {
                    cout << "the low for pad " << i <<" is " << padsLow[i] << endl;
                    cout << "the high for pad " << i <<" is " << padsHigh[i] << endl;
                    cout << "press x to exit calibration"<<endl;
                }
            }
        }
    }
    //end calibration mode
    
    //add game code here!
    
    if(!calibrateMode){
        for (int i =0 ; i <NUM_SENSORS_TREE; i++) {
            float newCutoff = ofMap(pads->at(i), padsLow.at(i), padsHigh.at(i), 20, 191,true);
            
             float res = ofMap(pads->at(i), padsLow.at(i), padsHigh.at(i), 2, 7.26,true);
            AudioUnitSetParameter(filters[0],
                                  kLowPassParam_CutoffFrequency,
                                  kAudioUnitScope_Global,
                                  0,
                                  newCutoff,
                                  0);
            AudioUnitSetParameter(filters[1],
                                  kLowPassParam_CutoffFrequency,
                                  kAudioUnitScope_Global,
                                  0,
                                  res,
                                  0);

            
        }
    }
}



void Tree::keyReleased(ofKeyEventArgs &key){
    keyPress = (char)key.keycode;
    
    if(keyPress =='`' && current ==-1)calibrateMode = false;
    
    if(keyPress == '0' && current ==-1)
    {
        current = 0;
        endTime = currentTime + duration;
        cout << "calibrating pad 0" << endl;
        calibrating = true;
        value = 0;
    }
    
    if(ofToString(keyPress) == ofToString(current+1) && calibrating ==false){
        
        endTime = currentTime + duration;
        cout << "calibrating pad " << current << endl;
        calibrating = true;
        current ++;
    }
    
    if(keyPress =='X')
    {
        calibrateMode = false;
        cout << "bye!!! Game starting now."<< endl;
    }
}




Tree::~Tree()
{
    delete pads;

    
    pads = 0;

    
}