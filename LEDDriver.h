#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "States.h"

// LED pin definitions - using Port A (pins 22-29 on Arduino Mega)
// Yellow LED - PA0 (pin 22)
// Green LED  - PA1 (pin 24)
// Red LED    - PA2 (pin 26)
// Blue LED   - PA3 (pin 28)

volatile unsigned char* my_DDRA  = (unsigned char*)0x21;
volatile unsigned char* my_PORTA = (unsigned char*)0x22;

#define YELLOW_LED_BIT 0
#define GREEN_LED_BIT  1
#define RED_LED_BIT    2
#define BLUE_LED_BIT   3

void ledInit(){
  *my_DDRA |= (1 << YELLOW_LED_BIT);
  *my_DDRA |= (1 << GREEN_LED_BIT);
  *my_DDRA |= (1 << RED_LED_BIT);
  *my_DDRA |= (1 << BLUE_LED_BIT);
  ledAllOff();
}

void ledYellowOn(){
  *my_PORTA |= (1 << YELLOW_LED_BIT);
}

void ledYellowOff(){
  *my_PORTA &= ~(1 << YELLOW_LED_BIT);
}

void ledGreenOn(){
  *my_PORTA |= (1 << GREEN_LED_BIT);
}

void ledGreenOff(){
  *my_PORTA &= ~(1 << GREEN_LED_BIT);
}

void ledRedOn(){
  *my_PORTA |= (1 << RED_LED_BIT);
}

void ledRedOff(){
  *my_PORTA &= ~(1 << RED_LED_BIT);
}

void ledBlueOn(){
  *my_PORTA |= (1 << BLUE_LED_BIT);
}

void ledBlueOff(){
  *my_PORTA &= ~(1 << BLUE_LED_BIT);
}

void ledAllOff() {
  *my_PORTA &= ~(1 << YELLOW_LED_BIT);
  *my_PORTA &= ~(1 << GREEN_LED_BIT);
  *my_PORTA &= ~(1 << RED_LED_BIT);
  *my_PORTA &= ~(1 << BLUE_LED_BIT);
}

void ledSetState(States state){
  ledAllOff();
  switch(state){
    case DISABLED:
      ledYellowOn();
      break;
      
    case IDLE:
      ledGreenOn();
      break;
      
    case ERROR:
      ledRedOn();
      break;
      
    case RUNNING:
      ledBlueOn();
      break;
      
    default:
      ledAllOff();
      break;
  }
}

#endif