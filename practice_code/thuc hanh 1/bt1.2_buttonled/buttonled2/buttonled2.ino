const int buttonPin = 19;  // Chân GPIO 19 cho nút nhấn
const int LED1 = 2;  // Chân GPIO cho LED1
const int LED2 = 16; // Chân GPIO cho LED2
const int LED3 = 17; // Chân GPIO cho LED3

int currentLed = 1;           // LED hiện tại (bắt đầu từ LED1)
int buttonState = 0;          // Trạng thái nút nhấn hiện tại
int lastButtonState = HIGH;   // Trạng thái nút nhấn trước đó
unsigned long lastDebounceTime = 0;  // Thời gian debounce lần cuối
unsigned long debounceDelay = 50;    // Độ trễ debounce (50ms)

void setup() {
  // Thiết lập chân nút nhấn
  pinMode(buttonPin, INPUT_PULLUP);  // Sử dụng chế độ PULLUP cho nút nhấn

  // Thiết lập các chân LED là OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Tắt tất cả các LED ban đầu
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

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
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);

        // Bật LED hiện tại dựa trên giá trị của `currentLed`
        if (currentLed == 1) {
          digitalWrite(LED1, HIGH);
          Serial.println("LED1 ON");
        } else if (currentLed == 2) {
          digitalWrite(LED2, HIGH);
          Serial.println("LED2 ON");
        } else if (currentLed == 3) {
          digitalWrite(LED3, HIGH);
          Serial.println("LED3 ON");
        }

        // Cập nhật để chuyển sang LED tiếp theo
        currentLed = (currentLed % 3) + 1;  // Chuyển sang LED tiếp theo (1 → 2 → 3 → 1)
      }
    }
  }

  // Ghi lại trạng thái của nút nhấn cho vòng lặp sau
  lastButtonState = reading;
}
