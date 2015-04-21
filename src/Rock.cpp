//
//  Rock.cpp
//  http_example
//
//  Created by Phoenix Perry on 29/03/15.
//
//

#include "Rock.h"
Rock::Rock(Spark_core_manager *spark_){
    spark = spark_;

    mix.setInputBusCount(1);
    clip.setFile(ofFilePath::getAbsolutePath("sound/rock3.aif"));
    filter.setup(kAudioUnitType_FormatConverter, kAudioUnitSubType_Varispeed);
    clip.connectTo(filter).connectTo(tap).connectTo(mix,1);
    mix.connectTo(output);
    mix.setInputVolume(0.8f, 1);
    mix.setOutputVolume(1.0f);
    output.start();
    ofSetVerticalSync(true);
   //sla clip.loop();
  //  clip.play();
}

void Rock::update(){
  
    
    data = spark->sensor_data;
    //cout<<  data << "number!";
    int num = ofToInt(data);
    
   // cout << num << " is the rock data" << endl;
    float newSpeed = ofMap(num, 255, 0, 0, 1.0,true);
    
    AudioUnitSetParameter(filter,  kVarispeedParam_PlaybackRate,
                          kAudioUnitScope_Global,
                          0,
                          newSpeed,
                          0);
    AudioUnitSetParameter(mix, kMultiChannelMixerParam_Volume, kAudioUnitScope_Input, 0, newSpeed, 0);

 
}
//change speed based on rock
