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
    
    oscData = new OscData(6448, 12000);
    filteredOsc = new OscData(8000, 8001);

    
    pads =  vector<float>(numSensors);
    serial_reader = serial_reader_;
    
    padsFiltered = new vector<float>();
}

void Tree::update(){
    //yea old serial data
    //touch sensor data
    pads.at(0)= serial_reader->pad0;
    pads.at(1) = serial_reader->pad3;
//    cout << pads.size() << " num pads" << endl;
//    cout << pads.at(0) << " pad 0 "<<endl;
//    cout << pads.at(1) << " pads 1" << endl;
//    
    sendToWekinator(pads, "/tree/inputs");
    
    //get data back from wekinator
    padsFiltered = oscData->getData("/tree/outputs");
    
    //effect data with health
    vector<float>::iterator it;
    int num = 0;
    for (it = padsFiltered->begin(); it != padsFiltered->end(); it++)
    {
        *it = health+*it/2; //average two nums
    }
    
    //send data to osculator
    vector<float> &pads_ = pads;
    filteredOsc->sendData(pads_, "/tree/filtered");
    
}


void Tree::sendToWekinator(vector<float> &pads_, string inputToWekinator){
 
    oscData->sendData(pads, inputToWekinator);
}


Tree::~Tree()
{
   // delete osc
}