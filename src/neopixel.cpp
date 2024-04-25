#include "neopixel.h"

int RevLights::LEDPINS = 4;
int RevLights::NUMPIXELS = 16;

Adafruit_NeoPixel RevLights::pixels(NUMPIXELS, LEDPINS, NEO_GRB + NEO_KHZ400);