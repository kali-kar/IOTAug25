#include "DHT.h"
#define INTERVAL_MS 10 * 1000 // in milliseconds
#define DHT11PIN 4
#define LED 5
#define INTERVAL_MS 10 * 1000
DHT dht(DHT11PIN, DHT11);
volatile bool readDHT = false; // Flag to trigger DHT reading in loop
hw_timer_t *My_timer = NULL;
void IRAM_ATTR onTimer(){
  readDHT=true;
}
void setup() {
  My_timer = timerBegin(0, 80,  true); // counter 0, prescalar = 80, count UP=true
  timerAttachInterrupt(My_timer, &onTimer,true); // Attach timer interrupt with service routine
  timerAlarmWrite(My_timer, INTERVAL_MS*1000, true);// set the timer interval
  timerAlarmEnable(My_timer); 
  Serial.begin(9600);  /* Start the DHT11 Sensor */
  dht.begin();
  pinMode(LED, OUTPUT);
  digitalWrite(LED,0);
}
void loop() {
  // LED will blink independent of the code here
if(readDHT) {
  readDHT=false;
  digitalWrite(LED,1);
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.println("Temperature: "+ String(temp) + " °C");
  Serial.println("Humidity: " + String(humi) + " % ");
  delay(100);
  digitalWrite(LED,0);
}
  
}
