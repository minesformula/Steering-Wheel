#ifndef NEXTION_H
#define NEXTION_H

void setWaterTemp(unsigned short value);

void setOilTemp(unsigned short value);

void setOilPressure(unsigned short value);

void setVoltage(float value);

void setRPM(unsigned short value);

void setGear(unsigned short value);

void setFuelPump(bool value);

void setFan(bool value);

void setWaterPump(bool value);

void setLambda(unsigned short value);

void setNeutral(unsigned short value);

void switchToLoading();

void switchToStartUp();

void switchToDriver();

#endif //NEXTION_H 