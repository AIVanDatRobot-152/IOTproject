#define BLYNK_TEMPLATE_ID "TMPL6b31QHCWy"
#define BLYNK_TEMPLATE_NAME "FireFighting"
#define BLYNK_AUTH_TOKEN "unPQiF7ZLotvYq_YhISt9ivY_cKC-wKd"
#define BLYNK_PRINT Serial

#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "HUTECH";
char pass[] = "hutech@123";
char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

// Định nghĩa chân và loại cảm biến
#define DHTPIN 16       // Chân G16 nối với DHT11
#define DHTTYPE DHT11   // Định nghĩa loại cảm biến là DHT11
#define LED_PIN 2       // Chân G2 nối với LED
#define MQ2_PIN 32      // Chân G32 nối với MQ2

// Khởi tạo cảm biến DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(MQ2_PIN, INPUT);

  // Kết nối với WiFi và Blynk
  Blynk.begin(auth, ssid, pass);

  // Thiết lập bộ đếm thời gian để cập nhật giá trị mỗi giây
  timer.setInterval(1000L, sendSensorData);
}

void sendSensorData() {
  float temperature = dht.readTemperature();
  int mq2Value = analogRead(MQ2_PIN);

  // Kiểm tra lỗi khi đọc cảm biến DHT11
  if (isnan(temperature)) {
    Serial.println("Lỗi đọc dữ liệu từ cảm biến DHT11!");
  } else {
    Serial.print("Nhiệt độ: ");
    Serial.print(temperature);
    Serial.println("°C");

    Blynk.virtualWrite(V0, temperature); // Gửi nhiệt độ lên Blynk (V0)
  }

  // Đọc giá trị nồng độ khói từ MQ2
  Serial.print("Nồng độ khói (MQ2): ");
  Serial.println(mq2Value);

  Blynk.virtualWrite(V1, mq2Value); // Gửi nồng độ khói lên Blynk (V1)

  // Điều khiển LED và cập nhật trạng thái LED trên Blynk (V3)
  if (temperature > 30) {
    digitalWrite(LED_PIN, HIGH);
    Blynk.virtualWrite(V3, 1);  // LED sáng trên Blynk (V3)
  } else {
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V3, 0);  // LED tắt trên Blynk (V3)
  }
}

void loop() {
  Blynk.run();
  timer.run(); // Chạy bộ đếm thời gian
}
