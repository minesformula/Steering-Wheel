#ifndef NEXTION_H
#define NEXTION_H

void setWaterTemp(unsigned short value);

void setOilTemp(unsigned short value);

void setOilPressure(unsigned short value);

void setVoltage(float value);

void setRPM(unsigned short value);

void setGear(unsigned short value);

void setFuelPumpBool(bool value);

void setFanBool(bool value);

void setWaterPumpBool(bool value);

void setFuelPumpValue(bool value);

void setFanValue(bool value);

void setWaterPumpValue(bool value);

void setLambda(float value);

void setNeutral(bool value);

void switchToLoading();

void switchToStartUp();

void switchToDriver();

#endif //NEXTION_H 