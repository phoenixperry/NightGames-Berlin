#include "ofApp.h"
#include "RtAudio.h"

//needed for thread
//
ofBuffer buff;
//ofBuffer *serialData;

float startTime, currentTime;
//--------------------------------------------------------------
void ofApp::setup(){
    spark_clouds = new Spark_core_manager();
    spark_rock = new Spark_core_manager();
    spark_clouds->startThread();
    spark_rock->startThread();
    spark_clouds->setup_url_and_data("50ff6c065067545637110387", "c8c4c3aa486fa8e15d8d1edeeff64ec9d878052a", "cloud", "test");
    spark_rock->setup_url_and_data("54ff6e066678574931580767", "c8c4c3aa486fa8e15d8d1edeeff64ec9d878052a", "rock", "z_axis");
     p = new pitchEstimator();
     p->setup();
    clouds = new Clouds(spark_clouds, p);
   //   port_reader.setup();
//    startTime = ofGetElapsedTimef();
    bSendSerialMessage = false;

    serial = new ofSerial();
    serial->listDevices();
    serial->setup(0, 9600);
}



//--------------------------------------------------------------
void ofApp::update(){
    
    //This gets sent to arduino, calling for a new set of readings
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
        //cout << sensorPadValue << endl;
        //This was allows for the whole process to repeat without
        // getting strange overlapping readings from the encoder:
        serial->flush();
    }
    p->update();
    clouds->update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    p->draw();
    clouds->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    spark_clouds->spark_function_name ="set_color";
    spark_clouds->spark_variable_name = "orange";
    spark_clouds->sendPostData = true;

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


