#include <WiFi.h> // Thư viện WiFi cho ESP32

// Khai báo thông tin WiFi
const char* ssid = "HUTECH";
const char* password = "hutech@123";

void setup() {
  // Khởi tạo cổng Serial để debug
  Serial.begin(115200);
  
  // Bắt đầu kết nối WiFi
  Serial.println("Đang kết nối tới WiFi...");
  WiFi.begin(ssid, password);
  
  // Chờ cho đến khi kết nối thành công
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  // Khi kết nối thành công
  Serial.println("");
  Serial.println("Kết nối thành công!");
  Serial.print("Địa chỉ IP của ESP32: ");
  Serial.println(WiFi.localIP()); // In ra địa chỉ IP nhận được từ DHCP
}

void loop() {
  // Chương trình chính có thể đặt ở đây
}
