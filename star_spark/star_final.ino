// This #include statement was automatically added by the Spark IDE.
#include "neopixel.h"

#define PIXEL_PIN D0
#define PIXEL_PIN D2
#define PIXEL_COUNT 2
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int sensor0 = 0, sensor1 = 0, sensor2 = 0, sensor3 = 0;
char combined[20];


void setup() {
    // sensors
    Spark.variable("sensor0", &sensor0, INT);
    Spark.variable("sensor1", &sensor1, INT);
    Spark.variable("sensor2", &sensor2, INT);
    Spark.variable("sensor3", &sensor3, INT);
    Spark.variable("combined", &combined, STRING);


    Serial.begin(9600);
    pinMode(A3, INPUT);

    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(A6, INPUT);

    // pixels
    strip.begin();
    strip.show();
}

void loop() {
    int reading = 0;

    reading = analogRead(A3);
    sensor0 = reading;
    Serial.print(sensor0); 
    reading = analogRead(A4);
    sensor1 = reading;

    reading = analogRead(A5);
    sensor2 = reading;

    reading = analogRead(A6);
    sensor3 = reading;

    sprintf(combined, "%d,%d,%d,%d", sensor0, sensor1, sensor2, sensor3);

    rainbow(20);
}

// from neopixl sample code

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
