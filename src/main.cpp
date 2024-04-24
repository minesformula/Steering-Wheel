#include "main.h"
#include "neopixel.h"

int const shiftUp = 2;
int const shiftDown = 3;

Adafruit_NeoPixel pixels(16, 2, NEO_GRB + NEO_KHZ800);

int rotaryPosition(int voltage){
  if(voltage > 980)
    return 0;
  if(voltage > 895)
    return 1;
  if(voltage > 809)
    return 2;
  if(voltage > 724)
    return 3;
  if(voltage > 639)
    return 4;
  if(voltage > 553)
    return 5;
  if(voltage > 468)
    return 6;
  if(voltage > 383)
    return 7;
  if(voltage > 297)
    return 8;
  if(voltage > 212)
    return 9;
  if(voltage > 127)
    return 10;
  if(voltage > 41)
    return 11;
  return 12;
}

void setup(void) {
  pinMode(shiftUp, INPUT_PULLUP);
  pinMode(shiftDown, INPUT_PULLUP);

  delay(400);
  Serial.begin(9600);

  Serial2.begin(115200);
  delay(200);
  Serial.println("Nextion Setup");
  
  Serial2.print("page1");
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(50); // Normal 150
  pixels.clear();
  pixels.show();

  delay(50);
}

bool shiftUpState = false;
bool shiftDownState = false;

void loop() {
  static const int lightRed = (255 << 16) | (20 << 8) | 0;
  static const int darkRed = (255 << 16) | (0 << 8) | 0;

  static const int lightGreen = (120 << 16) | (255 << 8) | 0;
  static const int darkGreen = (0 << 16) | (255 << 8) | 0;

  static const int lightBlue = (0 << 16) | (250 << 8) | 187;
  static const int darkBlue = (0 << 16) | (0 << 8) | 255;

  static const int purple = (255 << 16) | (0 << 8) | 255;

  /*DEMO CODE*/
  if(rotaryPosition(analogRead(A10)) < 3){
    Serial2.print("page page1");
    Serial2.write(0xFF);
    Serial2.write(0xFF);
    Serial2.write(0xFF);
  }
  else if(rotaryPosition(analogRead(A10)) < 6){
    Serial2.print("page page2");
    Serial2.write(0xFF);
    Serial2.write(0xFF);
    Serial2.write(0xFF);
  }
  else if(rotaryPosition(analogRead(A10)) < 9){
    Serial2.print("page page3");
    Serial2.write(0xFF);
    Serial2.write(0xFF);
    Serial2.write(0xFF);
  }
  else{
    Serial2.print("page page4");
    Serial2.write(0xFF);
    Serial2.write(0xFF);
    Serial2.write(0xFF);
  }


  if(rotaryPosition(analogRead(A11)) < 3){
    for(int x = 0; x < 16; x++)
      pixels.setPixelColor(x, purple);
    pixels.show();
  }
  else if(rotaryPosition(analogRead(A11)) < 6){
    for(int x = 0; x < 16; x++)
      pixels.setPixelColor(x, darkRed);
    pixels.show();
  }
  else if(rotaryPosition(analogRead(A11)) < 9){
    for(int x = 0; x < 16; x++)
      pixels.setPixelColor(x, darkBlue);
    pixels.show();
  }
  else{
    for(int x = 0; x < 16; x++)
      pixels.setPixelColor(x, darkGreen);
    pixels.show();
  }

  if(rotaryPosition(analogRead(A12)) < 3){
    pixels.setBrightness(10);
    pixels.show();
  }
  else if(rotaryPosition(analogRead(A12)) < 6){
    pixels.setBrightness(50);
    pixels.show();
  }
  else if(rotaryPosition(analogRead(A12)) < 9){
    pixels.setBrightness(100);
    pixels.show();
  }
  else {
    pixels.setBrightness(255);
    pixels.show();
  }
  


  /*Typical Can Interface*/
  // CanInterface::task();

  // if(digitalRead(shiftUp) == 0 && shiftUpState == false){
  //   Serial.println("Shift Up");
  //   CanInterface::send_shift(true, false);
  //   shiftUpState = true;
  // }
  // else if(digitalRead(shiftDown) == 0 && shiftDownState == false){
  //   Serial.println("Shift Down");
  //   CanInterface::send_shift(false, true);
  //   shiftDownState = true;
  // }
  // else if(digitalRead(shiftDown) == 1 && shiftDownState == true){
  //   CanInterface::send_shift(false, false);
  //   shiftDownState = false;
  // }
  // else if(digitalRead(shiftUp) == 1 && shiftUpState == true){
  //   CanInterface::send_shift(false, false);
  //   shiftUpState = false;
  // }
  Serial.print("R1: ");
  Serial.print(analogRead(A10));
  Serial.print(", R2: ");
  Serial.print(analogRead(A11));
  Serial.print(", R3: ");
  Serial.println(analogRead(A12));

  
  delay(250);
}