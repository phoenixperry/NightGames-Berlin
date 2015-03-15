// /*
//  * This is a minimal example, see extra-examples.cpp for a version
//  * with more explantory documentation, example routines, how to
//  * hook up your pixels and all of the pixel types that are supported.
//  *
//  */
//
// #include "application.h"
// //#include "spark_disable_wlan.h" // For faster local debugging only
// #include "neopixel.h"
//
// // IMPORTANT: Set pixel COUNT, PIN and TYPE
// #define PIXEL_PIN D2
// #define PIXEL_COUNT 2
// #define PIXEL_TYPE WS2812B
//
// Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
//
// //currntly displaying color
// uint32_t r= 255;
// uint32_t g= 255;
// uint32_t b= 255;
//
// //variables for fading colors
// uint32_t current_r = 255;
// uint32_t current_g=255;
// uint32_t current_b =255;
//
// uint32_t target_r = 255;
// uint32_t target_b = 255;
// uint32_t target_g =255;
//
// uint32_t col =255; //current color - this will get refactored later.
//
// //start fade at 0%
// float pct = 0;
//
// bool change = 0;
//
// int set_color(String command){
//   if(command == "light_blue"){target_r=0; target_g=0; target_b=255;}
//      else if(command == "teal"){target_r=0; target_g=155; target_b=100;}
//      else if(command=="pink"){target_r=200; target_g=0; target_b=10;}
//      else if(command=="grey"){target_r=255; target_g=0; target_b=0;}
//      else if(command=="orange"){target_r=255; target_g=255; target_b=0;}
//      else if(command=="yellow"){target_r=25; target_g=200; target_b=40;}
//      else if(command=="cream"){target_r=10; target_g=30; target_b=40;}
//      //violet is last!
//      else if (command=="purple"){ target_r=255; target_g=0; target_b=255;}
//      change = 1;
//
//     return 0;
// }
// //fucntions for calling from OF
//
// void set_leds(){
//     //for as long as we have pixels
//       //if we are going to trigger the fade
//       if(change ==1){
//         //for each pixel in the strip
//
//                       col = strip.Color(target_r, target_g, target_b);
//                       change = 0;
//                   }
//
//
//
//             else {
//             //there is no change so just show the current color
//               for(int16_t i=0; i<strip.numPixels(); i++)
//               {
//                   strip.setPixelColor(i, col);
//                   strip.show();
//                   delay(20);
//               }
//
//           }
//
// }
//
// void setup()
// {
//     //ultimately I'll have an exposed function for each color to change the active color. right now only this one is stubbed in.
//     Spark.function("set_color", set_color);
//
//     //code required to start the strip up
//     strip.begin();
//     strip.show();
//
//   //   // Make sure your //serial Terminal app is closed before powering your Core
//   //   Serial.begin(9600);
//   // //  Now open your //serial Terminal, and hit any key to continue!
//   //   while(!Serial.available()) SPARK_WLAN_Loop();
// }
// void loop()
// {
//     set_leds();
// //    Serial.println(current_r);
// }
/*
 * This is a minimal example, see extra-examples.cpp for a version
 * with more explantory documentation, example routines, how to
 * hook up your pixels and all of the pixel types that are supported.
 *
 */

#include "application.h"
//#include "spark_disable_wlan.h" // For faster local debugging only
#include "neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 2
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

//currntly displaying color
uint32_t r= 255;
uint32_t g= 255;
uint32_t b= 255;

//variables for fading colors
uint32_t current_r = 255;
uint32_t current_g=255;
uint32_t current_b =255;

uint32_t target_r = 255;
uint32_t target_b = 255;
uint32_t target_g =255;

uint32_t col =255; //current color

//start fade at 0%
float pct = 0;

//var for switching
bool change = 0;

//function to set the target color and trigger the color fade
int set_color(String command){
  //get the right color set as target
  if(command == "light_blue"){target_r=0; target_g=0; target_b=255;}
     else if(command == "teal"){target_r=0; target_g=255; target_b=100;}
     else if(command=="pink"){target_r=150; target_g=10; target_b=10;}
     else if(command=="grey"){target_r=10; target_g=10; target_b=0;}
     else if(command=="orange"){target_r=0; target_g=200; target_b=0;}
     else if(command=="yellow"){target_r=25; target_g=200; target_b=0;}
     else if(command=="cream"){target_r=255; target_g=255; target_b=255;}
     //violet is last!
     else if (command=="purple"){ target_r=255; target_g=0; target_b=255;}
     //flip the change switch
     change = 1;
    return 0;
}
void set_leds(){
      //if we are going to trigger the fade
      if(change ==1){
        //for each value in 256

                  for(int16_t i=0; i<256; i++)
                  {
                      //divide by 255 to get closer and closer to 1 and transition color values from current to target
                      pct = i/255.0F;
                      //fade from old color to new
                      r = (1-pct) * current_r + (pct) * target_r;
                      g = (1-pct) * current_g + (pct) * target_g;
                      b = (1-pct) * current_b + (pct) * target_b;
                      //transition the actual pixels
                      col = strip.Color(r,g,b);

                      for(uint16_t j=0; j<strip.numPixels(); j++) {
                        strip.setPixelColor(j, col);
                      }
                      strip.show();
                      delay(30);
                  }
                  //make sure the color we set the current color when we are done fading in
                  current_r = r;
                  current_g = b;
                  current_b = b;

                  //turn off the swtich because we are now done with both for loops.
                  change = 0;
              }


            else {
            //there is no change just show the current color
              for(int16_t i=0; i<strip.numPixels(); i++)
              {
                  col = strip.Color(r,g,b);
                  strip.setPixelColor(i, col);
              }
              strip.show();
              delay(20);

          }

}

void setup()
{
    //ultimately I'll have an exposed function for each color to change the active color. right now only this one is stubbed in.
    Spark.function("set_color", set_color);

    //code required to start the strip up
    strip.begin();
    strip.show();

    // Make sure your //serial Terminal app is closed before powering your Core
    //Serial.begin(9600);
  //  Now open your //serial Terminal, and hit any key to continue!
  //  while(!Serial.available()) SPARK_WLAN_Loop();
}
void loop()
{
    set_leds();
  //  Serial.println(current_r);
}
