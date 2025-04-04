#define BLYNK_TEMPLATE_ID "TMPL6TDS1Gzm3"
#define BLYNK_TEMPLATE_NAME "battat2den"
#define BLYNK_AUTH_TOKEN "dt0t41PJAHZDdE0MO31wVjkS6p96TmXx"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> // Thư viện ArduinoJson

char ssid[] = "HUTECH";
char pass[] = "hutech@123";
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;

// Định nghĩa các chân cho đèn LED
#define LED1 2   // Chân G2
#define LED2 17  // Chân G17

// Điều khiển bật/tắt LED1 bằng công tắc (Blynk V0)
BLYNK_WRITE(V0) {
  bool switchState = param.asInt();
  digitalWrite(LED1, switchState);
  Serial.println("LED1 State: " + String(switchState ? "ON" : "OFF"));
}

// Điều khiển độ sáng của LED2 (Blynk V1)
BLYNK_WRITE(V1) {
  int brightness = param.asInt();  // Giá trị từ 0 đến 255
  Serial.println("LED2 Brightness: " + String(brightness));
  analogWrite(LED2, brightness);
}

// Hiển thị thông tin thời tiết qua nhãn (V2)
void getWeather() {
  HTTPClient http;
  String host = "https://api.openweathermap.org/data/2.5/weather?lat=10.802824761923334&lon=106.71526191534544&appid=357576f6abab4c87f8fb8608b91768a2";
  
  http.begin(host);  
  int httpCode = http.GET();  

  if (httpCode == HTTP_CODE_OK) {  
    String payload = http.getString();  
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);
    if (!error) {
      const char* mainWeather = doc["weather"][0]["main"];
      Blynk.virtualWrite(V2, String(mainWeather));  // Hiển thị thông tin thời tiết lên nhãn
      Serial.println("Weather: " + String(mainWeather));
    }
  } else {
    Serial.println("HTTP Error: " + String(httpCode));
  }
  http.end();
}

void setup() {
  // Khởi tạo Serial
  Serial.begin(115200);
  delay(1000);
  
  // Kết nối WiFi và Blynk
  Blynk.begin(auth, ssid, pass);
  
  // Thiết lập chế độ cho các chân LED
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Chạy hàm getWeather mỗi 5 giây
  timer.setInterval(5000L, getWeather);
}

void loop() {
  Blynk.run();
  timer.run();
}
