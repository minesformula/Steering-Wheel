#include <Adafruit_NeoPixel.h>

#ifndef NEOPIXEL_H
#define NEOPIXEL_H

class RevLights{
private:
    static int LEDPINS;
    static int NUMPIXELS;

    static Adafruit_NeoPixel pixels;


    static const int lightRed = (255 << 16) | (20 << 8) | 0;
    static const int darkRed = (255 << 16) | (0 << 8) | 0;

    static const int lightGreen = (120 << 16) | (255 << 8) | 0;
    static const int darkGreen = (0 << 16) | (255 << 8) | 0;

    static const int lightBlue = (0 << 16) | (250 << 8) | 187;
    static const int darkBlue = (0 << 16) | (0 << 8) | 255;

    static const int blank = 0;

public:
    RevLights(){
        pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
        pixels.setBrightness(100); // Normal 150
        pixels.clear();
        pixels.show();

        rpmBased(6000);
    }

    void rpmBased(int rpm){
        if(rpm > 1000)
            for(int x = 0; x < 5; x++)
                pixels.setPixelColor(x, darkGreen);

        if(rpm > 2000)
            for(int x = 5; x < 11; x++)
                pixels.setPixelColor(x, darkRed);

        if(rpm > 3000)
            for(int x = 11; x < 16; x++)
                pixels.setPixelColor(x, darkBlue);

        if(rpm > 5000)
            for(int x = 0; x < 16; x++)
                pixels.setPixelColor(x, darkRed);

        pixels.show();
        delay(100);

    }
};

#endif //NEOPIXEL_H

/*
// LED globals
#define PIN 6    
#define NUMPIXELS 16
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t NONE = ((uint32_t)0 << 16) | ((uint32_t)0 <<  8) | 0;
uint32_t RED = ((uint32_t)255 << 16) | ((uint32_t)0 <<  8) | 0;
uint32_t GREEN = ((uint32_t)0 << 16) | ((uint32_t)255 <<  8) | 0;
uint32_t BLUE = ((uint32_t)0 << 16) | ((uint32_t)0 <<  8) | 255;
uint32_t YELLOW = ((uint32_t)255 << 16) | ((uint32_t)255 <<  8) | 0;
uint32_t ORANGE = ((uint32_t)255 << 16) | ((uint32_t)128 <<  8) | 0;
uint32_t LTBLUE = ((uint32_t)0 << 16) | ((uint32_t)255 <<  8) | 255;
*/