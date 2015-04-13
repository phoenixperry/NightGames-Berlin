// This #include st// This #include statement was automatically added by the Spark IDE.
#include "neopixel.h"

#define PIXEL_TYPE WS2812B
#define PIXEL_PIN D5
#define PIXEL_COUNT 2

// pins
#define IR_LED_0 D2
#define IR_LED_1 D3
#define VIBE A0
#define ACCEL_X A1
#define ACCEL_Y A2
#define ACCEL_Z A3

int z_axis = 0, y_axis = 0, x_axis = 0;
int z_axis_prev = 0, y_axis_prev = 0, x_axis_prev = 0;

int motion = 0;
char* motion_string;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
    Spark.variable("motion", &motion_string, STRING);
    pinMode(IR_LED_0, OUTPUT);
    pinMode(IR_LED_1, OUTPUT);
    pinMode(VIBE, OUTPUT);
    pinMode(ACCEL_X, INPUT);
    pinMode(ACCEL_Y, INPUT);
    pinMode(ACCEL_Z, INPUT);
    strip.begin();
    strip.show();
}

// map 0 - 255 to color gradient
// going from blue -> cyan -> green -> yellow -> red -> white
int gradient(int a) {
    if (a < 42) {
        // blue
        return strip.Color(0, 0, 128 + (3 * a));
    } else if (a < 84) {
        // cyan
        return strip.Color(0, 6 * (a - 42), 255);
    } else if (a < 126) {
        // green
        return strip.Color(0, 255, 255 - (3 * (a - 84)));
    } else if (a < 168) {
        // yellow
        return strip.Color(6 * (a - 126), 255, 0);
    } else if (a < 200) {
        // red
        return strip.Color(255, 255 - (6 * (a - 168)), 0);
    } else {
        // white
        return strip.Color(255, 255, 4 * (a - 200));
    }
}

int accelToVibe(int a) {
    if (a > 200) return 255;
    if (a > 128) return 150;
    if (a > 64) return 84;
    return 0;
}

void loop() {
    int z_delta = 0, y_delta = 0, x_delta = 0;
    int m = 0;

    digitalWrite(IR_LED_0, HIGH);
    digitalWrite(IR_LED_1, HIGH);

    z_axis_prev = z_axis;
    z_axis = analogRead(ACCEL_Z);
    z_delta = abs(z_axis - z_axis_prev);

    y_axis_prev = y_axis;
    y_axis = analogRead(ACCEL_Y);
    y_delta = abs(y_axis - y_axis_prev);

    x_axis_prev = x_axis;
    x_axis = analogRead(ACCEL_X);
    x_delta = abs(x_axis - x_axis_prev);

    m = max(max(z_delta, y_delta), x_delta);
    analogWrite(VIBE, accelToVibe(m));
    for (int i = 0; i < PIXEL_COUNT; i++) {
        strip.setPixelColor(i, gradient(m));
    }
    strip.show();
    motion = m;
    sprintf (motion_string, "%d", m);
  

    delay(100);

}
