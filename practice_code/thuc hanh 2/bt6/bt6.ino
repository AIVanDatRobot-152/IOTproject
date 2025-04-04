#include <WiFi.h>
#include <HTTPClient.h>

// Thông tin WiFi
const char* ssid = "IoT_101";
const char* password = "12345678";

// Địa chỉ host
const char* serverName = "http://192.168.0.115:3000/robots/1";

void setup() {
  Serial.begin(115200);

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  Serial.print("Đang kết nối với WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Kết nối WiFi thành công");

  // Tạo HTTP GET request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Gửi request đến server
    http.begin(serverName);
    int httpResponseCode = http.GET();

    // Kiểm tra phản hồi từ server
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("Phản hồi từ server:");
      Serial.println(payload);
    } else {
      Serial.print("Lỗi trong quá trình gửi yêu cầu. Mã lỗi: ");
      Serial.println(httpResponseCode);
    }

    // Kết thúc kết nối
    http.end();
  } else {
    Serial.println("Không thể kết nối đến WiFi");
  }
}

void loop() {
  // Không cần lặp trong ví dụ này
}