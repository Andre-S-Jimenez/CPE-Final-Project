# CPE-Final-Project
CPE Final Project
 
Vent (uses pin A1): 
    -ventInit()
    -ventSet(int percent)
        -ventMove(int steps) <- private

LCD (uses pins 2, 3, 4, 5, 6, 7): 
    -lcdInit()
    -lcdPrintStatus(float temp, float humidity, State state)
        -stateMessage(State state) <- private
    -lcdPrintError(err)

Fan (uses pin 13):
    -fanInit()
    -fanOn()
    -fanOff()

MASTER PIN REFERENCE HERE:
0 - XX
1 - XX

2 - LCD RS
3 - LCD EN
4 - LCD D4
5 - LCD D5
6 - LCD D6
7 - LCD D7

13 - Fan output

A0 - Water sensor

A1 - Pot for vent control

22 - Vent
24 - Vent
26 - Vent
28 - Vent