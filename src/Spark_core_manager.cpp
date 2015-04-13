//
//  Spark_core_manager.cpp
//  http_example
//
//  Created by Phoenix Perry on 04/03/15.
//
//

#include "Spark_core_manager.h"


Spark_core_manager::Spark_core_manager(){

}

void Spark_core_manager::setup_url_and_data(string device_id, string access_token, string device_name_, string spark_variable_name_, bool isString) {
    //this inits the object settings and also gets the url
    //set up for get requests with a variable from the core
    hasInited = true;
    device_name = device_name_;
    spark_variable_name = spark_variable_name_;
    std::string url_name1_("https://api.spark.io/v1/devices/");
    url_name1 += url_name1_+  device_id;
    url_name1 += "/";
    
    std::string url_name2_("?access_token=");
    url_name2 +=url_name2_+ access_token;
    action_url = url_name1+spark_variable_name + url_name2;
    
    cout << action_url << " is the action url" << endl;
    
    //this is a listener that fires a function everytime there's a new event here involving http
    if(isString){ofAddListener(httpUtils.newResponseEvent,this, &Spark_core_manager::newResponseString);}
        else {ofAddListener(httpUtils.newResponseEvent,this, &Spark_core_manager::newResponse);}
    
    //start up http stuffs
    httpUtils.start();
}
void Spark_core_manager::threadedFunction()
{
     while(isThreadRunning()) {
         if(hasInited){
             httpUtils.getUrl(action_url);
     
            if(sendPostData)
            {
                postData();
            }
        }
     }
}
void Spark_core_manager::newResponseString(ofxHttpResponse & response){
    responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
    //note that it can't tell the 2 different types of json objects apart from get and post so the get and post both make objects and both
    //save out to this result which is kinda annoying. this is why I did the if statements to get the name
    
    //print raw json data so you can see all the data. see the ofxjson exampl for more info here.
    //cout << responseStr;
    bool parse =result.parse(response.responseBody);
    if(parse)
    {
        
        result.getRawString();
        
        sensor_data = result["result"].asString();
        
        string var_name = result["name"].asString();
        
        if(device_name =="device_name"){
            //this is the function trigger from of to spark core and the return value from sparkcore.
            cout<< result["return_value"].asString() << " is returned data" << endl;
        }
        if( spark_variable_name ==var_name)
        {
            //this is sensor data
          //  cout<< result["result"].asString() << " is sensor data" << endl;
        }
    }else{
        cout << "json parse failure";
    }
}

void Spark_core_manager::newResponse(ofxHttpResponse & response){
    responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
    //note that it can't tell the 2 different types of json objects apart from get and post so the get and post both make objects and both
    //save out to this result which is kinda annoying. this is why I did the if statements to get the name
    
    //print raw json data so you can see all the data. see the ofxjson exampl for more info here.
     //cout << responseStr;
    bool parse =result.parse(response.responseBody);
    if(parse)
    {
        
        result.getRawString();
 
        sensor_data = result["result"].asInt();
 
        string var_name = result["name"].asString();
        
         if(device_name =="device_name"){
             //this is the function trigger from of to spark core and the return value from sparkcore.
             cout<< result["return_value"].asInt() << " is returned data" << endl;
        }
        if( spark_variable_name ==var_name)
        {
            //this is sensor data
            cout<< result["result"].asInt() << " is sensor data" << endl;
        }
    }else{
        cout << "json parse failure";
    }
}
    void Spark_core_manager::postData(){

        //to send new data make sure to set the new args first before calling this function or the old data will be sent.
        //completed URL should look like this:
        //httpUtils.postData("https://api.spark.io/v1/devices/50ff6c065067545637110387/" +spark_function_name + "?access_token=c8c4c3aa486fa8e15d8d1edeeff64ec9d878052a&args="+args, mybuff, "application/x-www-form-urlencoded");
        cout << spark_function_name <<  " called on spark" << endl;
        string args_ = "args="+args;
        string post_url_name = url_name1 + spark_function_name+url_name2;
        cout << post_url_name;
        mybuff.set(args_);
        
        httpUtils.postData(post_url_name, mybuff, "application/x-www-form-urlencoded");
        sendPostData = false;
}


