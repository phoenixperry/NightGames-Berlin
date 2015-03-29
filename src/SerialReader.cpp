//
//  SerialReader.cpp
//  http_example
//
//  Created by Phoenix Perry on 24/03/15.
//
//
#include "SerialReader.h"
SerialReader::SerialReader(){

}
void SerialReader::setup(){

    serial = new ofSerial();
    serial->listDevices();
    serial->setup(0, 9600);
}
void SerialReader::update(){

    serial->writeByte('a');
    
    if(serial->available()){
        
        unsigned char bytesReturned[6]; //000 new line + null terminator
        
        //  memset(bytesReadString, 0, 3);
        memset(bytesReturned, 0, sizeof(bytesReturned));
        
        // This reads the data now that arduino is sending a response,
        serial->readBytes(bytesReturned, 5);
        //check the data to make sure the new line isn't doing weird stuff
        
        string serialData = (char*) bytesReturned;
        sensorPadValue = ofToInt(serialData);
        
        cout << sensorPadValue << endl;
        //This was allows for the whole process to repeat without
        // getting strange overlapping readings from the encoder:
        serial->flush();
    }

}
    


