// Khai báo chân kết nối với biến trở (giả sử nối vào chân GPIO 34)
const int potPin = 4;

// Các thông số của ADC và điện áp
const float voltageRef = 3.3;  // Điện áp tham chiếu của ESP32 (thường là 3.3V)
const int resolution = 4095;   // Độ phân giải của ADC ESP32 (12-bit -> từ 0 đến 4095)

void setup() {
  // Bắt đầu Serial để in ra dữ liệu
  Serial.begin(9600);
  
  // Cấu hình chân GPIO là chế độ đọc giá trị analog
  pinMode(potPin, INPUT);
}

void loop() {
  // Đọc giá trị từ biến trở (ADC)
  int adcValue = analogRead(potPin);

  // Tính toán giá trị điện áp từ giá trị ADC
  float voltage = (adcValue * voltageRef) / resolution;

  // In giá trị ADC và điện áp ra Serial
  Serial.print("Giá trị ADC: ");
  Serial.print(adcValue);
  Serial.print("\tĐiện áp: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Chờ 1 giây trước khi đọc giá trị tiếp theo
  delay(500);
}