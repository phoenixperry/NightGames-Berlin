#pragma once

#include "ofMain.h"
#include "Spark_core_manager.h"
#include "Clouds.h"
#include "SerialReader.h"
#include <vector>
#include "Hut.h"
#include "Stars.h"
#include "Rock.h"
#include "OscData.h"
#include "Flowers.h"
using namespace std;

class ofApp : public ofBaseApp{
private:
    
    int scaleDegree;
    void trigger();
    void setScaleDegreeBasedOnMouseX();

public:
    ofxTonicSynth synth;
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioRequested (float * output, int bufferSize, int nChannels);
    
    SerialReader *serial_reader;
    OscData *oscData;
 
    float lightLevel;
    vector<float> ardVals;
    ofSoundPlayer player;
    
    void setupSound();
    int average; 

};
