//TODO: needs real time clock for when fan toggle. 
// "DHT sensor library" by Adafruit
#ifndef DHT_DRIVER_H
#define DHT_DRIVER_H

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2                                          // can change later for conformance to standards
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/*Returns whether the fan should run. 

  In the case of a temperature reading error, it will return false.
*/
bool fanShouldRun() {

  static bool running = false;
  
  float temp = dht.readTemperature(true);                 // Read temperature as Fahrenheit (isFahrenheit = true)


  if (isnan(temp)) {                                      // Check if any reads failed and exit early (to try again).
    Serial.println(F("Temperature Read Malfunction"));
    running = false;
    return false;
  }

  /*If the cooler is running, it will run until it hits 
  60 degrees f, after which it will turn off.
  It will not turn on again until temp exceeds 72 degrees f.*/
  if (running){
    if (temp <= 60.0f){
      running = false;
    }
  }
  /*If the cooler is off, it will stay off until it hits
  72 degrees f, after which it will turn on. 
  It will not turn off again until temp drops below 60.*/
  else {
    if (temp >= 72.0f){
      running = true;
    }
  }
  return running;
}

/*Returns the temperature in farenheit.

  If there is an error reading the temperature,
  it will return an error value of -500, which 
  should not be physically attainable.
*/
float getTemp() {

  float temp = dht.readTemperature(true);

  if (isnan(temp)){
    Serial.println(F("Temperature Read Malfunction"));
    return -500.0f;
  }

  return temp;
}

/*Returns the humidity in whole percent. 

  If there is an error reading the humidity, 
  it will return an error value of -500, which
  should not be physically attainable.
*/
float getHumidity(){

  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println(F("Humidity Read Malfunction"));
    return -500.0f;
  }

  return humidity;  
}

#endif