#include "ofApp.h"

void ofApp::setup(){
    spark_clouds = new Spark_core_manager();
    spark_rock = new Spark_core_manager();
    spark_clouds->startThread();
    spark_rock->startThread();
    spark_clouds->setup_url_and_data("50ff6c065067545637110387", "12d6475ce64882db47631f249deb47d795186ea9", "cloud", "test");
    spark_rock->setup_url_and_data("54ff6e066678574931580767", "12d6475ce64882db47631f249deb47d795186ea9", "rock", "z_axis");
     p = new pitchEstimator();
     p->setup();
    clouds = new Clouds(spark_clouds, p);
    serial = new SerialReader();
    serial->setup();
}
void ofApp::update(){

    p->update();
    clouds->update();
    serial->update();
}
void ofApp::draw(){
    p->draw();
    clouds->draw();
}
void ofApp::keyReleased(int key){
//    spark_clouds->spark_function_name ="set_color";
//    spark_clouds->spark_variable_name = "orange";
//    spark_clouds->sendPostData = true;

}
