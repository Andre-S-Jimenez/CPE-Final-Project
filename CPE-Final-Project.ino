// Samuel Landaverde & Andre Jimenez & Jacob Darby

#define RDA 0x80
#define TBE 0x20  

volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;

volatile unsigned char* my_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* my_ADC_DATA = (unsigned int*) 0x78;

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

void U0init(int U0baud){
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U0baud - 1);
  *myUCSR0A = 0x20;
  *myUCSR0B = 0x18;
  *myUCSR0C = 0x06;
  *myUBRR0  = tbaud;
}

unsigned char U0kbhit(){
  return *myUCSR0A & RDA;
}

unsigned char U0getchar(){
  return *myUDR0;
}

void U0putchar(unsigned char U0pdata){
  while((*myUCSR0A & TBE)==0);
  *myUDR0 = U0pdata;
}

void U0printStr(const unsigned char* string){
  int length = strlen(string);
  for (int i = 0; i < length; i++){
    U0putchar(string[i]);
  }
}

void U0printNum(int number){
  if (number < 10) {
    U0putchar((unsigned char)(number + 48));
  }else {
    U0printNum(number / 10);
    U0putchar((unsigned char)((number % 10) + 48));
  }
}



