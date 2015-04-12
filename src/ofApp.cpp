#include "ofApp.h"
#include "ofEvents.h"
void ofApp::setup(){
    //hardware setup
//    spark_clouds = new Spark_core_manager();
//    spark_rock = new Spark_core_manager();
//    spark_clouds->startThread();
//    spark_rock->startThread();
   // spark_clouds->setup_url_and_data("50ff6c065067545637110387", "12d6475ce64882db47631f249deb47d795186ea9", "cloud", "test");
    //spark_rock->setup_url_and_data("54ff6e066678574931580767", "12d6475ce64882db47631f249deb47d795186ea9", "rock", "z_axis");
     p = new pitchEstimator();
     p->setup();
   //  clouds = new Clouds(spark_clouds, p);

  //  cloud_sound_1.loadSound("sounds/clouds1.wav");
  //  cloud_sound_1.setVolume(0.75f);
  //  cloud_sound_1.setMultiPlay(true);
    hut = new Hut();
    rock = new Rock(); 
    stars = new Stars();


   // taps.resize(11);   
    ofAddListener(ofEvents().keyReleased, hut, &Hut::keyReleased);
  //  hutFilters = &hut->getUnits();
  //  output.setDevice("Komplete Audio 6");
    

//    OFXAU_PRINT(AudioUnitSetProperty(output,
//                                     kAudioUnitProperty_StreamFormat,
//                                     kAudioUnitScope_Input,
//                                     0,
//                                     &ASBD,
//                                     sizeof(ASBD)),
//                "setting output unit's input ASBD");
    
    // setting mixer to have 960 input busses, 1 output bus and use the
    // 16 channel stream format on its output bus
//    mixer.setChannelLayout(NUMBER_OF_FILE_PLAYERS, 1, NULL, &ASBD);

}
void ofApp::update(){
    hut->update();
     p->update();
 //   clouds->update();

    ofSoundUpdate();

}
void ofApp::draw(){
    p->draw();
    hut->draw();
    
  //  clouds->draw();
}
void ofApp::keyReleased(int key){
//    spark_clouds->spark_function_name ="set_color";
//    spark_clouds->spark_variable_name = "orange";
//    spark_clouds->sendPostData = true;

}
