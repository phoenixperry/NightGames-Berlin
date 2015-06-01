//
//  OscData.cpp
//  http_example
//
//  Created by Phoenix Perry on 23/05/15.
//
//

#include "OscData.h"
#include "ofxOsc.h"
float num1, num2, num3, num4;

int num=0;
OscData::OscData(){
    sender.setup("127.0.0.1", 6448);
    
    receiver.setup(12000);

}

void OscData::setup(){
    
}
void OscData::update()
{

    while (receiver.hasWaitingMessages()) {
        
        //get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        //parse the message
       // if(m.getAddress() == "/wek/outputs")
    //    {
            num1 = m.getArgAsFloat(0);
//            num2 = m.getArgAsFloat(1);
//            num3 = m.getArgAsFloat(2);
//            num4 = m.getArgAsFloat(3);
        cout<< num1 <<" I am from wek"<<endl;
        
      //  }
    }
}
void OscData::sendData(vector<int> &data, string interaction){
    num=0;
    vector<int>::const_iterator it;
    ofxOscMessage m;
    m.setAddress("/wek/inputs");
    for (it = data.begin(); it != data.end(); it++)
    {
        //cout << *it << " ";
        //float mapped = ofMap((float)*it, 250.0f, 834.0f, 0.0f, 1.0f);
        //mapped =ofClamp(mapped, 0.0f, 1.0f);
        //cout << mapped << "i am output from "<< num<<endl;
        //m.setAddress(interaction+ "/" + ofToString(+num));
        cout<< (float)*it << "is what wekinator gets" << endl;
        m.addFloatArg((float)*it);
        num++;
        cout << num << " ran"<<endl;
    }

    sender.sendMessage(m);
    }



