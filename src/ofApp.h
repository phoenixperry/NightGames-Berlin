#pragma once

#include "ofMain.h"
#include "Spark_core_manager.h"
#include "Clouds.h"
#include "SerialReader.h"
#include <vector>
#include "Hut.h"
#include "Stars.h"
using namespace std;
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
    
    Hut *hut;
   // Stars *stars;
    

  //  ofxAudioUnitOutput output;
  //  ofxAudioUnitMixer mixer;
    
};
