// Samuel Landaverde & Andre Jimenez & Jacob Darby
#include "UartSerial.h"
#include "DHT_Driver.h"
#include "States.h"
#include "LcdDriver.h"
#include "FanDriver.h"
#include "VentDriver.h"
#include "LEDDriver.h"
#include "ButtonDriver.h"
#include "RTCDriver.h"

#define POT_ADC_CHANNEL 1

volatile unsigned char* my_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* my_ADC_DATA = (unsigned int*) 0x78;

States state = DISABLED;

unsigned long previousTime = 0;
const unsigned long LOOP_INTERVAL = 1600;

unsigned long dhtTime = 0;
const unsigned long DHT_INTERVAL = 6000;

float lastTemp = 0.0;
float lastHumidity = 0.0;
bool dhtValid = false;

static bool coolerRunning = false;
static bool fanIsOn = false;
static int lastWaterLevel = 1023;
static int lastVentPercentLogged = -1;

void adc_init();
unsigned int adc_read(unsigned char adc_channel_num);

static const unsigned char* stateStr(States s) {
  switch (s) {
    case DISABLED: return (const unsigned char*)"DISABLED";
    case IDLE: return (const unsigned char*)"IDLE";
    case ERROR: return (const unsigned char*)"ERROR";
    case RUNNING: return (const unsigned char*)"RUNNING";
    default: return (const unsigned char*)"UNDEFINED";
  }
}

void setState (States newState) {
  if (state == newState){
    return;
  }
  state = newState;
  rtc_logStateChange(stateStr(state));
  ledSetState(state);

  if (state == DISABLED) {
    fanOff();
    if (fanIsOn){
      fanIsOn = false;
      rtc_logFanChange(false);
    }
    coolerRunning = false;
    lcdBlank();
    //lcdPrintStatus(lastTemp, lastHumidity, state);
  } else if (state == ERROR) {
    fanOff();
    if (fanIsOn){
      fanIsOn = false;
      rtc_logFanChange(false);
    }
    coolerRunning = false;
    lcdPrintError("WATER LOW");
  } else {
    if (dhtValid){
      lcdPrintStatus(lastTemp, lastHumidity, state);
    }else{
      lcdPrintStatus(0.0, 0.0, state);
    }
  
  }
}
void setup(){
  U0init(9600);
  rtc_init();
  adc_init();
  dht.begin();
  lcdInit();

  ledInit();
  fanInit();
  ventInit();
  buttonInit();
  setState(DISABLED);
  ledSetState(state);
 
  dhtTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  if (state == ERROR) {
    lastWaterLevel = (int)adc_read(0);
  }

  if (buttonPressedEvent()) {
    if (state == DISABLED) {
      setState(IDLE);
    } else if (state == ERROR) {
      lastWaterLevel = (int)adc_read(0);
      if (lastWaterLevel >= 200) {
        setState(IDLE);
      }
    } else {
      setState(DISABLED);
    }
  }

  if (state == DISABLED) {
    return;
  }

  static int lastVentPercent = -1;
  unsigned int potVal = adc_read(POT_ADC_CHANNEL);
  int ventPercent = (int)(((unsigned long)potVal * 100UL) / 1023UL);
  if (lastVentPercent < 0 || abs(ventPercent - lastVentPercent) >= 2) {
    ventSet(ventPercent);
    lastVentPercent = ventPercent;

    if (lastVentPercentLogged != ventPercent) {
      rtc_logVentChange(ventPercent);
      lastVentPercentLogged = ventPercent;
    }
  }

  if ((currentTime - dhtTime) >= DHT_INTERVAL) {
    float t = getTemp();
    float h = getHumidity();
    if (t != -500.0f && h != -500.0f) {
      lastTemp = t;
      lastHumidity = h;
      dhtValid = true;

      if (state == IDLE || state == RUNNING) {
        lcdPrintStatus(lastTemp, lastHumidity, state);
      }
    }
    dhtTime = currentTime;
  }

  if (currentTime - previousTime >= LOOP_INTERVAL) {
    previousTime = currentTime;

    lastWaterLevel = (int)adc_read(0);

    if (lastWaterLevel < 200) {
      setState(ERROR);
      return;
    }


    if (state == ERROR) {
      fanOff();
      if (fanIsOn) {
        fanIsOn = false;
        rtc_logFanChange(false);
      }
      return;
    }

    if (dhtValid) {
      if (coolerRunning) {
        if (lastTemp <= 60.0f) coolerRunning = false;
      } else {
        if (lastTemp >= 72.0f) coolerRunning = true;
      }
    } else {
      coolerRunning = false;
    }

    if (coolerRunning) {
      if (state != RUNNING) setState(RUNNING);
      fanOn();
      if (!fanIsOn) {
        fanIsOn = true;
        rtc_logFanChange(true);
      }
    } else {
      if (state != IDLE) setState(IDLE);
      fanOff();
      if (fanIsOn) {
        fanIsOn = false;
        rtc_logFanChange(false);
      }
    }
  }
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
