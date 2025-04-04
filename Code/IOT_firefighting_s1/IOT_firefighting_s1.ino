#define BLYNK_TEMPLATE_ID "TMPL6qsfW-Ns6"
#define BLYNK_TEMPLATE_NAME "FireWarning" 
#define BLYNK_AUTH_TOKEN "6O4lZLpJ2eNzCJX8D9eLT5ZbuMDcGXvb"
#define BLYNK_PRINT Serial

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "minmean";
char pass[] = "12345678";
char auth[] = BLYNK_AUTH_TOKEN; 

#define DHTPIN 16       // Chân G16 nối với DHT11
#define DHTTYPE DHT11   // Định nghĩa loại cảm biến là DHT11
#define LED_PIN 2       // Chân G2 nối với LED
#define MQ2_PIN 32      // Chân G32 nối với MQ2

BlynkTimer timer;

// Khởi tạo cảm biến DHT
DHT dht(DHTPIN, DHTTYPE);

// Khởi tạo LCD với địa chỉ I2C là 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(MQ2_PIN, INPUT);

  // Khởi tạo LCD
  lcd.init();
  lcd.backlight();

  // Kết nối với WiFi và Blynk
  Blynk.begin(auth, ssid, pass);

  // Thiết lập timer để gửi dữ liệu cảm biến lên Blynk mỗi giây
  timer.setInterval(1000L, sendSensorData);
}

void sendSensorData() {
  float temperature = dht.readTemperature();
  int mq2Value = analogRead(MQ2_PIN);

  // Kiểm tra lỗi khi đọc cảm biến DHT11
  if (isnan(temperature)) {
    Serial.println("Lỗi đọc dữ liệu từ cảm biến DHT11!");
    lcd.setCursor(0, 0);
    lcd.print("DHT11 Error     ");
  } else {
    // Gửi nhiệt độ lên Blynk (Virtual Pin V0)
    Blynk.virtualWrite(V0, temperature);

    // Hiển thị nhiệt độ trên Serial và LCD
    Serial.print("Nhiệt độ: ");
    Serial.print(temperature);
    Serial.println("°C");

    lcd.setCursor(0, 0);
    lcd.print("Nhiet do: ");
    lcd.print(temperature);
    lcd.print(" C   ");
  }

  // Gửi giá trị nồng độ khói lên Blynk (Virtual Pin V1)
  Blynk.virtualWrite(V1, mq2Value);

  // Hiển thị giá trị nồng độ khói trên Serial và LCD
  Serial.print("Nồng độ khói (MQ2): ");
  Serial.println(mq2Value);

  lcd.setCursor(0, 1);
  lcd.print("Khoi: ");
  lcd.print(mq2Value);
  lcd.print("     ");

  // Điều khiển LED theo nhiệt độ và gửi trạng thái LED lên Blynk (Virtual Pin V4)
  if (temperature > 30) {
    digitalWrite(LED_PIN, HIGH);  // Bật LED nếu nhiệt độ trên 30°C
    Blynk.virtualWrite(V4, 1);    // Gửi trạng thái LED là "1" (bật) lên Blynk
  } else {
    digitalWrite(LED_PIN, LOW);   // Tắt LED nếu nhiệt độ dưới 30°C
    Blynk.virtualWrite(V4, 0);    // Gửi trạng thái LED là "0" (tắt) lên Blynk
  }
}

void loop() {
  Blynk.run();
  timer.run();  // Chạy timer cho Blynk
}
