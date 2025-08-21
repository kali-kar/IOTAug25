#define LED 5
#define ONTIME 500000  // In microseconds
#define OFFTIME 2000000 // In microseconds
hw_timer_t *My_timer = NULL;
void IRAM_ATTR onTimer(){
digitalWrite(LED, !digitalRead(LED));
if(digitalRead(LED)){
  timerAlarmWrite(My_timer, ONTIME,true);
}
else{
  timerAlarmWrite(My_timer, OFFTIME,true);
}
}
void setup() {
pinMode(LED, OUTPUT);
//Set clock input to counter to 1MHz
My_timer = timerBegin(0, 80,  true); // counter 0, prescalar = 80, count UP=true
timerAttachInterrupt(My_timer, &onTimer, true);
timerAlarmWrite(My_timer, ONTIME,true); //timerInstance, alarm Value, auto reload
timerAlarmEnable(My_timer); //Just Enable
}
void loop() {
}


