//
//  Spark_core_manager.h
//  http_example
//
//  Created by Phoenix Perry on 04/03/15.
//
//
#pragma once
#ifndef __http_example__Spark_core_manager__
#define __http_example__Spark_core_manager__

#endif /* defined(__http_example__Spark_core_manager__) */
#include <stdio.h>
#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxJSON.h"

using namespace std;

class Spark_core_manager:public ofThread{
public:
    string device_name;
    //name spark saves your device as
    
    string sensor_data;
    //used for incoming sensor data in the get request
    
    string responseStr;
    //what the spark spits back
    
    string action_url;
    //the spark url for post requests
    
    //strings for URL construction
    std::string  url_name1;
    std::string  url_name2;
    
    string args;
    //must be set to send data to spark. change this var to send different data when the post request is called
    string spark_function_name="set_leds";
    string spark_variable_name="test";
    
    bool sendPostData= false;
    //switch for the update loop to send data to spark
    bool hasInited = false;
    //is object is set up for get requests
    
    ofxHttpUtils httpUtils;
    ofxJSONElement result;
    //you need a data buffer to write data from spark into
    ofBuffer mybuff;

    Spark_core_manager();
    void update();
    void postData();
    void threadedFunction();
    void quit();
    void newResponse(ofxHttpResponse & response);
    
    void setup_url_and_data(string device_id, string access_token, string device_name_, string spark_variable_name_);
};