const int trigPin = 10;
const int echoPin = 9;

const int ledHigh = 13;
const int ledMedium = 12;
const int ledLow = 11;
const int buzzer = 8;

const int levelHigh = 15;    // in inches
const int levelMedium = 10;
const int levelLow = 5;
const int levelCritical = 5;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledHigh, OUTPUT);
  pinMode(ledMedium, OUTPUT);
  pinMode(ledLow, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Turn everything off initially
  digitalWrite(ledHigh, LOW);
  digitalWrite(ledMedium, LOW);
  digitalWrite(ledLow, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  long duration, inches;

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);

  Serial.print("Water level: ");
  Serial.print(inches);
  Serial.println(" inches");

  // Reset all outputs
  digitalWrite(ledHigh, LOW);
  digitalWrite(ledMedium, LOW);
  digitalWrite(ledLow, LOW);
  digitalWrite(buzzer, LOW);

  // Decision logic based on water level
  if (inches >= levelHigh) {
    digitalWrite(ledHigh, HIGH); // Full tank
  } else if (inches >= levelMedium) {
    digitalWrite(ledMedium, HIGH); // Medium level
  } else if (inches >= levelLow) {
    digitalWrite(ledLow, HIGH); // Low level warning
  } else if (inches <= levelCritical) {
    digitalWrite(ledLow, HIGH); // Still show low LED
    digitalWrite(buzzer, HIGH); // Critical alert
  }

  delay(500); // Small delay for stability
}

long microsecondsToInches(long microseconds) {
  return (microseconds / 74) / 2;
}
