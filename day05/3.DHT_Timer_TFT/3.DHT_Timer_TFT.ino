#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // For SPI communication
#include "DHT.h"
#define INTERVAL_MS 10 * 1000 // in milliseconds
#define DHT11PIN 4
#define LED 5
#define INTERVAL_MS 10 * 1000
#define TFT_CS    13 // Chip Select pin
#define TFT_DC    14  // Data/Command pin
#define TFT_RST   12  // Reset pin

// Above THREE pins are user defined. Can be altered
// GPIO18 is connected to SCK (SPI Clock Pin)
// GPIO23 is connected to SDA (SPI MOSI Pin)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
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
  tft.initR(INITR_BLACKTAB); // Initialize ST7735S in black tab mode
  tft.fillScreen(ST7735_BLACK); // Fill screen with black
  tft.setTextColor(ST7735_WHITE); // Set text color
  tft.setTextSize(1); // Set text size
  tft.fillScreen(ST7735_BLACK); // Fill screen with black
}
void loop() {
  // LED will blink independent of the code here
if(readDHT) {
  readDHT=false;
  digitalWrite(LED,1);
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.println("Temperature: "+ String(temp) + " °C");
  tft.fillScreen(ST7735_BLACK); // Fill screen with black
  tft.setCursor(2, 10); // Set text cursor position
  tft.print("Temperature: "+ String(temp) + " C"); // Display Temperature
  Serial.println("Humidity: " + String(humi) + " %");
  tft.setCursor(2, 30); // Set text cursor position
  tft.print("Humidity: " + String(humi) + " %"); // Display Humidity
  delay(100);
  digitalWrite(LED,0);

}
  
}

