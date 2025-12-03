// Samuel Landaverde & Andre Jimenez & Jacob Darby
#include "UartSerial.h"
#include "DHT_Driver.h"

void setup(){
  U0init(9600);
  adc_init();
  dht.begin();
}

void loop(){
  int value = adc_read(0);
  if (value < 200){
  U0printNum(value);
  U0printStr("Water Level: LOW");
  U0putchar('\n');
  }else{
  U0printStr("Water Level: High");
  U0putchar('\n');
  }

  delay(1600); //CHANGE THIS SO IT DOESNT USE "DELAY"
}
