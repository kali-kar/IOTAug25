#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>  // Install ArduinoJson library via Library Manager
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // For SPI communication
#define TFT_CS    13 // Chip Select pin
#define TFT_DC    14  // Data/Command pin
#define TFT_RST   12  // Reset pin
// Above THREE pins are user defined. Can be altered
// GPIO18 is connected to SCK (SPI Clock Pin)
// GPIO23 is connected to SDA (SPI MOSI Pin)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
// WiFi credentials
const char* ssid = "SAMS";
const char* password = "SAMata06";

// MQTT Broker info
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

// JSON buffer size (adjust if needed)
StaticJsonDocument<200> jsonDoc;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");

  // Copy payload into a string for JSON parsing
  char jsonBuffer[256];
  if (length < sizeof(jsonBuffer)) {
    memcpy(jsonBuffer, payload, length);
    jsonBuffer[length] = '\0'; // Null terminate the string

    Serial.println(jsonBuffer);

    // Parse JSON
    DeserializationError error = deserializeJson(jsonDoc, jsonBuffer);
    if (!error) {
      const char* timestamp = jsonDoc["timestamp"];
      float temperature = jsonDoc["temperature"];
      tft.fillScreen(ST7735_BLACK); // Fill screen with black
      tft.setCursor(10, 5); // Set text cursor position
      tft.setTextSize(2); // Set text size
      tft.print("MQTT"); // Display text
      Serial.print("Timestamp: ");
      Serial.println(timestamp);
      Serial.print("Temperature: ");
      Serial.println(temperature, 2);
      tft.setCursor(10, 25); // Set text cursor position
      tft.setTextSize(1); // Set text size
      tft.print(timestamp); // Display text
      tft.setCursor(10, 50); // Set text cursor position
      tft.print("Temperature: "+ String(temperature,2)); // Display text

    } else {
      Serial.print("JSON parse error: ");
      Serial.println(error.c_str());
      tft.fillScreen(ST7735_BLACK); // Fill screen with black
      tft.setCursor(10, 5); // Set text cursor position
      tft.setTextSize(1); // Set text size
      tft.print("JSON parse error"); // Display text
    }
  } else {
    Serial.println("Payload too large");
      tft.fillScreen(ST7735_BLACK); // Fill screen with black
      tft.setCursor(10, 5); // Set text cursor position
      tft.setTextSize(1); // Set text size
      tft.print("Payload too large"); // Display text
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Consumer-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("esp3201/ds18b2001/temperature");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  tft.initR(INITR_BLACKTAB); // Initialize ST7735S in black tab mode
  tft.fillScreen(ST7735_BLACK); // Fill screen with black
   tft.setTextColor(ST7735_WHITE); // Set text color
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
