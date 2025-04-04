// Khai báo các chân kết nối LED
const int LED1 = 2; // GPIO 
const int LED2 = 16; // GPIO 

void setup() {
  // Cấu hình các chân LED là OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Cấu hình PWM cho LED2
  ledcAttach(LED2, 2500, 10); // Attach channel 0 to LED2

  // Khởi động Serial để in trạng thái
  Serial.begin(115200);
}

void loop() {
  // Chớp tắt LED1 mỗi 2 giây
  digitalWrite(LED1, HIGH);
  Serial.println("LED1: ON");
  delay(2000); // Đợi 2 giây

  digitalWrite(LED1, LOW);
  Serial.println("LED1: OFF");
  delay(2000); // Đợi 2 giây

  // Điều chỉnh độ sáng LED2
  ledcWrite(0, 409); // 40% của 1023 (10-bit resolution)
  Serial.println("LED2: 40% brightness");
}
