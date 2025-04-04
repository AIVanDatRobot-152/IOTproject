#include <WiFi.h> // Thư viện WiFi cho ESP32

// Khai báo thông tin WiFi
const char* ssid = "GS25 Friendly Fresh Fun";

// Cấu hình địa chỉ IP tĩnh
IPAddress local_IP(192, 168, 0, 10); // Địa chỉ IP tĩnh
IPAddress gateway(192, 168, 0, 1);   // Gateway
IPAddress subnet(255, 255, 255, 0);  // Subnet mask

void setup() {
  // Khởi tạo cổng Serial để debug
  Serial.begin(115200);

  // Thiết lập IP tĩnh trước khi kết nối
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Thiết lập địa chỉ IP tĩnh thất bại!");
  }

  // Kết nối WiFi
  Serial.println("Đang kết nối tới WiFi...");
  WiFi.begin(ssid);

  // Chờ cho đến khi kết nối thành công
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Khi kết nối thành công
  Serial.println("");
  Serial.println("Kết nối thành công!");
  Serial.print("Địa chỉ IP của ESP32: ");
  Serial.println(WiFi.localIP()); // In ra địa chỉ IP tĩnh
}

void loop() {
  // Chương trình chính
}
