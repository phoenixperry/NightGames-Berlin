//
//  Hut.cpp
//  http_example
//
//  Created by Phoenix Perry on 4/4/15.
//
//

#include "Hut.h"



Hut::Hut(){
    serial_reader = new SerialReader();
    serial_reader->setup();
    init();
}
void Hut::init (){
    
    //give these values a default that's not 0.
    for(int i=0; i <= NUM_SENSORS; i++)
    {
        padsLow[i] = serial_reader->pads[i];
        padsHigh[i] = serial_reader->pads[i];
    }
}
void Hut::update(){
    serial_reader->update();
    
    ///just for testing change these before shipping code
    pads[0] = serial_reader->pads[1];
    pads[1] =serial_reader->pads[4];
    pads[2] = serial_reader->pads[5];
    pads[3] = serial_reader->pads[7];
    pads[4] = serial_reader->pads[8];
    pads[5] = serial_reader->pads[3];
    pads[6] = serial_reader->pads[10];
    cout << pads [0];
}
void Hut::draw(){
    currentTime = ofGetElapsedTimeMillis();
    
    if(current ==-1){
            ofDrawBitmapString("Hello Adelle! :) Welcome to calibration mode for the hut.\nThis isn't super tested code.\nI suggest not mulitasking or pressing any keys that are not asked for.\n\nThere is a variable called duration. You can change that to change the number of seconds \nyou calibrate for to make this easier. \n\nTo start, press 0 to calibrate the 0 pad.", 100,100);
            }
    
    if(current > -1)
    {
        if(currentTime < endTime){
            value = pads[current];
            if( value < padsLow[current]){
                padsLow[current] = value;
                cout << value;
            }
            if(value > padsHigh[current]){
                padsHigh[current] = value;
            }
        }
        if(currentTime > endTime)
        {
            cout << "done calibrating " << current << endl;
            if(current < NUM_SENSORS)
            {
                cout << "press" << current +1 << " to continue"<< endl;
            }
        }   if(current == NUM_SENSORS){
            cout << "There are no more! Done calibrating all " << NUM_SENSORS<<" sensors! " <<endl;
            current = -1;
            for (int i =0; i<NUM_SENSORS; i++) {
                cout << "the low for pad " << i <<" is " << padsLow[i] << endl;
                cout << "the high for pad " << i <<" is " << padsHigh[i] << endl;
            }
        }
    }
    
}

void Hut::calibrate(){
        ofSetColor(255,255,0);
    if(bullshitPress){
        ofSetColor(200, 20, 255);
        ofDrawBitmapString("not a valid key. please follow the guide ok? Hit any pad to resume calibration at that location", 100, 300);
        ofSetColor(200, 200,0);
    }
    

}

void Hut::keyReleased(ofKeyEventArgs &key){
    keyPress = (char)key.keycode;
    
    if(keyPress == '0' && current ==-1)
    {   current =0;
        endTime = currentTime + duration;
        cout << "calibrating pad 0" << endl;
    }
    
    if(ofToString(keyPress) == ofToString(current+1)){
        current++;
        endTime = currentTime + duration;
        cout << "calibrating pad " << current << endl;
    }

}