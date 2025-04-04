// Khai báo các chân kết nối
const int LED_PIN = 2; // Chân kết nối LED
const int POT_PIN = 4; // Chân kết nối biến trở

// Cấu hình kênh PWM
const int PWM_FREQ = 10000; // Tần số PWM 10kHz
const int PWM_CHANNEL = 0; // Kênh PWM
const int PWM_RESOLUTION = 12; // Độ phân giải tối đa (13 bit)

void setup() {
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION  );
  // Cấu hình chân LED là OUTPUT


  // Khởi động Serial để in trạng thái
  Serial.begin(9600);
}

void loop() {
  // Đọc giá trị từ biến trở
  int potValue = analogRead(POT_PIN);
  
  // Chuyển đổi giá trị biến trở thành độ rộng xung PWM
  int pwmValue = map(potValue, 0, 4095, 0, 8191); // 13 bit có giá trị từ 0 đến 8191
  
  // Thiết lập độ rộng xung PWM
  ledcWrite(LED_PIN, potValue);
  
  // In độ rộng xung PWM lên Serial
  Serial.print("PWM Value: ");
  Serial.println(pwmValue);
  
  delay(100); // Đợi 100ms trước khi đọc lại giá trị
}
