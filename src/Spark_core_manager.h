//
//  Spark_core_manager.h
//  http_example
//
//  Created by Phoenix Perry on 04/03/15.
//
//

#ifndef __http_example__Spark_core_manager__
#define __http_example__Spark_core_manager__

#include <stdio.h>
#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxJSON.h"

#endif /* defined(__http_example__Spark_core_manager__) */
class Spark_core_manager: public ofThread{
public:

    string responseStr;
    string action_url;
    ofxHttpUtils httpUtils;
    
    ofxJSONElement result;

    Spark_core_manager();
    void newResponse(ofxHttpResponse & response);
    void update();
    void threadedFunction();
    void postData(string color, string spark_function_name, string args);
    int val; 
};