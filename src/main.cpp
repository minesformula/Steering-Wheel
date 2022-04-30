#include "main.h"

int const shiftUp = 2;
int const shiftDown = 3;

void setup(void) {
  pinMode(shiftUp, INPUT_PULLUP);
  pinMode(shiftDown, INPUT_PULLUP);
  

  delay(400);
  Serial.begin(115200);

  NextionInterface::init(); // Creates Serial Port to Display
  delay(100);

  Serial.println(CanInterface::init());

  if(CanInterface::init()){ // If CAN setup then go to startup
    NextionInterface::switchToStartUp();
  }
}

bool shiftUpState = false;
bool shiftDownState = false;

void loop() {
  CanInterface::task();

  if(digitalRead(shiftUp) == 0 && shiftUpState == false){
    Serial.println("Shift Up");
    CanInterface::send_shift(true, false);
    shiftUpState = true;
  }
  else if(digitalRead(shiftDown) == 0 && shiftDownState == false){
    Serial.println("Shift Down");
    CanInterface::send_shift(false, true);
    shiftDownState = true;
  }
  else if(digitalRead(shiftDown) == 1 && shiftDownState == true){
    CanInterface::send_shift(false, false);
    shiftDownState = false;
  }
  else if(digitalRead(shiftUp) == 1 && shiftUpState == true){
    CanInterface::send_shift(false, false);
    shiftUpState = false;
  }
  
  delay(10);
}