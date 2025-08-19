const int irSensorPin = 2;

void setup() {
  pinMode(irSensorPin, INPUT);
  Serial.begin(9600);
  Serial.println("IR Motion Detection Initialized");
}

void loop() {
  int sensorState = digitalRead(irSensorPin);

  if (sensorState == LOW) {
    Serial.println("Motion Detected!");
  } else {
    Serial.println("No Motion");
  }

  delay(500);
}
