int leds[] = {A2,A3,A4,A5}; 
int numLEDs = 4;
int delayTime = 200; 
int direction = 1; 
int currentLED = 0;

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
    for (int i = 0; i < numLEDs; i++) {
        digitalWrite(leds[i], LOW);
    }

    digitalWrite(leds[currentLED], HIGH);
    currentLED += direction;
    if (currentLED >= numLEDs - 1 || currentLED <= 0) {
        direction *= -1; 
    }
}
