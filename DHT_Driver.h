#ifndef DHT_DRIVER_H
#define DHT_DRIVER_H
#include "UartSerial.h"

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 8                                          // can change later for conformance to standards
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


float getTemp() {

  float temp = dht.readTemperature(true);

  if (isnan(temp)){
    U0printStr("Temperature Read Malfunction\n");
    return -500.0f;
  }

  return temp;
}


float getHumidity(){

  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    U0printStr("Humidity Read Malfunction\n");
    return -500.0f;
  }

  return humidity;  
}

#endif