#include <Arduino.h>
#include <tinyNeoPixel.h>

#define PIN         10
#define NUMPIXELS   10

tinyNeoPixel pixels = tinyNeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; 

void setup() {
    pixels.begin();
}

void loop() {

    for(int i=0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(0,150,0));
        pixels.show();
        delay(delayval); // Delay for a period of time (in milliseconds).
    }
    
    for(int i=(NUMPIXELS-1);i>=0;i--){
        pixels.setPixelColor(i, pixels.Color(150,0,0));
        pixels.show();
        delay(delayval); // Delay for a period of time (in milliseconds).
    }
}
