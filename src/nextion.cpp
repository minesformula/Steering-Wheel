#include "nextion.h"

page NextionInterface::current_page = page::LOADING;

uint8_t NextionInterface::waterTemp = 0;
uint8_t NextionInterface::oilTemp = 0;
uint16_t NextionInterface::oilPressure = 0;
float NextionInterface::batteryVoltage = 0;
uint16_t NextionInterface::engineRPM = 0;
uint8_t NextionInterface::lambda = 0;
uint8_t NextionInterface::gear = 0;

bool NextionInterface::neutral = false;

NextionInterface::NextionInterface() {}

void NextionInterface::init()
{
    Serial2.begin(115200);
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
    Serial2.print(message);
    Serial2.write(0xFF);
    Serial2.write(0xFF);
    Serial2.write(0xFF);
}

void NextionInterface::setWaterTemp(uint8_t value)
{
    if(value != waterTemp){
        waterTemp = value;

        String instruction = "watertempvalue.txt=\"" + String(ctof(value), DEC) + " " + char(176) + "F\"";
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setOilTemp(uint8_t value)
{
    if(value != oilTemp){
        oilTemp = value;

        String instruction = "oiltempvalue.txt=\"" + String(ctof(value), DEC) + " " + char(176) + "F\"";
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setOilPressure(uint8_t value, uint8_t value2)
{
    float oilPresTemp = (value2 | (value << 8)) * 0.1 * 0.145038;
    if(oilPresTemp != oilPressure){
        oilPressure = oilPresTemp;
        String instruction = "oilpressvalue.txt=\"" + String(oilPressure, DEC) + " PSI\"";
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setVoltage(float value)
{
    if(value != batteryVoltage){
        batteryVoltage = value;

        String instruction = "voltvalue.txt=\"" + String(value, 2) + " V\"";
        sendNextionMessage(instruction);
    }
}

void NextionInterface::setRPM(uint16_t value)
{
    if(value != engineRPM){
        engineRPM = value;

        String instruction = "rpm.txt=\"" + String(value, DEC) + "\"";
        sendNextionMessage(instruction);
    }   
}

void NextionInterface::setGear(const CAN_message_t &msg)
{
    uint16_t engine_output = msg.buf[7] | (msg.buf[6] << 8);
    uint16_t engine_input = msg.buf[5] | (msg.buf[4] << 8);
    float gearRatio = (float) engine_input / engine_output;

    if(gear != gearRatio){
        gear = gearRatio;

        String instruction = "";
        if(neutral){
            instruction = "gear.txt=\"N\"";
        } else if(5.5 < gearRatio && gearRatio < 5.9){
            instruction = "gear.txt=\"1\"";
        } else if(3.9 < gearRatio && gearRatio < 4.2){
            instruction = "gear.txt=\"2\"";
        } else if(3.4 < gearRatio && gearRatio < 3.6){
            instruction = "gear.txt=\"3\"";
        } else if(3.05 < gearRatio && gearRatio < 3.4){
            instruction = "gear.txt=\"4\"";
        } else if(2.75 < gearRatio && gearRatio < 3.05){
            instruction = "gear.txt=\"5\"";
        } else if(2.3 < gearRatio && gearRatio < 2.75){
            instruction = "gear.txt=\"6\"";
        } 

        sendNextionMessage(instruction);
    }   
}

void NextionInterface::setFuelPumpBool(bool value)
{
    // String instruction = "";

    // if (value)
    // {
    //     instruction = "fuelpumpbool.bco=" + String(RGB565_GREEN, DEC);
    //     sendNextionMessage(instruction);
    // }
    // else
    // {
    //     instruction = "fuelpumpbool.bco=" + String(RGB565_RED, DEC);
    //     sendNextionMessage(instruction);
    // }
}

void NextionInterface::setFanBool(bool value)
{
    // String instruction = "";

    // if (value)
    // {
    //     instruction = "fanbool.bco=" + String(RGB565_GREEN, DEC);
    //     sendNextionMessage(instruction);
    // }
    // else
    // {
    //     instruction = "fanbool.bco=" + String(RGB565_RED, DEC);
    //     sendNextionMessage(instruction);
    // }
}

void NextionInterface::setWaterPumpBool(bool value)
{
    // String instruction = "";

    // if (value)
    // {
    //     instruction = "waterpumpbool.bco=" + String(RGB565_GREEN, DEC);
    //     sendNextionMessage(instruction);
    // }
    // else
    // {
    //     instruction = "waterpumpbool.bco=" + String(RGB565_RED, DEC);
    //     sendNextionMessage(instruction);
    // }
}

void NextionInterface::setFuelPumpValue(bool value)
{
    // String instruction = "";

    // if (value)
    // {
    //     instruction = "fuelpumpvalue.bco=" + String(RGB565_GREEN, DEC);
    //     sendNextionMessage(instruction);

    //     instruction = "fuelpumpvalue.txt=\"ON\"";
    //     sendNextionMessage(instruction);
    // }
    // else
    // {
    //     instruction = "fuelpumpvalue.bco=" + String(RGB565_RED, DEC);
    //     sendNextionMessage(instruction);

    //     instruction = "fuelpumpvalue.txt=\"OFF\"";
    //     sendNextionMessage(instruction);
    // }
}

void NextionInterface::setFanValue(bool value)
{
    // String instruction = "";

    // if (value)
    // {
    //     instruction = "fanvalue.bco=" + String(RGB565_GREEN, DEC);
    //     sendNextionMessage(instruction);

    //     instruction = "fanvalue.txt=\"ON\"";
    //     sendNextionMessage(instruction);
    // }
    // else
    // {
    //     instruction = "fanvalue.bco=" + String(RGB565_RED, DEC);
    //     sendNextionMessage(instruction);

    //     instruction = "fanvalue.txt=\"OFF\"";
    //     sendNextionMessage(instruction);
    // }
}

void NextionInterface::setWaterPumpValue(bool value)
{
    // String instruction = "";

    // if (value)
    // {
    //     instruction = "waterpumpvalue.bco=" + String(RGB565_GREEN, DEC);
    //     sendNextionMessage(instruction);

    //     instruction = "waterpumpvalue.txt=\"ON\"";
    //     sendNextionMessage(instruction);
    // }
    // else
    // {
    //     instruction = "waterpumpvalue.bco=" + String(RGB565_RED, DEC);
    //     sendNextionMessage(instruction);

    //     instruction = "waterpumpvalue.txt=\"OFF\"";
    //     sendNextionMessage(instruction);
    // }
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
    if(value != neutral){
        neutral = value;
        if(value)
            sendNextionMessage("gear.txt=\"N\"");
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