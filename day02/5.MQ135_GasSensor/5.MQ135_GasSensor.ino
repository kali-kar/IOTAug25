
const int mq135Pin = A0;

const float RLOAD = 10.0;       
const float RZERO = 76.63;      
const float PARA = 116.6020682; 
const float PARB = 2.769034857;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("MQ135 Air Quality Sensor Initialized");
}

void loop() {
  int adcValue = analogRead(mq135Pin);
  float voltage = adcValue * (5.0 / 1023.0);
  float resistance = ((5.0 * RLOAD) / voltage) - RLOAD;
  float ratio = resistance / RZERO;

  // Estimate CO₂ concentration in ppm
  float ppm = PARA * pow(ratio, -PARB);

  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print("V | CO₂: ");
  Serial.print(ppm, 2);
  Serial.println(" ppm");

  delay(2000);
}
