
int potPin = A3; 
int potVal = 0; 

int redPin = 2;   
int grnPin = 3;  
int bluPin = 4;  

int redVal = 0;   
int grnVal = 0;
int bluVal = 0;

void setup()
{
  pinMode(redPin, OUTPUT);   
  pinMode(grnPin, OUTPUT);   
  pinMode(bluPin, OUTPUT); 
}


void loop()
{
  potVal = analogRead(potPin);   

  if (potVal < 341)  
  {                  
    potVal = (potVal * 3) / 4; 

    redVal = 256 - potVal;  
    grnVal = potVal;        
    bluVal = 1;             
  }
  else if (potVal < 682) 
  {
    potVal = ( (potVal-341) * 3) / 4; 

    redVal = 1;           
    grnVal = 256 - potVal; 
    bluVal = potVal;       
  }
  else  
  {
    potVal = ( (potVal-683) * 3) / 4; 

    redVal = potVal;       
    grnVal = 1;            
    bluVal = 256 - potVal; 
  }
  analogWrite(redPin, redVal);  
  analogWrite(grnPin, grnVal); 
  analogWrite(bluPin, bluVal);  
}
