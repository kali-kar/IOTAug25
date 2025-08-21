#define LEDCOUNT 3
#define ONTIME 5  // x100 milliseconds

// ONTIME = PERIOD - OFFTIME
uint8_t leds[LEDCOUNT]={17,18,19}; //GPIO list in order
uint8_t count=0;
hw_timer_t *My_timer = NULL;
void IRAM_ATTR onTimer(){
  count++;
  if(count%ONTIME==0){
    uint8_t index = count/ONTIME - 1;
    digitalWrite(leds[index], !digitalRead(leds[index]));
    digitalWrite(leds[(index+1)%LEDCOUNT], !digitalRead(leds[(index+1)%LEDCOUNT]));
  }
  if(count==ONTIME*LEDCOUNT){count=0;}
}

void setup() {
for(uint8_t i=0;i<LEDCOUNT;i++){
  pinMode(leds[i],OUTPUT);
  digitalWrite(leds[i],0);
}
My_timer = timerBegin(0, 80,  true); // counter 0, prescalar = 80, count UP=true

timerAttachInterrupt(My_timer, &onTimer,true);
// Interrupt every 100 millisecond
timerAlarmWrite(My_timer, 100000, true); //timerInstance, alarm Value, auto reload

timerAlarmEnable(My_timer); // Just Enable the timer
digitalWrite(leds[0],1);
}
void loop() {
}


