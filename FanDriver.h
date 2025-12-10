//Jacob Darby
#ifndef FANDRIVER_H
#define FANDRIVER_H

//pin stuff - who knows
volatile unsigned char* my_DDRB = (unsigned char*)0x24;
volatile unsigned char* my_PORTB = (unsigned char*)0x25;

#define FAN_BIT 5

void fanInit(){
    //FAN_BIT as output
    *my_DDRB |= (1 << FAN_BIT);

    //start off
    fanOff();

}

void fanOn() {
    *my_PORTB |= (1 << FAN_BIT);
}

void fanOff() {
    *my_PORTB &= ~(1 << FAN_BIT);
}

#endif