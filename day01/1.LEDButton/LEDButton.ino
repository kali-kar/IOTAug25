
const int buttonPin1 = 10;     
int buttonState1 = LOW;       
const int ledPin1 = A2;       
const int buttonPin2 = 11;    
int buttonState2 = LOW;       
const int ledPin2 =  A3;       

void setup() {                   
  pinMode(buttonPin1, INPUT);   
  pinMode(ledPin1, OUTPUT);     
  pinMode(buttonPin2, INPUT);   
  pinMode(ledPin2, OUTPUT);     
  Serial.begin(9600);           
}

void loop() {                  

  buttonState1 = digitalRead(buttonPin1);  
  buttonState2 = digitalRead(buttonPin2);  



if (buttonState1 == LOW) {    
digitalWrite(ledPin1, LOW);  
} else {
digitalWrite(ledPin1, HIGH);   
}
Serial.println(buttonState1); 
if (buttonState2 == LOW) {   
digitalWrite(ledPin2, LOW);  
} else {
digitalWrite(ledPin2, HIGH);   
delay(10);
}
Serial.println(buttonState2);
}
