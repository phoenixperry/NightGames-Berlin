//
//  Clouds.cpp
//  http_example
//
//  Created by Phoenix Perry on 08/03/15.
//
//

#include "Clouds.h"
#include "Spark_core_manager.h"

Clouds::Clouds(Spark_core_manager *spark_, pitchEstimator *p_){
    spark = spark_;
    p = p_;
    
        //varispeed.loadCustomPreset(ofFilePath::getAbsolutePath("audioPresets/reverb_start.aupreset"));
    
    
    filters.resize(NUM_SENSORS);
    taps.resize(NUM_SENSORS);
    clips.resize(NUM_SENSORS);
    

    mixer.setInputBusCount(NUM_SENSORS);
    //audio setup
    
    for (int i=0; i<NUM_SENSORS; i++) {
        ofxAudioUnitTap tap;
        ofxAudioUnit varispeed;

        varispeed.setup(kAudioUnitType_Effect, kAudioUnitSubType_Delay);
  
        varispeed.loadCustomPreset("audioPresets/delay_start.aupreset");
        filters[i] = varispeed;
        taps[i] = tap;
    }
    
    for (int i=0; i<NUM_SENSORS; i++) {
        ofxAudioUnitFilePlayer filePlayer;
        
        clips[i].setFile(ofFilePath::getAbsolutePath("sound/cloud"+ofToString(i+1)+".wav"));
        clips[i].loop();
        clips[i].connectTo(filters.at(i)).connectTo(taps.at(i)).connectTo(mixer, i);
    }
    mixer.connectTo(output);
    mixer.setInputVolume(0.5, 2);
    mixer.setOutputVolume(1.0f);
    output.start();
    
    ofSetVerticalSync(true);

    
}
void Clouds::update(){
    currentTime = ofGetElapsedTimeMillis();
    float tx = currentTime*0.1+50; //volume smoothing
    
    for(int i =0; i < 5; i++)
    {
     
        //Calculate the sample volume as 2D Perlin noise,
        //depending on tx and ty = i * 0.2
        float ty = i*0.2;
        vol[i] = ofNoise( tx, ty );	//Perlin noise
        ofMap( stars_average, 0, 1000, 0, 100);
        AudioUnitSetParameter(filters[i], kDelayParam_DelayTime , kAudioUnitScope_Global, 0, stars_average, 0);
        mixer.setInputVolume(vol[i]*stars_average, i);
    }
    
    

    
}
void Clouds::draw(){
    //int x = ofGetMouseX();
   // mixer.setPan(ofMap(x, 0, ofGetWidth(), -1, 1, true));
}

void Clouds::update_star_data(float val)
{
    stars_average = val;
}

void Clouds::triggerLed(string color)
{
    //spark->postData("set_color", color);
}