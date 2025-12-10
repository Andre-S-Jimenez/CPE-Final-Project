//Jacob Darby. Lots of code recycled from Lab 7
#ifndef LCDDRIVER_H
#define LCDDRIVER_H

#include <LiquidCrystal.h>
#include "States.h"

//idk if these are the right pins
#define LCD_RS 11
#define LCD_EN 12
#define LCD_D4 2
#define LCD_D5 3
#define LCD_D6 4
#define LCD_D7 5

static LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

cosnt char* stateMessage(States state) {
    switch (state) {
        case DISABLED: return "DISABLES";
        case IDLE: return "IDLE";
        case ERROR: return "ERROR";
        case RUNNING: return "RUNNING";
        default: return "UNDEFINED STATE";
    }
}
void lcdInit(){
    lcd.begin(16,2);
    lcd.clear();
}

void lcdPrintStatus(float temp, float humidity, States state){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.print(temp, 1);
    lcd.print("F H:");
    lcd.print(humidity,0);
    lcd.print("%");

    lcd.setCursor(0,1);
    lcd.print("State:");
    lcd.print(stateMessage(state));
}

void lcdPrintError(const char* err){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ERROR");
    lcd.setCursor(0,1);
    lcd.print(msg);
}

#endif