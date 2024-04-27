#include "main.h"
#include "neopixel.h"

#include <IntervalTimer.h>

// Define the interval in microseconds (10 ms = 10000 microseconds)
const unsigned long interval = 10;
bool executeFlag = false;

int const shiftUp = 37;
int const shiftDown = 36;

// Timer callback function
void timerCallback() {
  // Set the flag to indicate it's time to execute the command
  executeFlag = true;
}

void setup(void)
{
  pinMode(shiftUp, INPUT_PULLUP);
  pinMode(shiftDown, INPUT_PULLUP);

  RevLights lights{};

  delay(400);
  Serial.begin(115200);

  NextionInterface::init(); // Creates Serial Port to Display

  CanInterface::init();

  // Initialize the IntervalTimer object
  IntervalTimer myTimer;
  
  // Attach the timer callback function
  myTimer.begin(timerCallback, interval);
}

bool shiftUpState = false;
bool shiftDownState = false;

void loop()
{
  CanInterface::task();

  if (digitalRead(shiftUp) == 0 && shiftUpState == false)
  {
    shiftUpState = true;
  }
  else if (digitalRead(shiftDown) == 0 && shiftDownState == false)
  {
    shiftDownState = true;
  }
  else if (digitalRead(shiftDown) == 1 && shiftDownState == true)
  {
    shiftDownState = false;
  }
  else if (digitalRead(shiftUp) == 1 && shiftUpState == true)
  {
    shiftUpState = false;
  }

  CanInterface::send_shift(shiftUpState, shiftDownState);
}