#include "ofApp.h"

#define NUMBER_OF_KEYS 10

//--------------------------------------------------------------
void ofApp::setup(){
    serial_reader = new SerialReader();
    serial_reader->setup();
    tree = new Tree(serial_reader);
}
//--------------------------------------------------------------
void ofApp::update(){
    serial_reader->update();
    tree->update();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
   }

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    }

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    

    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

