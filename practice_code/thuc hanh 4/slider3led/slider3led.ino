#define BLYNK_TEMPLATE_ID "TMPL6TDS1Gzm3"
#define BLYNK_TEMPLATE_NAME "battat3den"
#define BLYNK_AUTH_TOKEN "dt0t41PJAHZDdE0MO31wVjkS6p96TmXx"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "HUTECH";
char pass[] = "hutech@123";
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;

// Định nghĩa các chân cho đèn LED
#define LED1 2   // Chân G2
#define LED2 17  // Chân G17
#define LED3 18  // Chân G18

// Điều khiển độ sáng của LED1 (Blynk V2)
BLYNK_WRITE(V0) {
  int brightness = param.asInt();  // Giá trị từ 0 đến 255
  Serial.println("LED1 Brightness: " + String(brightness));
  analogWrite(LED1, brightness);
}

// Điều khiển độ sáng của LED2 (Blynk V1)
BLYNK_WRITE(V1) {
  int brightness = param.asInt();  // Giá trị từ 0 đến 255
  Serial.println("LED2 Brightness: " + String(brightness));
  analogWrite(LED2, brightness);
}

// Điều khiển độ sáng của LED3 (Blynk V0)
BLYNK_WRITE(V2) {
  int brightness = param.asInt();  // Giá trị từ 0 đến 255
  Serial.println("LED3 Brightness: " + String(brightness));
  analogWrite(LED3, brightness);
}

void setup() {
  // Debug console
  Serial.begin(115200);
  delay(1000);
  Blynk.begin(auth, ssid, pass);
  
  // Thiết lập chế độ cho các chân LED
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run();
}
