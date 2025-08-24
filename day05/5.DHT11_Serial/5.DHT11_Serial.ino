#include "DHT.h"
#define DHT11PIN 4
DHT dht(DHT11PIN, DHT11);
//float humi, temp;
void setup()
{
  Serial.begin(9600);
  /* Start the DHT11 Sensor */
  dht.begin();
}
void loop()
{
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.println(" % ");
  delay(2000);
}