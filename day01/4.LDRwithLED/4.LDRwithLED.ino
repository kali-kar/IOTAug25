
const int sensorPin = 32;
const int ledPin = 27;


int lightInit;  
int lightVal; 

void setup()
{
  pinMode(ledPin, OUTPUT);
  lightInit = analogRead(sensorPin);
}

void loop()
{

  lightVal = analogRead(sensorPin);

  if(lightVal - lightInit <  50)
  {
      digitalWrite (ledPin, HIGH); 
  }
  else
  {
    digitalWrite (ledPin, LOW); 
  }

}
