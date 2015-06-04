//
//  OscData.cpp
//  http_example
//
//  Created by Phoenix Perry on 23/05/15.
//
//

#include "OscData.h"
#include "ofxOsc.h"
#include "vector.h"


OscData::OscData(int port_number, int incoming_port_){
    
    sender.setup("127.0.0.1", port_number);
    
    receiver.setup(incoming_port_);
    nums = new vector<float>(1);
}

vector<float>* OscData::getData(string inputString)
{
    nums->clear();
    while (receiver.hasWaitingMessages()) {

        //get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        nums->resize(m.getNumArgs());
        //parse the message
        if(m.getAddress() == inputString)
        {
            for(int i =0; i < m.getNumArgs(); i++)
            {
                nums->at(i) = m.getArgAsFloat(i);
                //cout << m.getArgAsFloat(i) << "raw from flower" << endl;
            }
        }
    }
        return nums;
}
void OscData::sendData(float &num, string outputString)
{
    ofxOscMessage m;
    m.setAddress(outputString);
    m.addFloatArg(num);
    sender.sendMessage(m);
    
}

void OscData::sendData(vector<float> &data, string outputString){
    int num =0;
    vector<float>::const_iterator it;
    ofxOscMessage m;
    m.setAddress(outputString);
    for (it = data.begin(); it != data.end(); it++)
    {
        //cout << *it << " ";
        //float mapped = ofMap((float)*it, 250.0f, 834.0f, 0.0f, 1.0f);
        //mapped =ofClamp(mapped, 0.0f, 1.0f);
        //cout << mapped << "i am output from "<< num<<endl;
        //m.setAddress(interaction+ "/" + ofToString(+num));
        num++;
        //cout<< *it << "is what wekinator gets "<< num << endl;
        m.addFloatArg(*it);
        
    }
    
    sender.sendMessage(m);
}



//void OscData::sendData(vector<float> *data, string outputString){
//    int num =0;
//    vector<float>::const_iterator it;
//    ofxOscMessage m;
//    m.setAddress(outputString);
//    for (it = data->begin(); it != data->end(); it++)
//    {
//        //cout << *it << " ";
//        //float mapped = ofMap((float)*it, 250.0f, 834.0f, 0.0f, 1.0f);
//        //mapped =ofClamp(mapped, 0.0f, 1.0f);
//        //cout << mapped << "i am output from "<< num<<endl;
//        //m.setAddress(interaction+ "/" + ofToString(+num));
//        num++;
//        cout<< *it << "is what wekinator gets "<< num << endl;
//        m.addFloatArg(*it);
//        
//    }
//    
//    sender.sendMessage(m);
//}


