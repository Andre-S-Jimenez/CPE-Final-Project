// Samuel Landaverde & Andre Jimenez & Jacob Darby
#include "UartSerial.h"
#include "DHT_Driver.h"
#include "States.h"

volatile unsigned char* my_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* my_ADC_DATA = (unsigned int*) 0x78;

unsigned long dhtTime = millis();
States state = DISABLED;

void setup(){
  U0init(9600);
  adc_init();
  dht.begin();
}

void loop(){

  if (state != DISABLED) {
    
    unsigned long currentTime = millis();

    // water level needs to be abstracted
    int value = adc_read(0);
    if (value < 200){
    U0printNum(value);
    U0printStr("Water Level: LOW");
    U0putchar('\n');
    }else{
    U0printStr("Water Level: High");
    U0putchar('\n');
    }

    // toggle dht updates once per minute
    if (currentTime - dhtTime > 60000){
      //TODO: print temperature and humitidy to LCD
    }

  }
    delay(1600); //CHANGE THIS SO IT DOESNT USE "DELAY"
}


void adc_init(){
  *my_ADCSRA |= 0b10000000;
  *my_ADCSRA &= 0b11011111;
  *my_ADCSRA &= 0b11110111;
  *my_ADCSRA |= 0b00000111;
  *my_ADCSRB &= 0b11110111;
  *my_ADCSRB &= 0b11111000;
  *my_ADMUX &= 0b01111111;
  *my_ADMUX |= 0b01000000;
  *my_ADMUX &= 0b11011111;
  *my_ADMUX &= 0b11100000;
}

unsigned int adc_read(unsigned char adc_channel_num){
  *my_ADMUX &= 0b11100000;
  *my_ADCSRB &= 0b11110111;
  if (adc_channel_num & 0x08)
  *my_ADCSRB |= 0b00001000;
  *my_ADMUX |= (adc_channel_num & 0x07);
  *my_ADCSRA |= 0b01000000;
  while((*my_ADCSRA & 0b01000000) != 0);
  unsigned int val = (*my_ADC_DATA & 0x03FF);
  return val;
}
