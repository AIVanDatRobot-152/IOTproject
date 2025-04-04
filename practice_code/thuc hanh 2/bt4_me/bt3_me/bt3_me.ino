#include <WiFi.h>
#include <HTTPClient.h>

// Thông tin Wi-Fi
const char* ssid = "HUTECH";          // Thay bằng SSID Wi-Fi của bạn
const char* password = "hutech@123";  // Thay bằng mật khẩu Wi-Fi của bạn

// OpenWeatherMap API key và URL
const String apiUrl = "http://192.168.1.18:3000/robots/1";

void setup() {
  Serial.begin(115200);  // Khởi tạo Serial

  // Kết nối Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Đang kết nối với Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("\nĐã kết nối thành công với Wi-Fi!");
  Serial.print("Địa chỉ IP: ");
  Serial.println(WiFi.localIP());

  // Đọc dữ liệu thời tiết từ API
  getWeatherData();
}

void loop() {
  // Không làm gì trong loop
}

void getWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {  // Kiểm tra xem ESP32 có kết nối Wi-Fi không
    HTTPClient http;

    http.begin(apiUrl);  // Khởi tạo kết nối HTTP
    int httpCode = http.GET();  // Gửi yêu cầu GET

    if (httpCode > 0) {  // Kiểm tra mã phản hồi HTTP
      String payload = http.getString();  // Nhận phản hồi từ server
      Serial.println("Phản hồi từ API:");
      Serial.println(payload);  // In toàn bộ dữ liệu JSON ra màn hình Serial
    } else {
      Serial.println("Lỗi khi gửi yêu cầu GET");
    }

    http.end();  // Kết thúc kết nối HTTP
  } else {
    Serial.println("Chưa kết nối Wi-Fi");
  }
}