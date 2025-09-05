#define BLYNK_TEMPLATE_ID "*********"
#define BLYNK_TEMPLATE_NAME "***********"
#define BLYNK_AUTH_TOKEN "**************"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Replace with your Wi-Fi credentials
char ssid[] = "*************";
char pass[] = "****************";

#define LED_PIN 2  // Onboard LED or external LED connected to GPIO 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Start with LED off

  // Connect to Wi-Fi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Connecting to Blynk...");
}

void loop() {
  Blynk.run();  // Keep Blynk connection alive
}

// This function is triggered when the app writes to Virtual Pin V0
BLYNK_WRITE(V0) {
  int ledState = param.asInt();  // 1 = ON, 0 = OFF
  digitalWrite(LED_PIN, ledState);
  Serial.printf("LED set to: %s\n", ledState ? "ON" : "OFF");
}