#include "nextion.h"

page NextionInterface::current_page = page::LOADING;

NextionInterface::NextionInterface() {}

void NextionInterface::init()
{
    Serial1.begin(115200);
    delay(200);
    Serial.println("Nextion Setup");
    switchToLoading();
}

short NextionInterface::ctof(short celsius)
{
    return (celsius * 9 / 5) + 32;
}

void NextionInterface::sendNextionMessage(String message)
{
    Serial1.print(message);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
}

void NextionInterface::setWaterTemp(uint16_t value)
{
    value = ctof(value);

    uint16_t max = 200;
    uint16_t high = 180;
    uint16_t low = 40;
    uint16_t min = 32;

    String instruction = "watertempvalue.txt=\"" + String(value, DEC) + " " + char(176) + "F\"";
    sendNextionMessage(instruction);

    if (value > max || value < min)
    {
        instruction = "watertempvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
    else if (value > high || value < low)
    {
        instruction = "watertempvalue.bco=" + String(RGB565_ORANGE, DEC);
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "watertempvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setOilTemp(uint16_t value)
{
    uint16_t max = 200;
    uint16_t high = 180;
    uint16_t low = 60;
    uint16_t min = 40;

    String instruction = "oiltempvalue.txt=\"" + String(ctof(value), DEC) + " " + char(176) + "F\"";
    sendNextionMessage(instruction);

    if (value > max || value < min)
    {
        instruction = "oiltempvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
    else if (value > high || value < low)
    {
        instruction = "oiltempvalue.bco=" + String(RGB565_ORANGE, DEC);
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "oiltempvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setOilPressure(uint16_t value)
{
    uint16_t max = 80;
    uint16_t high = 70;
    uint16_t low = 50;
    uint16_t min = 40;

    String instruction = "oilpressvalue.txt=\"" + String(value, DEC) + " PSI\"";
    sendNextionMessage(instruction);

    if (value > max || value < min)
    {
        instruction = "oilpressvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
    else if (value > high || value < low)
    {
        instruction = "oilpressvalue.bco=" + String(RGB565_ORANGE, DEC);
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "oilpressvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setVoltage(float value)
{
    float max = 15.0;
    float high = 14.0;
    float low = 12.5;
    float min = 12.0;

    String instruction = "voltvalue.txt=\"" + String(value, 2) + " V\"";
    sendNextionMessage(instruction);

    if (value > max || value < min)
    {
        instruction = "voltvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
    else if (value > high || value < low)
    {
        instruction = "voltvalue.bco=" + String(RGB565_ORANGE, DEC);
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "voltvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setRPM(uint16_t value)
{
    String instruction = "rpm.txt=\"" + String(value, DEC) + "\"";
    sendNextionMessage(instruction);
}

void NextionInterface::setGear(uint16_t value)
{
    String instruction = "";
    if (value == 0)
    {
        instruction = "gear.txt=\"N\"";
    }
    else
    {
        instruction = "gear.txt=\"" + String(value, DEC) + "\"";
    }
    sendNextionMessage(instruction);
}

void NextionInterface::setFuelPumpBool(bool value)
{
    String instruction = "";

    if (value)
    {
        instruction = "fuelpumpbool.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "fuelpumpbool.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setFanBool(bool value)
{
    String instruction = "";

    if (value)
    {
        instruction = "fanbool.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "fanbool.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setWaterPumpBool(bool value)
{
    String instruction = "";

    if (value)
    {
        instruction = "waterpumpbool.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "waterpumpbool.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setFuelPumpValue(bool value)
{
    String instruction = "";

    if (value)
    {
        instruction = "fuelpumpvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);

        instruction = "fuelpumpvalue.txt=\"ON\"";
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "fuelpumpvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);

        instruction = "fuelpumpvalue.txt=\"OFF\"";
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setFanValue(bool value)
{
    String instruction = "";

    if (value)
    {
        instruction = "fanvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);

        instruction = "fanvalue.txt=\"ON\"";
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "fanvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);

        instruction = "fanvalue.txt=\"OFF\"";
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setWaterPumpValue(bool value)
{
    String instruction = "";

    if (value)
    {
        instruction = "waterpumpvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);

        instruction = "waterpumpvalue.txt=\"ON\"";
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "waterpumpvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);

        instruction = "waterpumpvalue.txt=\"OFF\"";
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setLambda(float value)
{
    float max = 1.5;
    float high = 1.2;
    float low = 0.8;
    float min = 0.5;

    String instruction = "lambdavalue.txt=\"" + String(value, 2) + " V\"";
    sendNextionMessage(instruction);

    if (value > max || value < min)
    {
        instruction = "lambdavalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
    else if (value > high || value < low)
    {
        instruction = "lambdavalue.bco=" + String(RGB565_ORANGE, DEC);
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "lambdavalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setNeutral(bool value)
{
    String instruction = "";

    if (value)
    {
        instruction = "neutralvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);

        instruction = "neutralvalue.txt=\"ON\"";
        sendNextionMessage(instruction);
    }
    else
    {
        instruction = "neutralvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);

        instruction = "neutralvalue.txt=\"OFF\"";
        sendNextionMessage(instruction);
    }
}

void NextionInterface::switchToLoading()
{
    sendNextionMessage("page page1");
    current_page = page::LOADING;
}

void NextionInterface::switchToStartUp()
{
    sendNextionMessage("page page2");
    current_page = page::STARTUP;
}

void NextionInterface::switchToDriver()
{
    sendNextionMessage("page page3");
    current_page = page::DRIVER;
}

page NextionInterface::getCurrentPage()
{
    return current_page;
}