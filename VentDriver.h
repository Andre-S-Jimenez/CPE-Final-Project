#ifndef VENTDRIVER_H
#define VENTDRIVER_H

#define VENT_DEADBAND_STEPS 30
#include <Stepper.h>

//implement with potentiometer
//init pins 
#define VENT_IN1 22
#define VENT_IN2 26
#define VENT_IN3 24
#define VENT_IN4 28

//change if not 200 step motor
static Stepper ventStepper(2048, VENT_IN1, VENT_IN2, VENT_IN3, VENT_IN4);

static int ventCurr = 0; //start closed
void ventMove(int steps) {
    ventStepper.step((int)steps);
    ventCurr += steps;
    if (ventCurr < 0){
        ventCurr = 0;
    }
    if (ventCurr > 2048){
        ventCurr = 2048;
    }
}

void ventSet(int percent) {
    if (percent < 0){
        percent = 0;
    }
    if (percent > 100){
        percent = 100;
    }

    //math assuming 200 step motor
    long desiredSetting = ((long)percent * 2048L)/100L;
    long change = desiredSetting - ventCurr;

    if (labs(change) <= VENT_DEADBAND_STEPS){
        return;
    }
    
    ventMove(change);
}

void ventInit(){
    
    ventStepper.setSpeed(10);
    //close all the way
    ventStepper.step(-2048);
    ventCurr = 0;

}



#endif