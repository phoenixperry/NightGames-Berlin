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
//

#include "Hut.h"
#include "vector.h"
#include "SerialReader.h"
Tree::Tree(SerialReader *serial_reader_, OscData *oscData_){
    pads = vector<int>(3);
    serial_reader = serial_reader_; 
    oscData = oscData_;
    for(int i=0; i <= NUM_SENSORS; i++)
    {
        padsHigh.push_back(i);
    }
    
}

void Tree::update(){
    serial_reader->update();
    pads.at(0)= serial_reader->pad0;
    pads.at(1) = serial_reader->pad3;
    pads.at(2) = serial_reader->pad5;
   // cout<< pads->at(0)<<endl;
    oscData->sendData(pads, "/touch");
}
void Tree::draw(){
}


void Tree::keyReleased(ofKeyEventArgs &key){

}




Tree::~Tree()
{
   // delete pads;

}