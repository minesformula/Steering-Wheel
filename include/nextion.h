#ifndef NEXTION_H
#define NEXTION_H

#include <Arduino.h>

enum page { LOADING, STARTUP, DRIVER};

class NextionInterface{
private:
    static short ctof(short celsius);

    static page current_page;

    static void sendNextionMessage(String message);

    static int const RGB565_GREEN = 1472;
    static int const RGB565_ORANGE = 47936;
    static int const RGB565_RED = 45056;
    static int const RGB565_BLACK = 0;
public:
    NextionInterface();

    static void init();

    static void setWaterTemp(unsigned short value);

    static void setOilTemp(unsigned short value);

    static void setOilPressure(unsigned short value);

    static void setVoltage(float value);

    static void setRPM(unsigned short value);

    static void setGear(unsigned short value);

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

#endif //NEXTION_H 