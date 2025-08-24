#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int LED_PIN = 2; // Onboard LED, change pin if using external LED

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  SerialBT.begin("ESP32_BT_LED"); // Bluetooth device name
  Serial.println("Bluetooth started. Ready for commands (ON/OFF).");
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim(); // Remove trailing newlines or spaces

    if (command.equalsIgnoreCase("ON")) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
      SerialBT.println("LED ON");
    } else if (command.equalsIgnoreCase("OFF")) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
      SerialBT.println("LED OFF");
    } else {
      Serial.println("Unknown command: " + command);
      SerialBT.println("Unknown command: " + command);
    }
  }
  delay(20);
}

