#include <Adafruit_NeoPixel.h>

#ifndef NEOPIXEL_H
#define NEOPIXEL_H

class RevLights
{
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
    RevLights()
    {
        init();
    }

    void static init()
    {
        pixels.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
        pixels.setBrightness(75); // Normal 150
        pixels.clear();
        pixels.show();

        delay(50);
        rpmBased(0);
    }

    void static rpmBased(int rpm)
    {
        if (rpm < 8000)
            for (int x = 0; x < 16; x++)
                pixels.setPixelColor(x, blank);

        else
        {
            if (rpm > 8000)
                for (int x = 0; x < 5; x++)
                    pixels.setPixelColor(x, darkGreen);

            if (rpm > 9000)
                for (int x = 5; x < 11; x++)
                    pixels.setPixelColor(x, darkRed);

            if (rpm > 10500)
                for (int x = 11; x < 16; x++)
                    pixels.setPixelColor(x, darkBlue);

            if (rpm > 12000)
                for (int x = 0; x < 16; x++)
                    pixels.setPixelColor(x, darkRed);
        }

        pixels.show();
    }
};

#endif // NEOPIXEL_H