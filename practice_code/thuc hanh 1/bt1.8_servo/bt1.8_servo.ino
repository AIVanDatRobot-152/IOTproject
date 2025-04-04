#include <ESP32Servo.h>  // Thư viện ESP32Servo cho ESP32

Servo myServo;  // Tạo đối tượng Servo

const int servoPin = 4;  // Chân GPIO 4 để kết nối với Servo
int angle = 0;           // Góc hiện tại của Servo
int step = 10;            // Bước thay đổi góc

void setup() {
  // Khởi tạo Serial Monitor
  Serial.begin(9600);

  // Gắn chân servo vào đối tượng Servo
  myServo.attach(servoPin);

  // Đưa servo về vị trí 0 độ ban đầu
  myServo.write(0);
  Serial.println("Servo bắt đầu ở góc 0 độ");
  delay(1000);  // Đợi 1 giây để đảm bảo servo về góc 0 độ trước khi tiếp tục
}

void loop() {
  // Quay Servo từ 0 đến 180 độ
  myServo.write(angle);
  Serial.print("Góc Servo: ");
  Serial.println(angle);

  // Thay đổi góc quay Servo
  angle += step;

  // Nếu Servo đạt tới 180 độ hoặc 0 độ, đảo chiều thay đổi góc
  if (angle >= 180|| angle <= 0) {
    step = -step;  // Đảo chiều góc quay
  }

  // Chờ 20ms giữa mỗi lần thay đổi góc để Servo quay từ từ
  delay(20);
}
