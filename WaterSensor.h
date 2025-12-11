#ifndef WATER_SENSOR_H
#define WATER_SENSOR_H

volatile unsigned char* my_ADMUX    = (unsigned char*) 0x7C;
volatile unsigned char* my_ADCSRB   = (unsigned char*) 0x7B;
volatile unsigned char* my_ADCSRA   = (unsigned char*) 0x7A;
volatile unsigned int*  my_ADC_DATA = (unsigned int*) 0x78;

// Initialize the ADC for water sensor
void water_init(){
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

// Read the water sensor on the given ADC channel
unsigned int water_read(unsigned char adc_channel_num = 0){
  *my_ADMUX &= 0b11100000;
  *my_ADCSRB &= 0b11110111;

  if(adc_channel_num & 0x08)
    *my_ADCSRB |= 0b00001000;

  *my_ADMUX |= (adc_channel_num & 0x07);

  *my_ADCSRA |= 0b01000000;
  while (*my_ADCSRA & 0b01000000); // wait for conversion

  return (*my_ADC_DATA & 0x03FF);
}

#endif