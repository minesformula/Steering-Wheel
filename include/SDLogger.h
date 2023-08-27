#ifndef SDLOGGING_H
#define SDLOGGING_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <stdio.h>
#include <FlexCAN_T4.h>

class SDLogger
{
public:
    SDLogger();

    void createLog();

    void writeToLog(int title, char *input, const int length);
    void writeToLog(const CAN_message_t &msg);

    char *getFileName();
    uint8_t getNameLength();

private:
    char* logFile;
    uint8_t nameLength;
};

#endif