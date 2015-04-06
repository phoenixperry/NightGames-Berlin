//
//  Clouds.cpp
//  http_example
//
//  Created by Phoenix Perry on 08/03/15.
//
//

#include "Clouds.h"
#include "Spark_core_manager.h"
Spark_core_manager *spark;
Clouds::Clouds(Spark_core_manager *spark_, pitchEstimator *p_){
    spark = spark_;
    p = p_;
    reverb.setup('aufx', 'mrev', 'appl');

    
    //reverb.connectTo(mixer).connectTo(output);
    
    output.start();
    
    clouds1.setFile(ofToDataPath("sound/clouds1.aif"));
    clouds2.setFile(ofToDataPath("sound/clouds2.aif"));
    clouds3.setFile(ofToDataPath("sound/clouds3.aif"));
    clouds4.setFile(ofToDataPath("sound/clouds4.aif"));
    clouds5.setFile(ofToDataPath("sound/clouds5.aif"));

    
    clouds1.connectTo(reverb).connectTo(tap1);
    clouds2.connectTo(reverb).connectTo(tap2);
    clouds3.connectTo(reverb).connectTo(tap3);
    clouds4.connectTo(reverb).connectTo(tap4);
    clouds5.connectTo(reverb).connectTo(tap5);
    mixer.setInputBusCount(5);
    
    tap1.connectTo(mixer, 0);
    tap2.connectTo(mixer, 1);
    tap3.connectTo(mixer, 2);
    tap4.connectTo(mixer, 3);
    tap5.connectTo(mixer, 4);
    
  //  mixer.connectTo(output);
  //  output.start();
    
    ofSetVerticalSync(true);

    clouds1.loop();
    clouds2.loop();
    clouds3.loop();
    clouds4.loop();
    clouds5.loop();
 //   mixer.setInputVolume(.5,2);

    delay.showUI();
    startTime = ofGetElapsedTimeMillis();
    
}
void Clouds::update(){
    currentTime = ofGetElapsedTimeMillis() - startTime;
    
}
void Clouds::draw(){
    int x = ofGetMouseX();
    mixer.setPan(ofMap(x, 0, ofGetWidth(), -1, 1, true));
   
}

void Clouds::triggerLed(string color)
{
    //spark->postData("set_color", color);
}