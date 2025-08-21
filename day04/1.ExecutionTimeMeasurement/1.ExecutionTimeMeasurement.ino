
hw_timer_t * timer = NULL;

void setup() {
  // put your setup code here, to run once:
timer = timerBegin(1, 8, true); // Input to counter @10MHz (100 nano seconds period)
timerAlarmEnable(timer);
uint64_t start_time = timerRead(timer);
delay(100);
uint64_t end_time = timerRead(timer);
uint64_t duration = end_time- start_time; // Ticks
timerAlarmDisable(timer);
timerEnd(timer);
Serial.begin(115200);
Serial.println("Start Timer Value: " +String(start_time) );
Serial.println("End Timer Value: " + String(end_time));
Serial.println("Time for executing the instruction: " +String(duration*100 ) + " nanoseconds");
}

void loop() {
  // put your main code here, to run repeatedly:

}
