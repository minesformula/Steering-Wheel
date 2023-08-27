#include <FlexCAN_T4.h>

#include "SDLogger.h"

SDLogger::SDLogger()
{
    createLog();
}

void SDLogger::createLog()
{
    char temp[255];
    int i = 0;

    sprintf(temp, "logFile0.txt");

    while (SD.exists(logFile))
    {
        i++;

        sprintf(temp, "logFile%d.txt", i);
    }

    logFile = temp;
}

void SDLogger::writeToLog(int title, char *input, const int length)
{
    File writeFile = SD.open(logFile, FILE_WRITE);
    writeFile.print(title + ": ");

    for (int i = 0; i < length; i++)
    {
        writeFile.print(input[i]);
    }

    writeFile.println();
    writeFile.close();
}

void SDLogger::writeToLog(const CAN_message_t &msg)
{
    File writeFile = SD.open(logFile, FILE_WRITE);

    writeFile.print(" ID: ");
    writeFile.print(msg.id, DEC);
    writeFile.print("  OVERRUN: ");
    writeFile.print(msg.flags.overrun);
    writeFile.print("  LEN: ");
    writeFile.print(msg.len);
    writeFile.print(" EXT: ");
    writeFile.print(msg.flags.extended);
    writeFile.print(" TS: ");
    writeFile.print(msg.timestamp);
    writeFile.print(" Buffer: ");
    for (uint8_t i = 0; i < msg.len; i++)
    {
        writeFile.print(msg.buf[i], DEC);
        writeFile.print(" ");
    }
    writeFile.println();
}

char *SDLogger::getFileName()
{
    return logFile;
}

uint8_t SDLogger::getNameLength()
{
    return nameLength;
}