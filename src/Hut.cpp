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
    for(int i=0; i <= NUM_SENSORS; i++)
    {
        padsLow[i] = 1000;
        padsHigh[i] = 0;
    }
}

void Hut::update(){
    serial_reader->update();
    
    ///just for testing change these before shipping code
    if(serial_reader->serial->available())
    {
        pads[0] = &serial_reader->pad1;
        pads[1] = &serial_reader->pad3;
        pads[2] = &serial_reader->pad4;
        pads[3] = &serial_reader->pad5;
        pads[4] = &serial_reader->pad7;
        pads[5] = &serial_reader->pad8;
        pads[6] = &serial_reader->pad10;
    }
       // cout << pads [0];
}
void Hut::draw(){
    currentTime = ofGetElapsedTimeMillis();
    
    if(current ==-1){
            ofDrawBitmapString("Hello Adelle! :) Welcome to calibration mode for the hut.\nThis isn't super tested code.\nI suggest not mulitasking or pressing any keys that are not asked for.\n\nThere is a variable called duration. You can change that to change the number of seconds \nyou calibrate for to make this easier. \n\nTo start, press 0 to calibrate the 0 pad.", 100,100);
            }
    if(serial_reader->serial->available()){
    if(current > -1)
    {
        if(currentTime < endTime){
            value = *pads[current];
            if( value < padsLow[current]){
                padsLow[current] = value;
               // cout << value;
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