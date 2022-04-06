#include <Arduino.h>
#include <nextion.h>

int const RGB565_GREEN = 1472;

void setup() {
  Serial1.begin(115200);
  delay(2000);
  switchToStartUp();
  delay(500);
  
}

void loop() {
  delay(1000);
  setWaterTemp(random()%210);
  setOilTemp(random()%210);
  setVoltage(random()%4 + 10);
}