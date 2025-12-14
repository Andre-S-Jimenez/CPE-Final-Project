// Jacob Darby
#ifndef FANDRIVER_H
#define FANDRIVER_H

#include "UartSerial.h"

// Pins 10-13 -> PB4-PB7
volatile unsigned char* my_DDRB  = (unsigned char*)0x24;
volatile unsigned char* my_PORTB = (unsigned char*)0x25;

#define FAN_IN2_BIT   4   // Pin 10 -> chip pin 7 (IN2)
#define FAN_EN_BIT    5   // Pin 11 -> chip pin 1 (EN1)
#define FAN_IN1_BIT   6   // Pin 12 -> chip pin 2 (IN1)

static inline void fanOn() {
    // Enable + set direction (IN1=1, IN2=0)
    *my_PORTB |=  (1 << FAN_EN_BIT);
    *my_PORTB |=  (1 << FAN_IN1_BIT);
    *my_PORTB &= ~(1 << FAN_IN2_BIT);
}

static inline void fanOff() {
    // Disable bridge (clean off)
    *my_PORTB &= ~(1 << FAN_EN_BIT);
    *my_PORTB &= ~(1 << FAN_IN1_BIT);
    *my_PORTB &= ~(1 << FAN_IN2_BIT);
}

static inline void fanInit() {
    // Set the three control pins as outputs
    *my_DDRB |= (1 << FAN_EN_BIT) | (1 << FAN_IN1_BIT) | (1 << FAN_IN2_BIT);

    fanOff();
}

#endif
