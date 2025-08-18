#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

const int led1Pin = 6;
const int led2Pin = 7;

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 LED Control</title>
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; }
    button { padding: 15px 30px; margin: 10px; font-size: 18px; }
    #status { margin-top: 20px; font-weight: bold; }
  </style>
</head>
<body>
  <h1>ESP32 LED Controller</h1>
  <button onclick="toggleLED(1)">LED 1</button>
  <button onclick="toggleLED(2)">LED 2</button>
  <div id="status">Connecting...</div>

  <script>
    let socket = new WebSocket(`ws://${location.hostname}:81`);
    socket.onopen = () => document.getElementById("status").innerText = "Connected ✅";
    socket.onclose = () => document.getElementById("status").innerText = "Disconnected ❌";
    socket.onerror = () => document.getElementById("status").innerText = "Error ❌";
    socket.onmessage = (event) => console.log("ESP32 says:", event.data);

    function toggleLED(led) {
      socket.send("toggle" + led);
    }
  </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send_P(200, "text/html", webpage);
}

void setup() {
  Serial.begin(115200);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.begin();

  webSocket.begin();
  webSocket.onEvent([](uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
      case WStype_CONNECTED:
        Serial.println("Client connected");
        break;
      case WStype_DISCONNECTED:
        Serial.println("Client disconnected");
        break;
      case WStype_TEXT:
        String msg = String((char*)payload);
        if (msg == "toggle1") {
          digitalWrite(led1Pin, !digitalRead(led1Pin));
        } else if (msg == "toggle2") {
          digitalWrite(led2Pin, !digitalRead(led2Pin));
        }
        break;
    }
  });
}

void loop() {
  server.handleClient();
  webSocket.loop();
}