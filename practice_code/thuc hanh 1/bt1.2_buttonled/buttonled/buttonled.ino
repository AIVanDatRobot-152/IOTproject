const int buttonPin = 19;  // Chân GPIO 19 cho nút nhấn
const int ledPins[] = {2, 16, 17}; // Các chân GPIO cho các LED (LED1: G2, LED2: G16, LED3: G17)

int currentLed = 0;           // Chỉ số LED hiện tại
int buttonState = 0;          // Trạng thái nút nhấn
int lastButtonState = HIGH;   // Trạng thái trước đó của nút nhấn
unsigned long lastDebounceTime = 0;  // Thời gian debounce
unsigned long debounceDelay = 50;    // Độ trễ debounce (50ms)

void setup() {
  // Thiết lập chân nút nhấn
  pinMode(buttonPin, INPUT_PULLUP);  // Sử dụng chế độ PULLUP cho nút nhấn

  // Thiết lập các chân LED là OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);  // Tắt tất cả LED ban đầu
  }

  Serial.begin(115200);
}

void loop() {
  int reading = digitalRead(buttonPin);  // Đọc trạng thái nút nhấn

  // Kiểm tra nếu trạng thái nút nhấn thay đổi
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Ghi lại thời gian thay đổi trạng thái
  }

  // Kiểm tra nếu vượt qua thời gian debounce (50ms)
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Nếu trạng thái nút nhấn thay đổi
    if (reading != buttonState) {
      buttonState = reading;

      // Khi nút nhấn được bấm (LOW với PULLUP)
      if (buttonState == LOW) {
        // Tắt tất cả LED trước đó
        for (int i = 0; i < 3; i++) {
          digitalWrite(ledPins[i], LOW);
        }

        // Bật LED hiện tại
        digitalWrite(ledPins[currentLed], HIGH);
        Serial.println("LED " + String(currentLed + 1) + " ON");

        // Cập nhật để chuyển sang LED tiếp theo
        currentLed = (currentLed + 1) % 3;  // Khi currentLed >= 3, quay lại LED1
      }
    }
  }

  // Ghi lại trạng thái của nút nhấn cho vòng lặp sau
  lastButtonState = reading;
}
