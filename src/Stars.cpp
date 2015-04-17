//
//  Stars.cpp
//  http_example
//
//  Created by Phoenix Perry on 4/11/15.
//
//
#include <sstream>
#include "Stars.h"
Stars::Stars(Spark_core_manager *spark_){
    spark = spark_;
    sensors.resize(NUM_LIGHT_SENSORS);
    filters.resize(NUM_LIGHT_SENSORS);
    taps.resize(NUM_LIGHT_SENSORS);
    clips.resize(NUM_LIGHT_SENSORS);
    mixer.setInputBusCount(NUM_LIGHT_SENSORS/2);
    
    for (int i=0; i<NUM_LIGHT_SENSORS/2; i++) {
        ofxAudioUnitTap tap;
        ofxAudioUnit lowPass;
        lowPass.setup(kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
        lowPass.loadCustomPreset("LowPass_stars.aupreset");
        filters[i] = lowPass;
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
    mixer.setOutputVolume(0.8f);
    output.start(); 
}



void Stars::update(){
    string data = spark->sensor_data;
    vector<int> vect;
    stringstream ss(data);
    int i;
    int count=0;
    while(ss >> i)
    {
        vect.push_back(i);
        if(ss.peek()== ',')
            ss.ignore();
        sensors[count] = i;
        count++;
    }
    count = 0;
    for(int i=0; i<sensors.size(); i++)
    {
      //  cout << sensors[i] << "light sensor data source " << i << endl;
      //this comment will print out the sensor data coming in from the sparkcore.
    }
    
    float star_one_average = sensors[0] + sensors[1]/2;
    float star_two_average = sensors[2] + sensors[3]/2;
    float newCutoff = ofMap(star_one_average, 1000, 4000, 10, 6900);
    float newCutoffTwo = ofMap(star_two_average, 2000, 4000, 10, 6900);
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
                          newCutoffTwo,
                          0);
    float vol = ofMap(star_one_average, 1000.0f, 4000.0f, 0.0f, 1.0f);
    float volTwo = ofMap(star_two_average, 1000.0f, 40000.0f, 0.0f, 1.0f);

    AudioUnitSetParameter(mixer, kMultiChannelMixerParam_Volume, kAudioUnitScope_Input, 0, vol, 0);
    AudioUnitSetParameter(mixer, kMultiChannelMixerParam_Volume, kAudioUnitScope_Input, 1, volTwo, 0);

}

Stars::~Stars(){

}
