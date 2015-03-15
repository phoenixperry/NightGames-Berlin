#include "ofApp.h"
#include "RtAudio.h"
//ok let's talk bigger picture b/c for people who aren't web people the spark sdk is silly confusing.
//the way it works it that it gets and posts data via HTTP (the web!)
//all you need to do is get your spark core's device ID and your access token. That part of the SDK makes sense so see their site.
//all that curl business is doing is getting and sending http. you can do this in everything from python to c++ fairly easily.
//in python you can use requests.get("url_here") and it's a thing of simple beauty. OF is well a bit more work and 2 addons. This kind of hurts my feelings. See my includes in the header file or my addons here to see which ones I used. I use one add on to get and post http data from/to spark and another to parse the json object you get back. If you don't know what json is, google it but is basically just a comma seperated field of data that's easy to deal with.

//now down to business

//you need a data buffer to write data from spark into
ofBuffer buff;


//--------------------------------------------------------------
void ofApp::setup(){
    spark = new Spark_core_manager(); 
    spark->startThread(true, false);
    
    //pitch_detect.setup();
//    startBufferSize = 512;
//    sampleRate = 44100;
//    buffer = new float[startBufferSize];
//    
//    buffer = new float[startBufferSize];
//    memset(buffer, 0, startBufferSize * sizeof(float));
//    soundStream.setup(0,1,sampleRate,startBufferSize,4);
//    soundStream.setInput(this);
    p = new pitchEstimator;
    p->setup();
    //setup your URL - this is gonna change and see the spark sdk for this bit. Everyone's will be different
    //and depending on your own device ID.
//    action_url = "https://api.spark.io/v1/devices/50ff6c065067545637110387/val?access_token=7c3a17b73062e01cc52682cbf69a7941d17acb22";
//    
//    //this is a listener that fires a function everytime there's a new even here involving http
//    ofAddListener(httpUtils.newResponseEvent,this,&ofApp::newResponse);
//
//    //start up http stuffs
//    httpUtils.start();
    
   // vector<RtAudio::DeviceInfo> deviceVector; // to store the device info
    
//    ofPtr<RtAudio> audioTemp;
//    try {
//        audioTemp = ofPtr<RtAudio>(new RtAudio());
//    } catch (RtError &error) {
//        error.printMessage();
//        return;
//    }
//    int devices = audioTemp->getDeviceCount();
//    RtAudio::DeviceInfo info;
//    for (int i=0; i< devices; i++) {
//        try {
//            deviceVector.push_back(audioTemp->getDeviceInfo(i)); // actually add it
//        } catch (RtError &error) {
//            error.printMessage();
//            break;
//        }
//    }
    
//    cout << deviceVector.at(0).name << endl; // now we can print the name
    
}  



//--------------------------------------------------------------
void ofApp::update(){
    p->update();
   // cout << ofGetFrameRate() << endl;
    //spark->update();
    //get updates from spark -- again this is specific to your core! the val? is the exposed variable from spark. you'll see it
    //again in my spark code exmaple as Spark.variable("val", &val, INT);
//     httpUtils.getUrl("https://api.spark.io/v1/devices/50ff6c065067545637110387/val?access_token=c8c4c3aa486fa8e15d8d1edeeff64ec9d878052a");
    
}
//this function fires everytime there's new http data to deal with
void ofApp::newResponse(ofxHttpResponse & response){
   // responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
    //note that it can't tell the 2 different types of json objects apart from get and post so the get and post both make objects and both
    //save out to this result which is kinda annoying. this is why I did the if statements to get the name

    //print raw json data so you can see all the data. see the ofxjson exampl for more info here.
//    // cout << responseStr;
//    bool parse =result.parse(response.responseBody);
//    if(parse)
//    {
//        
//        result.getRawString();
//        int val;
//        val = result["result"].asInt();
//        string name = result["name"].asString();
//        
//        if(name =="val"){
//            //this is sensor data
//            cout << val << " is sensor data" << endl;
//        }
//        if(name =="archimedes")
//        {
//            //this is the function trigger from of to spark core and the return value from sparkcore.
//            cout<< result["return_value"].asInt() << " is returned data" << endl;
//        }
//    }else{
//        cout << "json parse failure";
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    p->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //on key press fire off a function on the spark please. the data it sends back via http will fire off an event and call the function void ofApp::newResponse(ofxHttpResponse & response)
    
 //   httpUtils.postData("https://api.spark.io/v1/devices/50ff6c065067545637110387/isPressed?access_token=7c3a17b73062e01cc52682cbf69a7941d17acb22&args=0", buff, "application/x-www-form-urlencoded");
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::exit(){
    spark->stopThread();
}

void ofApp::audioReceived(float *input, int bufferSize, int nChannels)
{
    
    printf("audio received =%i =%i\n", bufferSize, nChannels);
    
    if( startBufferSize != bufferSize ){
        ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", startBufferSize, bufferSize);
        return;
    }
    
    // samples are "interleaved"
    for (int i = 0; i < bufferSize; i++){
        buffer[i] = input[i];  
    }  


//    // samples are "interleaved"
//    for (int i = 0; i < bufferSize; i++){
//        right[i%256] = input[i*nChannels ] + input[i*nChannels +1] ;
//    }

    
    pitch_detect.processAudio(buffer, bufferSize);
    cout << pitch_detect.pitch;
    
}
void ofApp::audioOut( float *output, int bufferSize, int nChannels ){}

