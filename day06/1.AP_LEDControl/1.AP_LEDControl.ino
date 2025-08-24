#include <WiFi.h>

// Set your Access Point credentials
const char* ssid = "ESP32_AccessPoint_000";
const char* password = "12345678";

// Define LED pins
const int led1Pin = 16;
const int led2Pin = 17;

// Variables to hold LED states
bool led1State = false;
bool led2State = false;

WiFiServer server(80);

String htmlPage() {
  return String("<!DOCTYPE html><html><head><title>ESP32 LED Control</title>") +
         "<meta name='viewport' content='width=device-width, initial-scale=1'>" + 
         "<style>" +
         "body { font-family: Arial; text-align: center; margin-top: 50px; }" +
         "button { padding: 20px; font-size: 24px; margin: 10px; width: 150px; }" +
         ".on { background-color: #4CAF50; color: white; }" +
         ".off { background-color: #f44336; color: white; }" +
         "</style></head><body>" +
         "<h1>ESP32 LED Control</h1>" +
         "<button onclick=\"toggleLED(1)\" id='btn1' class='" + String(led1State ? "on" : "off") + "'>" + (led1State ? "LED 1 ON" : "LED 1 OFF") + "</button>" +
         "<button onclick=\"toggleLED(2)\" id='btn2' class='" + String(led2State ? "on" : "off") + "'>" + (led2State ? "LED 2 ON" : "LED 2 OFF") + "</button>" +

         "<script>" +
         "function toggleLED(led) {" +
         "  var xhr = new XMLHttpRequest();" +
         "  xhr.open('GET', '/toggle?led=' + led, true);" +
         "  xhr.send();" +
         "}" +
         // Update buttons every 1s to sync states after toggling
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
         "</script>" +

         "</body></html>";
}

void setup() {
  Serial.begin(115200);

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  // Start ESP32 Access Point
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP: ");
  Serial.println(IP);

  server.begin();
}

void handleClient(WiFiClient client) {
  String currentLine = "";
  String request = "";
  bool getRequestLineRead = false;

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      request += c;

      // Detect end of HTTP request line
      if (!getRequestLineRead && c == '\n') {
        getRequestLineRead = true;
      }

      if (c == '\n' && currentLine.length() == 0) {
        // End of headers, process request

        // Match GET requests
        if (request.indexOf("GET /toggle?led=1") >= 0) {
          led1State = !led1State;
          digitalWrite(led1Pin, led1State ? HIGH : LOW);
        } else if (request.indexOf("GET /toggle?led=2") >= 0) {
          led2State = !led2State;
          digitalWrite(led2Pin, led2State ? HIGH : LOW);
        } else if (request.indexOf("GET /state") >= 0) {
          // Respond with JSON state of LEDs
          String json = "{\"led1\":" + String(led1State ? "true" : "false") + ",\"led2\":" + String(led2State ? "true" : "false") + "}";
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");
          client.println();
          client.print(json);
          client.stop();
          return;
        }

        // Otherwise serve HTML page
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
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

void loop() {
  WiFiClient client = server.available();
  if (client) {
    handleClient(client);
  }
}
