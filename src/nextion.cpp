#include "nextion.h"
#include <Arduino.h>

int const RGB565_GREEN = 1472;
int const RGB565_ORANGE = 47936;
int const RGB565_RED = 45056;
int const RGB565_BLACK = 0;

void sendNextionMessage(String message){
  Serial1.print(message);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
}

void setWaterTemp(unsigned short value){
    unsigned short max = 200;
    unsigned short high = 180;
    unsigned short low = 60;
    unsigned short min = 40;

    String instruction = "watertempvalue.txt=\"" + String(value, DEC) + " " + char(176) + "F\"";
    sendNextionMessage(instruction);

    if(value > max || value < min){
        instruction = "watertempvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
    else if(value > high || value < low){
        instruction = "watertempvalue.bco=" + String(RGB565_ORANGE, DEC);
        sendNextionMessage(instruction);
    }
    else{
        instruction = "watertempvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
}

void setOilTemp(unsigned short value){
    unsigned short max = 200;
    unsigned short high = 180;
    unsigned short low = 60;
    unsigned short min = 40;

    String instruction = "oiltempvalue.txt=\"" + String(value, DEC) + " " + char(176) + "F\"";
    sendNextionMessage(instruction);

    if(value > max || value < min){
        instruction = "oiltempvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
    else if(value > high || value < low){
        instruction = "oiltempvalue.bco=" + String(RGB565_ORANGE, DEC);
        sendNextionMessage(instruction);
    }
    else{
        instruction = "oiltempvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
}

void setOilPressure(unsigned short value){
    
}

void setVoltage(float value){
    float max = 15.0;
    float high = 14.0;
    float low = 12.5;
    float min = 12.0;

    String instruction = "voltvalue.txt=\"" + String(value, DEC) + " V\"";
    sendNextionMessage(instruction);

    if(value > max || value < min){
        instruction = "voltvalue.bco=" + String(RGB565_RED, DEC);
        sendNextionMessage(instruction);
    }
    else if(value > high || value < low){
        instruction = "voltvalue.bco=" + String(RGB565_ORANGE, DEC);
        sendNextionMessage(instruction);
    }
    else{
        instruction = "voltvalue.bco=" + String(RGB565_GREEN, DEC);
        sendNextionMessage(instruction);
    }
}

void setRPM(unsigned short value){
    
}

void setGear(unsigned short value){
    
}

void setFuelPump(bool value){
    
}

void setFan(bool value){
    
}

void setWaterPump(bool value){
    
}

void setLambda(unsigned short value){
    
}

void setNeutral(unsigned short value){
    
}

void switchToLoading(){
    sendNextionMessage("page loading");
}

void switchToStartUp(){
    sendNextionMessage("page startup");
}

void switchToDriver(){
    sendNextionMessage("page driver");
}