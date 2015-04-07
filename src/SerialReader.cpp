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
        
        unsigned char bytesReturned[7]; //)00:000\n\0 (New line + null terminator in serial string must all be accounted for in the bytes returned)
        
        //  memset(bytesReadString, 0, 3);
        memset(bytesReturned, 0, sizeof(bytesReturned));
        
        // This reads the data now that arduino is sending a response,
        serial->readBytes(bytesReturned, 6);
        //check the data to make sure the new line isn't doing weird stuff
        
        serialData = (char*) bytesReturned;
        //throw in a safety check for different serial messages from arduio's side
        if(serialData.length() > 5){
            string pad = serialData.substr(0,2);
            string data = serialData.substr(3,5);
            int num = ofToInt(data);
          //  cout << pad << " " << data << endl;
    
      
//            if(pad == "00"){pad[0]=num;}
//            else if(pad=="01"){ pad[1] = num;}
//            else if(pad=="02"){ pad[2] = num;}
//            else if(pad=="03"){ pad[3] = num;}
//            else if(pad=="04"){ pad[4] = num;}
//            else if(pad=="05"){ pad[5] = num;}
//            else if(pad=="06"){ pad[6] = num;}
//            else if(pad=="07"){ pad[7] = num;}
//            else if(pad=="08"){ pad[8] = num;}
//            else if(pad=="09"){ pad[9] = num;}
//            else if(pad=="10"){ pad[10] = num;}
//            else{pad[11] = num;}
          //  cout << pad0 << " from serial"<< endl;
            if(pad == "00"){pad0=num;}
            else if(pad=="01"){ pad1= num;}
            else if(pad=="02"){ pad2 = num;}
            else if(pad=="03"){ pad3 = num;}
            else if(pad=="04"){ pad4 = num;}
            else if(pad=="05"){ pad5 = num;}
            else if(pad=="06"){ pad6 = num;}
            else if(pad=="07"){ pad7 = num;}
            else if(pad=="08"){ pad8 = num;}
            else if(pad=="09"){ pad9 = num;}
            else if(pad=="10"){ pad10 = num;}
            else{pad11 = num;}
            
        }else{ cout << "failed to get serial data" << endl;}
        //cout << pad << " pad "<< num << " data "<<endl;
      //  cout << "pad 5 " << pad5<< endl;
        
        sensorPadValue = ofToInt(serialData);
        
       // cout << sensorPadValue <<" is sensor data from bare" << endl;
        //This was allows for the whole process to repeat without
        // getting strange overlapping readings from the encoder:
        serial->flush();
    }

}
    


