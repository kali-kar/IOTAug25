#define RED 17
#define GRN 18
#define BLU 19
#define PERIOD 15 // x100 millseconds

// ONTIME = PERIOD - OFFTIME
uint8_t count=0;
hw_timer_t *My_timer = NULL;
void IRAM_ATTR onTimer(){
  count++;
  if (count == PERIOD) {
    digitalWrite(RED, !digitalRead(RED));
    digitalWrite(GRN, !digitalRead(GRN));
    }
  if(count == PERIOD*2){    
    digitalWrite(GRN, !digitalRead(GRN));
    digitalWrite(BLU, !digitalRead(BLU));
  }
  if(count == PERIOD*3){    
    digitalWrite(BLU, !digitalRead(BLU));
    digitalWrite(RED, !digitalRead(RED));
    count=0;
  }
}

void setup() {
pinMode(RED, OUTPUT);
pinMode(GRN, OUTPUT);
pinMode(BLU, OUTPUT);
My_timer = timerBegin(0, 80,  true); // counter 0, prescalar = 80, count UP=true

timerAttachInterrupt(My_timer, &onTimer,true);
timerAlarmWrite(My_timer, 100000,true);
timerAlarmEnable(My_timer);
digitalWrite(RED,1);
digitalWrite(GRN,0);
digitalWrite(BLU,0);
}
void loop() {
}


