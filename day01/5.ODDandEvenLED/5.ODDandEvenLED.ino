const int ledPins[] = {2, 3, 4, 5, 6, 7}; 
const int numLEDs = 6; 
const int delayTime = 500; 

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < numLEDs; i++) {
    if ((i + 1) % 2 != 0) { 
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  delay(delayTime);

  for (int i = 0; i < numLEDs; i++) {
    if ((i + 1) % 2 == 0) { 
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  delay(delayTime);
}
