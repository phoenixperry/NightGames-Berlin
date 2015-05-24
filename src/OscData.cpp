//
//  OscData.cpp
//  http_example
//
//  Created by Phoenix Perry on 23/05/15.
//
//

#include "OscData.h"
#include "ofxOsc.h"
int num=0;
OscData::OscData(){
    sender.setup("192.168.0.102", 12000);
    
    receiver.setup(8001);

}

void OscData::setup(){
    
}
void OscData::sendData(vector<int> &data, string interaction){
    num=0;
    vector<int>::const_iterator it;
    for (it = data.begin(); it != data.end(); it++)
    {
        cout << *it << " ";
        ofxOscMessage m;
        m.setAddress(interaction+ "/" + ofToString(+num));
        m.addIntArg(*it);
        num++;
        sender.sendMessage(m);
        cout << "sent to osc " << *it << " at position"<< num<< endl;

    }

//    ofxOscMessage m;
//    m.setAddress(interaction+ "/" + ofToString(+num));
//    m.addIntArg(num);
//    num++;
//    sender.sendMessage(m);
//    vector<int>::const_iterator it;
//    it = data.begin();
//    while(it !=data.end())
//    {
//        ofxOscMessage m;
//        m.addIntArg(*it);
//        m.setAddress(interaction);
//        sender.sendMessage(m);
//    }
    }
