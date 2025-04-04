#define TRIMPOT_PIN 4 // Chọn chân analog để kết nối với biến trở
hw_timer_t *myTimer = NULL; 
void IRAM_ATTR readPotentiometer() {
  int rawValue = analogRead(TRIMPOT_PIN); // Đọc giá trị từ biến trở
  float voltage = rawValue * (3.3 / 4095.0); // Chuyển đổi giá trị sang điện áp (3.3V là điện áp tham chiếu)
  
  Serial.print("Raw value: ");
  Serial.print(rawValue);
  Serial.print(", Voltage: ");
  Serial.println(voltage, 2); // In giá trị điện áp với 2 chữ số thập phân
}

void setup() {
  Serial.begin(9600); // Khởi tạo kết nối Serial Monitor
  analogReadResolution(12); // Đặt độ phân giải ADC là 12 bit (giá trị từ 0 đến 4095)
  myTimer =timerBegin(1000000);
  timerAttachInterrupt(myTimer, &readPotentiometer); // Gắn hàm đọc giá trị biến trở vào bộ đếm
  timerAlarm(myTimer, 50000, true, 0); // Đặt thời gian hẹn giờ là 500 ms
}

void loop() {
  // Do nothing in the loop
}