#include "BluetoothSerial.h"
#include "DHT.h"

BluetoothSerial SerialBT;

DHT* dht = nullptr;  // Pointer to a DHT object
int currentPin = -1; // Track currently active pin

#define DHTTYPE DHT11  // Change to DHT11 if needed

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_100");
  Serial.println("Bluetooth DHT started. Send commands like 'DHT4' or 'DHT14' to get readings.");
}

void loop() {
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    cmd.trim();

    if (cmd.startsWith("DHT")) {
      String pinStr = cmd.substring(3); 

      if (pinStr.length() == 0) {
        SerialBT.println("Error: No pin number specified.");
        Serial.println("Error: No pin number specified.");
        return;
      }

      int pinNum = pinStr.toInt();
      if (pinNum == 0 && pinStr != "0") {
        SerialBT.println("Invalid pin number.");
        Serial.println("Invalid pin number.");
        return;
      }

      if (pinNum != currentPin) {
        // Only create a new DHT object if the pin is different
        if (dht) {
          delete dht;
          dht = nullptr;
        }
        currentPin = pinNum;
        dht = new DHT(currentPin, DHTTYPE);
        pinMode(currentPin, INPUT);
        dht->begin();
        delay(1500); // Give sensor time to stabilize
      }

      float humidity = dht->readHumidity();
      float temperature = dht->readTemperature();

      if (isnan(humidity) || isnan(temperature)) {
        SerialBT.println("Failed to read from DHT sensor on pin " + String(currentPin));
        Serial.println("Failed to read from DHT sensor on pin " + String(currentPin));
      } else {
        String response = "Pin " + String(currentPin) + " - Humidity: " + String(humidity, 1) + "%  Temp: " + String(temperature, 1) + " C";
        SerialBT.println(response);
        Serial.println(response);
      }
    } else {
      SerialBT.println("Unknown command");
      Serial.println("Unknown command: " + cmd);
    }
  }
  delay(20);
}
