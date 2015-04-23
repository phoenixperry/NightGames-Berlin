
/*******************************************************************************

 Bare Conductive Proximity MP3 player
 ------------------------------
 
 proximity_mp3.ino - proximity triggered MP3 playback
 
 Based on code by Jim Lindblom and plenty of inspiration from the Freescale 
 Semiconductor datasheets and application notes.
 
 Bare Conductive code written by Stefan Dzisiewski-Smith and Peter Krige.
 
 This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 
 Unported License (CC BY-SA 3.0) http://creativecommons.org/licenses/by-sa/3.0/
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*******************************************************************************/

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
#define NUM_LEDS 7  
// sd card instantiation
// SdFat sd;

// define LED_BUILTIN for older versions of Arduino
#ifndef LED_BUILTIN
#define LED_BUILTIN 13

#endif


//We can use any of these!!! 
//int leds[] = {0,1,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3,A4,A5}; // these are the pads you can use for digital output  
int leds[] = {A0,A1,A2,A3,A4,A5,0}; 

int startTime =0; 
int durration = 3000;  
bool on = false; 

void setup(){  
  startTime = millis();
  Serial.begin(57600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i =0; i <NUM_LEDS; i++) 
 {
    pinMode(i, OUTPUT); //set up pints 
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

  if(millis() > startTime + durration && on)
  {

    startTime = millis(); 
    on = false; 

  }
  readTouchInputs();
  for(int i=0; i<12; i++){
    MPR121.updateFilteredData(); 
    int d = MPR121.getFilteredData(i);

      if(i < 10){
        Serial.print(0);
        Serial.print(i);
        Serial.print(":");
        Serial.println(d);
      }else {
        Serial.print(i);
        Serial.print(":");
        Serial.println(d);
      }
    Serial.flush();  
    digitalWrite(leds[i], HIGH); 
  }  
}


void readTouchInputs(){

    
    MPR121.updateTouchData();

      for (int i=0; i < 12; i++){  // Check which electrodes were pressed
        if(MPR121.isNewTouch(i)){
        
            //pin i was just touched
            Serial.print("pin ");
            Serial.print(i); 
    
            Serial.println(" was just touched");
            digitalWrite(leds[i], HIGH); 
        }else{
          if(MPR121.isNewRelease(i)){
            Serial.print("pin ");
            Serial.print(i);
            Serial.println(" is no longer being touched");
            digitalWrite(LED_BUILTIN, LOW);
         } 
        }
      }
 
}













