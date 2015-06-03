#pragma once

#include "ofMain.h"
#include "SerialReader.h"
#include <vector>
#include "OscData.h"
#include "Flowers.h"
#include "Tree.h"
using namespace std;

class ofApp : public ofBaseApp{
private:
    
public:
 
    
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
    
    
    SerialReader *serial_reader;
    Tree *tree;
    

};
