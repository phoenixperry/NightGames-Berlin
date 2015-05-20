

// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4



// touch behaviour definitions
#define firstPin 0
#define lastPin 11
#define NUM_LEDS 9  
// sd card instantiation
// SdFat sd;

// define LED_BUILTIN for older versions of Arduino
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif


//We can use any of these!!! 
//int leds[] = {0,1,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3,A4,A5}; // these are the pads you can use for digital output  
int leds[] = {1,1,1,5,6,7,1,1}; 
int on[] = {0,0,0,0,0,0,0,0,0,0,0,0};

void setup(){  
  Serial.begin(57600);
  
   // The EL channels are on pins 2 through 9
  // Initialize the pins as outputs
  
  pinMode(5, OUTPUT);  // channel D    
  pinMode(6, OUTPUT);  // channel E
  pinMode(7, OUTPUT);  // channel F
  for(int i =2; i <=9; i++) 
 {
    digitalWrite(i,LOW);
 } 

  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  
  // this is the touch threshold - setting it low makes it more like a proximity trigger
  // default value is 40 for touch
  MPR121.setTouchThreshold(8);

  
  // this is the release threshold - must ALWAYS be smaller than the touch threshold
  // default value is 20 for touch
  MPR121.setReleaseThreshold(4);  

}
void loop(){

  readTouchInputs();
  writeSerialData(); 


}
void readTouchInputs(){

    
   //if(MPR121.touchStatusChanged()){
    MPR121.updateTouchData();
    for(int i=0; i<lastPin; i++){
      if(MPR121.isNewTouch(i)){
        Serial.print("electrode ");
        Serial.print(i, DEC);
        Serial.println(" was just touched"); 
        on[i] = 1; 
      } else if(MPR121.isNewRelease(i)){
        Serial.print("electrode ");
        Serial.print(i, DEC);
        Serial.println(" was just released"); 
        on[i] = 0;  
      }
    
      if(on[i]==1){
         digitalWrite(leds[i], HIGH);
        }
        else {digitalWrite(leds[i], LOW);}
    
    }
  //}
}
 
void writeSerialData()
{

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
    if(d < 700)
    {
      digitalWrite(leds[i], HIGH);

    }

  }

}
