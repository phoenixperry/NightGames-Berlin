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
    for(int i=0; i <NUM_SENSORS; i++){
        int pad_low = 0;
        int pad_high =0;
        int pad = 0;
        padsLow[i] =pad_low;
        padsHigh[i] = pad_high;
        pads[i] = pad;
        calibrate_pad[i] = false;
        
    }
}
void Hut::update(){
    serial_reader->update();
    
    ///just for testing change these before shipping code
    pads[0] = serial_reader->pads[0];
    pads[1] =serial_reader->pads[3];
    pads[2] = serial_reader->pads[4];
    pads[3] = serial_reader->pads[5];
    pads[4] = serial_reader->pads[7];
    pads[5] = serial_reader->pads[8];
    pads[6] = serial_reader->pads[10];
    
    
}
void Hut::draw(){
    currentTime = ofGetElapsedTimeMillis();
   
    if(calibrate_state){
        if(calibrate_pad[calibrateNum]==false && keyPress!="0" && welcomeMessage) {
            ofDrawBitmapString("Hello Adelle! :) Welcome to calibration mode for the hut.\nThis isn't super tested code.\nI suggest not mulitasking or pressing any keys that are not asked for.\n\nThere is a variable called duration. You can change that to change the number of seconds \nyou calibrate for to make this easier. \n\nTo start, press 0 to calibrate the 0 pad.", 100,100);
        }

        calibrate();
    }
}
void Hut::calibrate(){
   
        ofSetColor(255,255,0);
    
       /////////////////////////////////////////////////////////////
    //main loop
  
    if(keyPress==currentPress && calibrate_pad[calibrateNum]==false) {calibrate_pad[calibrateNum] = true; welcomeMessage = false;}
    cout << keyPress << " is keypress" << currentPress <<  " is currentPress"<<endl;
        if(currentTime < endTime && keyPress == currentPress && calibrate_pad[calibrateNum]){
            ofDrawBitmapString("Get clear of pad "+ ofToString(keyPress) + " I'm now calibrating the untouched state for the next "+ ofToString(duration/1000) +" seconds.", 100, 120);
            current_data = pads[0];
            
            
            if(current_data > world_record){
                padsHigh[0] = current_data;
                world_record = current_data;
                cout << "setting high"<<endl;
            }
            
        }else if (currentTime > endTime &&keyPress ==currentPress && calibrate_pad[calibrateNum])
        {
            ofDrawBitmapString("pad" + ofToString(currentPress)+ " is set to a high of " + ofToString(padsHigh[0]), 10, 140);
            
            ofDrawBitmapString("press" + ofToString(subState)+ " to calibrate a touched state for pad "+ ofToString(currentPress)+  "touch as much of the sensor during the calibration as possible. ", 10, 150);
        }
    if(currentTime < endTime && keyPress==subState && calibrate_pad[calibrateNum]){
            ofDrawBitmapString("I'm now calibrating the touched state for the next "+ofToString(duration/1000) +" seconds.", 100, 120);
            current_data = pads[0];
            
            if(current_data < world_record){
                padsLow[0] = current_data;
                world_record = current_data;
                //cout << "setting low"<<endl;
            //    cout << padsLow[0] << " low num " << pads[0] << " pad 0" << endl;
            }
        }else if (currentTime > endTime &&keyPress == subState &&
                  calibrate_pad[calibrateNum])
        {
            ofDrawBitmapString("pad0 is set to a low of " + ofToString(padsLow[0]), 100, 140);
            ofSetColor(255, 39, 9);
            ofDrawBitmapString("Let's move on to pad "+ofToString(calibrateNum+1) + " Press " +ofToString(calibrateNum+1) +" to calibrate pad " + ofToString(calibrateNum+1), 100, 160);
            calibrate_pad[calibrateNum+1] = true;
            calibrateNum++;

        }
    
    ///////next state
    if(currentTime < endTime && keyPress == "1" && calibrate_pad[calibrateNum]){
         subState ="B";
         calibrate_pad[calibrateNum-1]  = false;
        ofDrawBitmapString("Get clear of pad 1 I'm now calibrating the untouched state for the next "+ ofToString(duration/1000) +" seconds.", 100, 180);
        current_data = pads[1];
        if(current_data > world_record){
            padsHigh[1] = current_data;
            world_record = current_data;
            cout << "setting high"<<endl;
        }
        
    }else if (currentTime > endTime &&keyPress =="1" && calibrate_pad[calibrateNum])
    {
        ofDrawBitmapString("pad1 is set to a high of " + ofToString(padsHigh[1]), 10, 140);
        
        ofDrawBitmapString("press b to calibrate a touched state for pad 1. touch as much of the sensor during the calibration as possible. ", 10, 150);
    }
    if(currentTime < endTime && keyPress=="B" &&calibrate_pad[calibrateNum]){
        ofDrawBitmapString("I'm now calibrating the touched state for the next "+ ofToString(duration/1000) +" seconds.", 100, 120);
        current_data = pads[1];
        
        if(current_data < world_record){
            padsLow[1] = current_data;
            world_record = current_data;
            //cout << "setting low"<<endl;
            cout << padsLow[1] << " low num " << pads[1] << " pad 1" << endl;
        }
    }else if (currentTime > endTime &&keyPress =="B" && calibrate_pad[calibrateNum])
    {
        ofDrawBitmapString("pad1 is set to a low of " + ofToString(padsLow[1]), 100, 140);
        ofSetColor(255, 39, 9);
        ofDrawBitmapString("Let's move on to pad 2. Press 2 to calibrate pad 2 ", 100, 160);
        calibrate_pad[calibrateNum+1] = true;
    }

    
    

}

void Hut::keyReleased(ofKeyEventArgs &key){
    keyPress = (char)key.keycode;
    cout << keyPress << "is key press ";
    if(calibrate_state)endTime = currentTime+duration;
    
 
    stringstream ss;
    ss << calibrateNum;
    currentPress = ss.str();}

