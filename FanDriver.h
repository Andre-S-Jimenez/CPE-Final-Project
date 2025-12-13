//Jacob Darby
#ifndef FANDRIVER_H
#define FANDRIVER_H
#include "UartSerial.h"
//pin stuff - who knows
volatile unsigned char* my_DDRB = (unsigned char*)0x24;
volatile unsigned char* my_PORTB = (unsigned char*)0x25;

#define FAN_BIT 7

void fanOn() {
    //U0printStr("fanOn() executed by fan driver\n");
    *my_PORTB |= (1 << FAN_BIT);
}

void fanOff() {
    //U0printStr("fanOff() executed by fan driver\n");
    *my_PORTB &= ~(1 << FAN_BIT);
}

void fanInit(){
    //FAN_BIT as output
    *my_DDRB |= (1 << FAN_BIT);

    //start off
    fanOff();

}

#endif