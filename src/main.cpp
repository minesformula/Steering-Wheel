#include "main.h"

void setup(void) {
  delay(400);
  Serial.begin(115200);

  NextionInterface::init();

  CanInterface::valid_signal();

  NextionInterface::switchToStartUp();


  

  while(true){}
  // Check For Can Data


}



void loop() {
  CanInterface::task();

}