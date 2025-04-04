#include <WiFi.h>
#include <WebServer.h>

const char *password = "11112222";

// Khai báo các chân đèn LED
const int led1 = 4;
const int led2 = 2;
const int led3 = 15;

// Trạng thái các đèn LED
bool led1_status = LOW;
bool led2_status = LOW;
bool led3_status = LOW;

// HTML cho trang chủ điều khiển đèn LED
const char *html =
  "<html>\
  <head>\
    <title>Nguyễn Văn Đạt _ MSSV 10 Leds Control</title>\
  </head>\
  <body>\
    <h1>LED Control</h1>\
    <a href=\"/led1on\">LED 1 ON</a><br>\
    <a href=\"/led1off\">LED 1 OFF</a><br>\
    <a href=\"/led2on\">LED 2 ON</a><br>\
    <a href=\"/led2off\">LED 2 OFF</a><br>\
    <a href=\"/led3on\">LED 3 ON</a><br>\
    <a href=\"/led3off\">LED 3 OFF</a><br>\
  </body>\
</html>";

IPAddress local_IP(192, 168, 113, 10);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

// Xử lý bật/tắt các LED
void handleLED1On() {
  led1_status = HIGH;
  Serial.println("LED 1: ON");
  handleRoot();
}

void handleLED1Off() {
  led1_status = LOW;
  Serial.println("LED 1: OFF");
  handleRoot();
}

void handleLED2On() {
  led2_status = HIGH;
  Serial.println("LED 2: ON");
  handleRoot();
}

void handleLED2Off() {
  led2_status = LOW;
  Serial.println("LED 2: OFF");
  handleRoot();
}

void handleLED3On() {
  led3_status = HIGH;
  Serial.println("LED 3: ON");
  handleRoot();
}

void handleLED3Off() {
  led3_status = LOW;
  Serial.println("LED 3: OFF");
  handleRoot();
}

// Xử lý trang chủ (homepage)
void handleRoot() {
  server.send(200, "text/html", html);
}

// Xử lý khi không tìm thấy route
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

void setup() {
  // Cài đặt chân LED là OUTPUT
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Thiết lập ban đầu cho các đèn LED (Tắt)
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  Serial.begin(115200);
  Serial.print("Configuring access point...");
  
  // Cài đặt SSID cho AP
  char ssid[64];
  sprintf(ssid, "ESP32-VanDat", ESP.getChipModel());
  WiFi.softAP(ssid, password);
  
  WiFi.softAPConfig(local_IP, gateway, subnet);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Đăng ký các route
  server.on("/", handleRoot);
  server.on("/led1on", handleLED1On);
  server.on("/led1off", handleLED1Off);
  server.on("/led2on", handleLED2On);
  server.on("/led2off", handleLED2Off);
  server.on("/led3on", handleLED3On);
  server.on("/led3off", handleLED3Off);
  server.onNotFound(handle_NotFound);
  
  // Bắt đầu server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();

  // Điều khiển đèn LED theo trạng thái
  digitalWrite(led1, led1_status);
  digitalWrite(led2, led2_status);
  digitalWrite(led3, led3_status);
}
