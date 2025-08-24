#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // For SPI communication
#define TFT_CS    13 // Chip Select pin
#define TFT_DC    14  // Data/Command pin
#define TFT_RST   12  // Reset pin

Adafruit_BMP085 bmp;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("BMP180 Sensor Test");
  tft.initR(INITR_BLACKTAB); // Initialize ST7735S in black tab mode
  
  tft.setTextColor(ST7735_WHITE); // Set text color
  tft.setTextSize(1); // Set text size
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1); // Halt
  }
}

void loop() {
  float temperature = bmp.readTemperature();
  int32_t pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(); // Adjust sea level pressure if needed

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" Pa");

  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" meters");

  Serial.println();
tft.fillScreen(ST7735_BLACK); // Fill screen with black
tft.setCursor(10, 10); // Set text cursor position
  tft.setTextSize(2); // Set text size
  tft.print("BMP180"); // Display text
  tft.setCursor(5, 40); // Set text cursor position
  tft.setTextSize(1); // Set text size
  tft.print("Temperature: "+ String(temperature,1)+" C"); // Display text
tft.setCursor(5, 60); // Set text cursor position
tft.print("Pressure: "+ String(pressure)+" Pa");
tft.setCursor(5, 80); // Set text cursor position
tft.print("Altitude: "+ String(altitude,1)+" M");
  delay(2000); // Read every 2 seconds
}

