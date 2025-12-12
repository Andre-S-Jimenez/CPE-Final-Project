#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

#include <RTClib.h>

static RTC_DS1307 rtc;

void rtc_init(){
  if(!rtc.begin()){
    U0printStr((const unsigned char*)"RTC initialization failed\n");
    while (1);
  }

  if(!rtc.isrunning()){
    U0printStr((const unsigned char*)"RTC not running, setting time\n");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void rtc_getTimestamp(char* buffer) {
  DateTime now = rtc.now();

  buffer[0] = (now.year() / 1000) % 10 + '0';
  buffer[1] = (now.year() / 100) % 10 + '0';
  buffer[2] = (now.year() / 10) % 10 + '0';
  buffer[3] = now.year() % 10 + '0';
  buffer[4] = '-';
  buffer[5] = (now.month() / 10) + '0';
  buffer[6] = (now.month() % 10) + '0';
  buffer[7] = '-';
  buffer[8] = (now.day() / 10) + '0';
  buffer[9] = (now.day() % 10) + '0';
  buffer[10] = ' ';
  buffer[11] = (now.hour() / 10) + '0';
  buffer[12] = (now.hour() % 10) + '0';
  buffer[13] = ':';
  buffer[14] = (now.minute() / 10) + '0';
  buffer[15] = (now.minute() % 10) + '0';
  buffer[16] = ':';
  buffer[17] = (now.second() / 10) + '0';
  buffer[18] = (now.second() % 10) + '0';
  buffer[19] = '\0';
}

void rtc_logStateChange(const unsigned char* newState) {
  char timestamp[20];
  rtc_getTimestamp(timestamp);
  
  U0printStr((const unsigned char*)"[");
  U0printStr((const unsigned char*)timestamp);
  U0printStr((const unsigned char*)"] State changed to: ");
  U0printStr(newState);
  U0putchar('\n');
}

void rtc_logFanChange(bool fanOn) {
  char timestamp[20];
  rtc_getTimestamp(timestamp);
  
  U0printStr((const unsigned char*)"[");
  U0printStr((const unsigned char*)timestamp);
  U0printStr((const unsigned char*)"] Fan motor turned ");
  if (fanOn) {
    U0printStr((const unsigned char*)"ON\n");
  } else {
    U0printStr((const unsigned char*)"OFF\n");
  }
}

void rtc_logVentChange(int position) {
  char timestamp[20];
  rtc_getTimestamp(timestamp);
  
  U0printStr((const unsigned char*)"[");
  U0printStr((const unsigned char*)timestamp);
  U0printStr((const unsigned char*)"] Vent position changed to: ");
  U0printNum(position);
  U0putchar('%');
  U0putchar('\n');
}

#endif