//
//  Tree.cpp
//  http_example
//
//  Created by Phoenix Perry on 22/04/15.
//
//
#include "Tree.h"
//
//  Hut.cpp
//  http_example
//
//  Created by Phoenix Perry on 4/4/15.
//
#include <vector.h>
#include "SerialReader.h"
Tree::Tree(SerialReader *serial_reader_){
    
    oscData = new OscData(6448);
    pads = vector<float>(numSensors);
   
    serial_reader = serial_reader_;
}
//Tree::Tree(SerialReader *serial_reader_){
//
//}

void Tree::update(){
    //yea old serial data
    serial_reader->update();
    //touch sensor data
    pads.at(0)= serial_reader->pad0;
    pads.at(1) = serial_reader->pad3;
    pads.at(2) = serial_reader->pad5;
    //this might be questionable to pass as a reference
    vector<float>& pads_ = pads;
    sendToWekinator(pads_);
    //learned data from wekinator outputed back to OF
    //nums = oscData->getData("/tree/input");
}

void Tree::sendToWekinator(vector<float>& pads){
    oscData->sendData(pads, "/tree/input");
}
void Tree::setHealth(){
    float total =0.0f;
    //this is for when I get flower two built
    for(int i=0; i< nums->size(); i++)
    {
        total = total+nums->at(i);
    }
    
    health = total/nums->size();
}

void Tree::sendHealth(){
    //this is cheap I just happen to know there's one sensor here. when flower two is made this needs to be fixed.
    vector<float>health_ = vector<float>(1);
    health_.at(0) = health;
    //this will make sound from wekinator to ableton if all goes well
    
    //send the data back out to wekinator after averaging it
    //for now this isn't needed so much.
    oscData->sendData(health_, "/tree/output");
}

Tree::~Tree()
{
   // delete osc
}