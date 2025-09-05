//Install WiFiClient library, Install socketTest version 3.0.0 provided by ALS
#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "XXXXXXX";
const char* password = "***********";

// Replace with your DHT sensor type and pin number
#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

WiFiServer server(8888);  // TCP server port

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");

    // Wait for data from client
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        client.flush();

        if (request.indexOf("/humidity") != -1) {
          // Read humidity data from DHT sensor
          float humidity = dht.readHumidity();
          if (isnan(humidity)) {
            Serial.println("Failed to read humidity from DHT sensor");
            client.println("Failed to read humidity from DHT sensor");
          } else {
            Serial.print("Humidity: ");
            Serial.print(humidity);
            Serial.println("%");
            client.print("Humidity: ");
            client.print(humidity);
            client.println("%");
          }
        }

        // Close the connection
        client.stop();
        Serial.println("Client disconnected");
      }
    }
  }
}
