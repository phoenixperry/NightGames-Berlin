//
//  Spark_core_manager.cpp
//  http_example
//
//  Created by Phoenix Perry on 04/03/15.
//
//

#include "Spark_core_manager.h"
//you need a data buffer to write data from spark into
ofBuffer mybuff;

Spark_core_manager::Spark_core_manager(void){
    //setup your URL - this is gonna change and see the spark sdk for this bit. Everyone's will be different
    //and depending on your own device ID.
    action_url = "https://api.spark.io/v1/devices/50ff6c065067545637110387/val?access_token=7c3a17b73062e01cc52682cbf69a7941d17acb22";
    
    //this is a listener that fires a function everytime there's a new even here involving http
    ofAddListener(httpUtils.newResponseEvent,this,&Spark_core_manager::newResponse);
    
    //start up http stuffs
    httpUtils.start();
    
}



void Spark_core_manager::threadedFunction()
{ 
    while(isThreadRunning()) {
      
     httpUtils.getUrl("https://api.spark.io/v1/devices/50ff6c065067545637110387/val?access_token=c8c4c3aa486fa8e15d8d1edeeff64ec9d878052a");
    }
}
void Spark_core_manager::newResponse(ofxHttpResponse & response){
    responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
    //note that it can't tell the 2 different types of json objects apart from get and post so the get and post both make objects and both
    //save out to this result which is kinda annoying. this is why I did the if statements to get the name
    
    //print raw json data so you can see all the data. see the ofxjson exampl for more info here.
    // cout << responseStr;
    bool parse =result.parse(response.responseBody);
    if(parse)
    {
        
        result.getRawString();
        lock();
        val = result["result"].asInt();
        unlock(); 
        string name = result["name"].asString();
        
        if(name =="val"){
            //this is sensor data
            cout << val << " is sensor data" << endl;
        }
        if(name =="archimedes")
        {
            //this is the function trigger from of to spark core and the return value from sparkcore.
            cout<< result["return_value"].asInt() << " is returned data" << endl;
        }
    }else{
        cout << "json parse failure";
    }
}
    void Spark_core_manager::postData(string color, string spark_function_name, string args){
        
        if(spark_function_name=="triggerRed")
        {
            
           // if("red"){
                httpUtils.postData("https://api.spark.io/v1/devices/50ff6c065067545637110387/" +spark_function_name + "?access_token=7c3a17b73062e01cc52682cbf69a7941d17acb22&args="+args, mybuff, "application/x-www-form-urlencoded");
           // }
            
            
        }
       
        
    }
