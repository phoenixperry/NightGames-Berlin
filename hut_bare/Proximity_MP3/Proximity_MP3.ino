

// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4


//We can use any of these!!! 
//int leds[] = {0,1,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3,A4,A5}; // these are the pads you can use for digital output  
int leds[] = {5,0,6,0,7,0,0,0}; 

int sensor1 = A4; 

int sensorData1, sensorData2, sensorData3, sensorData4 =0; 
void setup(){  
  Serial.begin(57600);
  
   // The EL channels are on pins 2 through 9
  // Initialize the pins as outputs
  
  pinMode(5, OUTPUT);  // channel D    
  pinMode(6, OUTPUT);  // channel E
  pinMode(7, OUTPUT);  // channel F
  
  pinMode(sensor1, INPUT);


  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);
 
  // this is the touch threshold - setting it low makes it more like a proximity trigger
  // default value is 40 for touch
  MPR121.setTouchThreshold(8);
  
  // this is the release threshold - must ALWAYS be smaller than the touch threshold
  // default value is 20 for touch
  MPR121.setReleaseThreshold(4);  

}
void lightSensor(){
  digitalWrite(sensor1, HIGH);
  sensorData1 = analogRead(sensor1);
  Serial.print(12); 
  Serial.print(":");
  Serial.println(sensorData1);

}  
void loop(){
  touchSensors(); 
  lightSensor(); 
}

void touchSensors()
{
 
   MPR121.updateTouchData();
    for(int i=0; i<12; i++){
  
    MPR121.updateFilteredData(); 
    int d = MPR121.getFilteredData(i);
      if(i < 10){
        Serial.print(0);
      }
        Serial.print(i);
        Serial.print(":");
        Serial.println(d);
        Serial.flush();  
      // chrome

    if(d < 700){
      digitalWrite(leds[i], HIGH);
    }
    else {
      digitalWrite(leds[i], LOW);
    }
  }
}
