#include <WiFi.h>
#include "DHT.h"

// Replace with your Wi-Fi network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Define LED pins
const int led1Pin = 16;
const int led2Pin = 17;

// Define DHT sensor pin and type
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Variables to hold LED states
bool led1State = false;
bool led2State = false;

WiFiServer server(80);

String htmlPage() {
  return String("<!DOCTYPE html><html><head><title>ESP32 LED & DHT Control</title>") +
         "<meta name='viewport' content='width=device-width, initial-scale=1'>" + 
         "<style>" +
         "body { font-family: Arial; text-align: center; margin-top: 50px; }" +
         "button { padding: 20px; font-size: 18px; margin: 10px; width: 200px; }" +
         ".on { background-color: #4CAF50; color: white; }" +
         ".off { background-color: #f44336; color: white; }" +
         "#dhtData { margin-top: 20px; font-size: 20px; }" +
         "</style></head><body>" +
         "<h1>ESP32 LED & DHT Control</h1>" +

         "<button onclick=\"toggleLED(1)\" id='btn1' class='" + String(led1State ? "on" : "off") + "'>" + (led1State ? "LED 1 ON" : "LED 1 OFF") + "</button>" +
         "<button onclick=\"toggleLED(2)\" id='btn2' class='" + String(led2State ? "on" : "off") + "'>" + (led2State ? "LED 2 ON" : "LED 2 OFF") + "</button>" +

         "<br><button onclick=\"getDHTData()\" id='btn3'>Read DHT11</button>" +

         "<div id='dhtData'>DHT Data will appear here</div>" +

         "<script>" +
         "function toggleLED(led) {" +
         "  var xhr = new XMLHttpRequest();" +
         "  xhr.open('GET', '/toggle?led=' + led, true);" +
         "  xhr.send();" +
         "}" +

         "function getDHTData() {" +
         "  fetch('/dht')" +
         "    .then(response => response.json())" +
         "    .then(data => {" +
         "      const dhtDiv = document.getElementById('dhtData');" +
         "      if(data.success) {" +
         "        dhtDiv.textContent = 'Humidity: ' + data.humidity + ' %, Temp: ' + data.temperature + '°C';" +
         "      } else {" +
         "        dhtDiv.textContent = 'Failed to read from DHT sensor';" +
         "      }" +
         "    })" +
         "    .catch(() => {" +
         "      document.getElementById('dhtData').textContent = 'Error fetching DHT data';" +
         "    });" +
         "}" +

         // Update LED buttons every 1s to sync states
         "setInterval(() => {" +
         "  fetch('/state')" +
         "    .then(response => response.json())" +
         "    .then(data => {" +
         "      const btn1 = document.getElementById('btn1');" +
         "      const btn2 = document.getElementById('btn2');" +
         "      btn1.className = data.led1 ? 'on' : 'off';" +
         "      btn2.className = data.led2 ? 'on' : 'off';" +
         "      btn1.textContent = data.led1 ? 'LED 1 ON' : 'LED 1 OFF';" +
         "      btn2.textContent = data.led2 ? 'LED 2 ON' : 'LED 2 OFF';" +
         "    });" +
         "}, 1000);" +

         "</script></body></html>";
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void handleClient(WiFiClient client) {
  String currentLine = "";
  String request = "";
  bool getRequestLineRead = false;

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      request += c;

      if (!getRequestLineRead && c == '\n') {
        getRequestLineRead = true;
      }

      if (c == '\n' && currentLine.length() == 0) {
        if (request.indexOf("GET /toggle?led=1") >= 0) {
          led1State = !led1State;
          digitalWrite(led1Pin, led1State ? HIGH : LOW);
        } else if (request.indexOf("GET /toggle?led=2") >= 0) {
          led2State = !led2State;
          digitalWrite(led2Pin, led2State ? HIGH : LOW);
        } else if (request.indexOf("GET /state") >= 0) {
          String json = "{\"led1\":" + String(led1State ? "true" : "false") +
                        ",\"led2\":" + String(led2State ? "true" : "false") + "}";
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json; charset=utf-8");
          client.println("Connection: close");
          client.println();
          client.print(json);
          client.stop();
          return;
        } else if (request.indexOf("GET /dht") >= 0) {
          float humidity = dht.readHumidity();
          float temperature = dht.readTemperature();

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json; charset=utf-8");
          client.println("Connection: close");
          client.println();

          if (isnan(humidity) || isnan(temperature)) {
            client.print("{\"success\":false}");
          } else {
            String json = "{\"success\":true,\"humidity\":" + String(humidity, 1) +
                          ",\"temperature\":" + String(temperature, 1) + "}";
            client.print(json);
          }
          client.stop();
          return;
        }

        // Serve the main web page for any other requests
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html;charset=utf-8");
        client.println("Connection: close");
        client.println();
        client.println(htmlPage());
        client.stop();
        return;
      }

      if (c == '\n') {
        currentLine = "";
      } else if (c != '\r') {
        currentLine += c;
      }
    }
  }
  client.stop();
}

void setup() {
  Serial.begin(115200);

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  dht.begin();

  connectToWiFi();

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    handleClient(client);
  }
}
