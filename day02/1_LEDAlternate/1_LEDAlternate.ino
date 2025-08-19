const int redLED = 2;
const int greenLED = 3;
const int blueLED = 4;
const int buttonPin = 7;

int state = 0; 
bool lastButtonState = HIGH;
bool currentButtonState;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  currentButtonState = digitalRead(buttonPin);

  
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    state = (state + 1) % 4; 
    updateLEDs(state);
    delay(200); 
  }

  lastButtonState = currentButtonState;
}

void updateLEDs(int s) {
  digitalWrite(redLED, s == 1 ? HIGH : LOW);
  digitalWrite(greenLED, s == 2 ? HIGH : LOW);
  digitalWrite(blueLED, s == 3 ? HIGH : LOW);
}
