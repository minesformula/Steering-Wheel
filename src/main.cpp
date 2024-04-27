#include "main.h"
#include "neopixel.h"

int const shiftUp = 37;
int const shiftDown = 36;

void setup(void)
{
  pinMode(shiftUp, INPUT_PULLUP);
  pinMode(shiftDown, INPUT_PULLUP);

  RevLights lights{};

  delay(400);
  Serial.begin(115200);

  NextionInterface::init(); // Creates Serial Port to Display

  CanInterface::init();
}

bool shiftUpState = false;
bool shiftDownState = false;

void loop()
{
  CanInterface::task();

  if (digitalRead(shiftUp) == 0 && shiftUpState == false)
  {
    Serial.println("Shift Up");
    CanInterface::send_shift(true, false);
    shiftUpState = true;
  }
  else if (digitalRead(shiftDown) == 0 && shiftDownState == false)
  {
    Serial.println("Shift Down");
    CanInterface::send_shift(false, true);
    shiftDownState = true;
  }
  else if (digitalRead(shiftDown) == 1 && shiftDownState == true)
  {
    CanInterface::send_shift(false, false);
    shiftDownState = false;
  }
  else if (digitalRead(shiftUp) == 1 && shiftUpState == true)
  {
    CanInterface::send_shift(false, false);
    shiftUpState = false;
  }

  delay(1);
}