#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  // Set ESP32 to station mode
  WiFi.mode(WIFI_STA);

  // Start connecting to WiFi network
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }

  // Connected
  Serial.println();
  Serial.println("WiFi connected successfully!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Nothing to do here
}

