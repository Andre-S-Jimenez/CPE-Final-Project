#ifndef VENTDRIVER_H
#define VENTDRIVER_H

#include <Stepper.h>

//implement with potentiometer
//init pins 
#define VENT_IN1 22
#define VENT_IN2 24
#define VENT_IN3 26
#define VENT_IN4 28

//change if not 200 step motor
static Stepper ventStepper(200, VENT_IN1, VENT_IN2, VENT_IN3, VENT_IN4);

static int ventCurr = 0; //start closed

void ventInit(){
    ventStepper.setSpeed(20);
    ventCurr = 0;
}

void ventMove(int steps) {
    ventStepper.step(steps);
    ventCurr += steps;
}

void ventSet(int percent) {
    if (percent < 0){
        percent = 0;
    }
    if (percent > 100){
        percent = 100;
    }

    //math assuming 200 step motor
    int desiredSetting = percent * 2;
    if (desiredSetting != ventCurr){
        int change = desiredSetting - ventCurr;
        ventMove(change);
    }
}

#endif