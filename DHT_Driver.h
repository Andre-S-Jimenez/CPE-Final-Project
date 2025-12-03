// "DHT sensor library" by Adafruit
#ifndef DHT_DRIVER_H
#define DHT_DRIVER_H

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2              // can change later for conformance to standards
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// to read humidity: dgt.readHumidity();
bool fanShouldRun() {

  static bool running = false;
  
  float temp = dht.readTemperature(true);                  // Read temperature as Fahrenheit (isFahrenheit = true)

  // Check if any reads failed and exit early (to try again).
  if (isnan(temp)) {
    Serial.println(F("Temperature Read Malfunction"));
    running = false;
    return false;
  }

  /*If the cooler is running, it will run until it hits 
  60 degrees f, after which it will turn off.
  It will not turn on again until temp exceeds 72 degrees f.*/
  if (running){
    if (temp > 60.0f){
      return true;
    }
    else {
      return false;
    }
  }
  /*If the cooler is off, it will stay off until it hits
  72 degrees f, after which it will turn on. 
  It will not turn off again until temp drops below 60.*/
  else {
    if (temp < 72.0f){
      return false;
    }
    else {
      return true;
    }
  }

}
#endif