#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H 

#include <Arduino.h>
//pin 18
volatile unsigned char* my_DDRE  = (unsigned char*)0x2D;
volatile unsigned char* my_PORTE = (unsigned char*)0x2E; 

#define BUTTON_BIT 5

volatile bool buttonEvent = false;
static unsigned long inputWait = 0;
void buttonISR() {
  if (millis() < inputWait){
    return;
  }
  buttonEvent = true;
}
void buttonInit() {
  *my_DDRE &= ~(1 << BUTTON_BIT);
  *my_PORTE |= (1 << BUTTON_BIT);
  
  inputWait = millis() + 300;
  buttonEvent = false;
  attachInterrupt(digitalPinToInterrupt(18), buttonISR, FALLING);
  buttonEvent = false;
}

bool buttonPressedEvent() {
  if (buttonEvent) {
    buttonEvent = false;
    return true;
  }
  return false;
}

#endif