#include <dht.h>
dht DHT11;

#define DHT11_PIN 5     // Digital pin connected to the DHT sensor

int ledPin = 6;
int buzzerPin = 10;
float tempThreshold = 20.0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  float chk = DHT11.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT11.temperature);
  if (DHT11.temperature >= tempThreshold) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); // Turn on the buzzer
    delay(1000);           // Wait for 1 second
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);     // Turn off the buzzer
  }
  delay(2000);  //wait for 2 seconds to take the next reading
}
