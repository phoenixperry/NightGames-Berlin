//
//  Clouds.cpp
//  http_example
//
//  Created by Phoenix Perry on 08/03/15.
//
//

#include "Clouds.h"
#include "Spark_core_manager.h"
Spark_core_manager *spark;
Clouds::Clouds(Spark_core_manager *spark_, pitchEstimator *p_){
    spark = spark_;
    p = p_;
}
void Clouds::update(){}
void Clouds::draw(){

}

void Clouds::triggerLed(string color)
{
    //spark->postData("set_color", color);
}