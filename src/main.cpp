#include "main.h"

SteeringWheel* wheelptr;

void setup(void)
{
  wheelptr = new SteeringWheel();
}

bool shiftUpState = false;
bool shiftDownState = false;

void loop()
{
  wheelptr->update();

  delay(1);
}