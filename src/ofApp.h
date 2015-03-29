#pragma once

#include "ofMain.h"

#include "Spark_core_manager.h"

#include "Clouds.h"
#include "SerialReader.h"

class ofApp : public ofBaseApp{
  	public:
		void setup();
		void update();
		void draw();


		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
   
    Clouds *clouds;
    pitchEstimator *p;
    Spark_core_manager *spark_clouds;
    Spark_core_manager *spark_rock;
    
    float 	* buffer;

   // SerialReader port_reader;
    
    bool bSendSerialMessage;
    int countCycles;
    ofSerial * serial;
    
    
    int sensorPadValue;

};
