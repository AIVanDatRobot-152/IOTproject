#define LED_PIN 2
#define BUTTON_PIN 19
volatile bool ledState = false;
void IRAM_ATTR handleInterrupt() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON_PIN, handleInterrupt, FALLING);
}
void loop() {
}