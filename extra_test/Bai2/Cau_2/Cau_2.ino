#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>  // Thư viện ArduinoJson https://github.com/bblanchon/ArduinoJson

// Thông tin kết nối WiFi
const char* ssid = "HUTECH";           // Thay bằng SSID mạng của bạn
const char* password = "hutech@123";    // Thay bằng mật khẩu mạng của bạn

// URL API của OpenWeatherMap
const char* host = "https://api.openweathermap.org/data/2.5/weather?lat=10.802824761923334&lon=106.71526191534544&appid=357576f6abab4c87f8fb8608b91768a2";

void getWeather() {
  HTTPClient http;
  Serial.print("Đang kết nối tới: ");
  Serial.println(host);

  http.begin(host);  // Thiết lập kết nối HTTP
  int httpCode = http.GET();  // Gửi yêu cầu GET

  if (httpCode == HTTP_CODE_OK) {  // Nếu kết nối thành công
    String payload = http.getString();  // Nhận dữ liệu JSON từ API
    Serial.println(payload);  // In toàn bộ dữ liệu nhận được ra Serial

    // Khởi tạo đối tượng JSON document để chứa dữ liệu
    DynamicJsonDocument doc(1024);
    
    // Phân tích chuỗi JSON thành đối tượng JSON
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    // Truy xuất các thông tin cần thiết từ JSON
    float lon = doc["coord"]["lon"];
    float lat = doc["coord"]["lat"];
    const char* mainWeather = doc["weather"][0]["main"];
    // In các thông tin ra Serial
    Serial.println("Thông tin thời tiết thành phố Saigon:");
    Serial.print("Tọa độ: ");
    Serial.print("Longitude: "); Serial.print(lon);
    Serial.print(", Latitude: "); Serial.println(lat);
    Serial.print("Thời tiết: "); Serial.println(mainWeather);
  } else {
    Serial.print("Lỗi kết nối HTTP: ");
    Serial.println(httpCode);  // In mã lỗi nếu không kết nối được
  }
  http.end();  // Kết thúc kết nối HTTP
}

void setup() {
  Serial.begin(115200);  // Khởi tạo Serial để debug
  WiFi.begin(ssid, password);  // Kết nối WiFi

  Serial.print("Đang kết nối WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nKết nối WiFi thành công!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    getWeather();  // Gọi hàm lấy dữ liệu thời tiết
  }
  delay(5000);  // Gửi yêu cầu lại sau 60 giây
}
