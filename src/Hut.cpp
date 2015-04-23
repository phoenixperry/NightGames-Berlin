//
//  Hut.cpp
//  http_example
//
//  Created by Phoenix Perry on 4/4/15.
//
//

#include "Hut.h"
#include "vector.h"

Hut::Hut(){
    filters.resize(NUM_SENSORS);
    taps.resize(NUM_SENSORS);
    clips.resize(NUM_SENSORS);
    
    pads = new vector<int>(NUM_SENSORS);
    serial_reader = new SerialReader();
    serial_reader->setup();
    for(int i=0; i <= NUM_SENSORS; i++)
    {
        padsLow.push_back(1000);
        padsHigh.push_back(0);
        pads->push_back(500);
    }
    
    mixer.setInputBusCount(NUM_SENSORS);
    //audio setup
    
    for (int i=0; i<NUM_SENSORS; i++) {
        ofxAudioUnitTap tap;
        ofxAudioUnit varispeed;
        varispeed.setup(kAudioUnitType_FormatConverter, kAudioUnitSubType_Varispeed);
        filters[i] = varispeed;
        taps[i] = tap;
    }
    
    for (int i=0; i<NUM_SENSORS; i++) {
        ofxAudioUnitFilePlayer filePlayer;
        clips[i].setFile(ofFilePath::getAbsolutePath("sound/hut"+ofToString(i+1)+".wav"));
        clips[i].loop();
        clips[i].connectTo(filters.at(i)).connectTo(taps.at(i)).connectTo(mixer, i);
    }
    mixer.connectTo(output);
    mixer.setInputVolume(0.5, 2);
    mixer.setOutputVolume(1.0f);
    output.start();
    
    ofSetVerticalSync(true);
}

void Hut::update(){
    serial_reader->update();
    
    
    ///just for testing change these before shipping code
    
    pads->at(0)= serial_reader->pad11;
    pads->at(1) = serial_reader->pad9;
    pads->at(2) = serial_reader->pad5;
    pads->at(3) = serial_reader->pad3;
    pads->at(4) = serial_reader->pad0;
//    pads->at(5) = serial_reader->pad8;
//    pads->at(6) = serial_reader->pad10;
//    
    //audio update
    
    
}
void Hut::draw(){
    currentTime = ofGetElapsedTimeMillis();
    if(calibrateMode){
        for(int i =0; i < clips.size(); i++)
    //   {AudioUnitSetParameter(mixer, kMultiChannelMixerParam_Volume, kAudioUnitScope_Input, i, 0.0, 0);}
        
        if(current ==-1){
            ofDrawBitmapString("Hello Adelle! (=^･ｪ･^=)\nWelcome to calibration mode for the hut.\nYou can change the number of seconds you calibrate for with the duration variable.\n\nTo start, press 0 to calibrate the 0 pad.\n\nWatch the console for further instructions!!\n", 100,100);
        }
        
        if(current > -1)
        {
            
            if(currentTime < endTime){
                
                value = pads->at(current);
                cout << current << "I am current hut pad and pad value is "<< pads->at(current) <<endl;
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
                if(current < NUM_SENSORS)
                {
                    cout << "press" << current +1 << " to continue"<< endl;
                    calibrating = false;
                }
            }
            
            if(current == NUM_SENSORS){
                cout << "There are no more! Done calibrating all " << NUM_SENSORS<<" sensors! " <<endl;
                current = -1;
                for (int i =0; i<NUM_SENSORS; i++) {
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
        for (int i =0 ; i <NUM_SENSORS; i++) {
            float newSpeed = ofMap(pads->at(i), padsLow.at(i), padsHigh.at(i), 0.01, 1.0f,true);
            AudioUnitSetParameter(filters.at(i),  kVarispeedParam_PlaybackRate,
                                  kAudioUnitScope_Global,
                                  0,
                                  newSpeed,
                                  0);
            
        }
    }
}



void Hut::keyReleased(ofKeyEventArgs &key){
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




Hut::~Hut()
{
    delete pads;
    delete serial_reader;
    
    pads = 0;
    serial_reader =0;
    
}