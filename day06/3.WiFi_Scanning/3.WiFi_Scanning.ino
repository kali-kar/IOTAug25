#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Set ESP32 to station mode and disconnect from any network
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(100);

  Serial.println("Starting WiFi scan...");
}

void loop() {
  // Scan for networks
  int n = WiFi.scanNetworks();

  Serial.println("Scan done.");
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.printf("%d networks found:\n", n);
    for (int i = 0; i < n; ++i) {
      Serial.printf("%d: %s (RSSI: %d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    }
  }

  Serial.println("-----------------------");

  // Wait 10 seconds before next scan
  delay(10000);
}
