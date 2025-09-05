#include <WiFi.h>
#include <WiFiUdp.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "XXXXXXXX";
const char* password = "******************";

// Replace with your DHT sensor type and pin
#define DHT_PIN 4
#define DHT_TYPE DHT11

// UDP server port
#define UDP_PORT 5000

// Create an instance of the DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

WiFiUDP udp;
float humidity = 0.0;

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP32 IP address
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  // Start the UDP server
  udp.begin(UDP_PORT);
  Serial.println("UDP server started");

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Wait for incoming UDP packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Read the incoming packet
    char packetData[packetSize];
    udp.read(packetData, packetSize);
    String request = String(packetData);

    if (request == "get_humidity") {
      // Read humidity from the DHT sensor
      humidity = dht.readHumidity();

      // Send humidity data to the UDP client
      udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.printf("Humidity: %.2f%%", humidity);
      udp.endPacket();
      Serial.printf("Sent humidity data: %.2f%%\n", humidity);
    }
  }
}
