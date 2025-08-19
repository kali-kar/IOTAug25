#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <DHT.h>

#define DHTPIN 4     
#define DHTTYPE DHT11  
#define TFT_CS     14
#define TFT_RST    12 
#define TFT_DC     13  //A0
#define TFT_SCLK   SCL   //SCK //CLK //22
#define TFT_MOSI   SDA   //SDA //DIN //21

DHT dht(DHTPIN, DHTTYPE);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

float t;
float h;

void setup() {

  Serial.begin(9600);
  dht.begin();
  tft.initR(INITR_BLACKTAB);                  /* initialize a ST7735S chip, black tab */
  tft.setTextWrap(false);                     /* Allow text to run off right edge */
  tft.fillScreen(ST7735_YELLOW);
}
void loop() {
  Dhtread();
  Display();
  delay(100);
}
void Dhtread(void)
{
  delay(1000);
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.print("Humidity : ");
  Serial.print(h);
  Serial.print("%  Temperature : ");
  Serial.println(t);
  }

void Display(void) {
  tft.fillScreen(0x0000);  /* BLACK -- Background */ 
  tft.setRotation(1);
  //tft.serRotation(2); //for Vertical Display
  tft.setCursor(10, 20);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("Temp C:  ");

  tft.setCursor(110, 20);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println( t);

  tft.setCursor(10, 50);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("Hum %:  ");
    
  tft.setCursor(90, 50);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println( h);

  delay(1000);
}     
