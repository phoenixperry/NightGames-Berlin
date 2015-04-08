//
//  Hut.cpp
//  http_example
//
//  Created by Phoenix Perry on 4/4/15.
//
//

#include "Hut.h"
#include "vector.h"
//just to initialize the array before we use it should serial fail out

Hut::Hut(){
    pads = new vector<int>();
    serial_reader = new SerialReader();
    serial_reader->setup();
    for(int i=0; i <= NUM_SENSORS; i++)
    {
        padsLow.push_back(1000);
        padsHigh.push_back(0);
        pads->push_back(500);
    }
}

void Hut::update(){
    serial_reader->update();
    
    ///just for testing change these before shipping code
    if(serial_reader->serial->available())
    {
        pads->at(0)= serial_reader->pad1;
        pads->at(1) = serial_reader->pad3;
        pads->at(2) = serial_reader->pad4;
        pads->at(3) = serial_reader->pad5;
        pads->at(4) = serial_reader->pad7;
        pads->at(5) = serial_reader->pad8;
        pads->at(6) = serial_reader->pad10;
    }
       // cout << pads [0];
}
void Hut::draw(){
    currentTime = ofGetElapsedTimeMillis();
    if(calibrateMode){
        if(current ==-1){
                    ofDrawBitmapString("Hello Adelle! :) Welcome to calibration mode for the hut.\nWARNING: This isn't super safe code.\nI suggest not mulitasking or pressing any keys that are not asked for.\nWARNING: Hitting the same key more than once will break this\nThere is a variable called duration. You can change that to change the number of seconds \nyou calibrate for to make this easier. \n\nTo start, press 0 to calibrate the 0 pad. Watch the console for further instructions!!\n Sorry time and all... feel free to add some code here to print to screen\n", 100,100);
            }
            if(serial_reader->serial->available()){
            if(current > -1)
            {
                if(currentTime < endTime){
                    value = pads->at(current);
                    if( value < padsLow.at(current)){
                        padsLow[current] = value;
                       // cout << value;
                    }
                    if(value > padsHigh.at(current)){
                        padsHigh.at(current) = value;
                    }
                }
                if(currentTime > endTime)
                {
                    cout << "done calibrating " << current << endl;
                    if(current < NUM_SENSORS)
                    {
                        cout << "press" << current +1 << " to continue"<< endl;
                    }
                }
                
                if(current == NUM_SENSORS){
                    cout << "There are no more! Done calibrating all " << NUM_SENSORS<<" sensors! " <<endl;
                    current = -1;
                    for (int i =0; i<NUM_SENSORS; i++) {
                        cout << "the low for pad " << i <<" is " << padsLow[i] << endl;
                        cout << "the high for pad " << i <<" is " << padsHigh[i] << endl;
                        cout << "press x to exit calibration"<<endl;
                    }
                }
            }
        }
    }//end calibration mode
    
    
    //add game code here!
    
    
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
    if(keyPress =='X')
    {
        calibrateMode = false;
        cout << "bye!!! Game starting now."<< endl;
    }
}