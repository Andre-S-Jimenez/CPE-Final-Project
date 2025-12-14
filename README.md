# CPE-Final-Project
CPE Final Project
  
Members:  
    Jacob Darby  
    Andre Jimenez  
    Samuel Landaverde  
 
Vent (uses pin A1):  
    -ventInit()  
    -ventSet(int percent)  
    -ventMove(int steps) <- private  
  
LCD (uses pins 2, 3, 4, 5, 6, 7):  
    -lcdInit()  
    -lcdPrintStatus(float temp, float humidity, State state)  
    -stateMessage(State state) <- private  
    -lcdPrintError(err)  
  
Fan (uses pin 10, 11, 12):  
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
  
8 - DHT  
  
10 - Fan (IN2 on the chip)  
11 - Fan (EN1 on the chip)  
12 - Fan (IN1 on the chip)  
  
18 - button  
  
20 - RTC  
21 - RTC  
  
22 - Vent  
23 - LED  
24 - Vent  
25 - LED  
26 - Vent  
27 - LED  
28 - Vent  
29 - LED  
  
A0 - Water sensor  
  
A1 - Pot for vent control  

