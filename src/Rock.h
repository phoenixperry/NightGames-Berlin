//
//  Rock.h
//  http_example
//
//  Created by Phoenix Perry on 29/03/15.
//
//

#ifndef __http_example__Rock__
#define __http_example__Rock__
#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "Spark_core_manager.h"
class Rock{
public:
    
    Rock(Spark_core_manager *spark_); 
    
    Spark_core_manager *spark;
};

#endif /* defined(__http_example__Rock__) */
