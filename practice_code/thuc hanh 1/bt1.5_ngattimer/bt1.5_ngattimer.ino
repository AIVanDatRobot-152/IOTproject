#define LED 2
hw_timer_t *myTimer = NULL;
void IRAM_ATTR onTimer() {
  digitalWrite(LED, !digitalRead(LED));
}
void setup() {
  pinMode(LED, OUTPUT);
  myTimer = timerBegin(1000000);
  timerAttachInterrupt(myTimer, &onTimer);
  timerAlarm(myTimer, 100000, true, 0);
}
void loop() {
  // Do Nothing!
}