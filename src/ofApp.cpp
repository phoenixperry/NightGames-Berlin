#include "ofApp.h"
#include "ofEvents.h"
void ofApp::setup(){
    ofSetBackgroundColor(0, 0, 0);
    //hardware setup
   // spark_clouds = new Spark_core_manager();
   // spark_rock = new Spark_core_manager();
    //spark_clouds->startThread();
  //  spark_rock->startThread();
   // spark_clouds->setup_url_and_data("50ff6c065067545637110387", "12d6475ce64882db47631f249deb47d795186ea9", "cloud", "combined", true);
   // spark_rock->setup_url_and_data("54ff6e066678574931580767", "12d6475ce64882db47631f249deb47d795186ea9", "rock", "motion", true);
    // p = new pitchEstimator();
     //p->setup();
    // clouds = new Clouds(spark_clouds, p);

   // hut = new Hut();
   // rock = new Rock(spark_rock);
   // stars = new Stars(spark_clouds);
   // clouds = new Clouds(spark_clouds, p);
//    ofAddListener(ofEvents().keyReleased, hut, &Hut::keyReleased);
    //clouds->update_star_data(stars->holder);
    serial_reader = new SerialReader();
    serial_reader->setup();
    oscData = new OscData();
    tree = new Tree(serial_reader, oscData);
    oscData = new OscData();
}
void ofApp::update(){
    serial_reader->update(); 
    tree->update();
 //   hut->update();
  //   p->update();
    //stars->update();
   // tree->update(hut->treePads->at(0), hut->treePads->at(1));
    

  //  tree->update();
    //clouds->stars_average = stars->holder; //refractor holder to something sensable like stars average please! :)
    //clouds->update();
    //send star data to clouds
    
  //  ofSoundUpdate();
//    rock->update();

}
void ofApp::draw(){
  //  p->draw();
 //   hut->draw();
    
   // clouds->draw();
    
    //allows hut to calibrate first
//    if(hut->calibrateMode==false)
//    {
//        tree->draw();
//        cout << "calibrating tree ran";
//    }
}
void ofApp::keyReleased(int key){
//    spark_clouds->spark_function_name ="set_color";
//    spark_clouds->spark_variable_name = "orange";
//    spark_clouds->sendPostData = true;
    //if for some reason you want to trigger a function on the spark, from an object, this is how.
    //should? should be able to subclass but there might be thread issues if you do 
}
