#ifndef NEXTION_H
#define NEXTION_H

#include <Arduino.h>

enum page
{
    LOADING,
    STARTUP,
    DRIVER
};

class NextionInterface
{
private:
    static short ctof(short celsius);

    static page current_page;

    static void sendNextionMessage(String message);

    static int const RGB565_GREEN = 1472;
    static int const RGB565_ORANGE = 47936;
    static int const RGB565_RED = 45056;
    static int const RGB565_BLACK = 0;

    static uint8_t waterTemp;
    static uint8_t oilTemp;
    static uint8_t oilPressure;
    static float batteryVoltage;
    static uint8_t engineRPM;
    static uint8_t lambda;
    static uint8_t gear;

public:
    NextionInterface();

    static void init();

    static void setWaterTemp(uint8_t value);

    static void setOilTemp(uint8_t value);

    static void setOilPressure(uint8_t value);

    static void setVoltage(float value);

    static void setRPM(uint8_t value);

    static void setGear(uint8_t value);

    static void setFuelPumpBool(bool value);

    static void setFanBool(bool value);

    static void setWaterPumpBool(bool value);

    static void setFuelPumpValue(bool value);

    static void setFanValue(bool value);

    static void setWaterPumpValue(bool value);

    static void setLambda(float value);

    static void setNeutral(bool value);

    static void switchToLoading();

    static void switchToStartUp();

    static void switchToDriver();

    static page getCurrentPage();
};

#endif // NEXTION_H