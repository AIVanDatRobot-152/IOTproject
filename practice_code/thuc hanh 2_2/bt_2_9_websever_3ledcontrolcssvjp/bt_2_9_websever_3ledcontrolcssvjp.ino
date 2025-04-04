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

// HTML và CSS cho trang chủ điều khiển đèn LED
const char *html =
  "<html>\
  <meta charset = \"utf-8\">\
  <head>\
    <title>Nguyễn Văn Đạt_2286300010 Leds control</title>\
    <style>\
      html {\
        font-family: Helvetica, Arial, sans-serif;\
        display: inline-block;\
        margin: 0 auto;\
        text-align: center;\
      }\
      body {\
        margin-top: 50px;\
      }\
      h1 {\
        color: #444;\
        margin: 50px auto 30px;\
      }\
      h3 {\
        color: #444;\
        margin-bottom: 50px;\
      }\
      .button {\
        display: block;\
        width: 80px;\
        background-color: #3498db;\
        border: none;\
        color: white;\
        padding: 13px 30px;\
        text-decoration: none;\
        font-size: 25px;\
        margin: 0 auto 35px;\
        cursor: pointer;\
        border-radius: 4px;\
        transition: background-color 0.3s;\
      }\
      .button-on {\
        background-color: #3498db;\
      }\
      .button-on:active {\
        background-color: #2980b9;\
      }\
      .button-off {\
        background-color: #34495e;\
      }\
      .button-off:active {\
        background-color: #2c3e50;\
      }\
      p {\
        font-size: 14px;\
        color: #888;\
        margin-bottom: 10px;\
      }\
    </style>\
  </head>\
  <body>\
    <h1>LED Control</h1>\
    <a class=\"button button-on\" href=\"/led1on\">LED 1 ON</a>\
    <a class=\"button button-off\" href=\"/led1off\">LED 1 OFF</a>\
    <a class=\"button button-on\" href=\"/led2on\">LED 2 ON</a>\
    <a class=\"button button-off\" href=\"/led2off\">LED 2 OFF</a>\
    <a class=\"button button-on\" href=\"/led3on\">LED 3 ON</a>\
    <a class=\"button button-off\" href=\"/led3off\">LED 3 OFF</a>\
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
