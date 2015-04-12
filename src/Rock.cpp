//
//  Rock.cpp
//  http_example
//
//  Created by Phoenix Perry on 29/03/15.
//
//

#include "Rock.h"
//Rock::Rock(Spark_core_manager *spark_){
//    spark = spark_;
Rock::Rock(){
    mix.setInputBusCount(1);
    clip.setFile(ofFilePath::getAbsolutePath("sound/rock3.aif"));
    filter.setup(kAudioUnitType_FormatConverter, kAudioUnitSubType_Varispeed);
    clip.connectTo(filter).connectTo(tap).connectTo(mix,1);
    mix.connectTo(output);
    mix.setInputVolume(0.8f, 2);
    mix.setOutputVolume(1.0f);
    output.start();
    ofSetVerticalSync(true);
    clip.loop();
    
}

//change speed based on rock
