#include <DHT.h>

// Định nghĩa chân và loại cảm biến
#define DHTPIN 16       // Chân G16 nối với DHT11
#define DHTTYPE DHT11   // Định nghĩa loại cảm biến là DHT11
#define LED_PIN 2       // Chân G2 nối với LED
#define MQ2_PIN 32      // Chân G18 nối với MQ2

// Khởi tạo cảm biến DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Cài đặt chế độ cho LED và chân analog cho MQ2
  pinMode(LED_PIN, OUTPUT);
  pinMode(MQ2_PIN, INPUT);
}

void loop() {
  // Đọc giá trị nhiệt độ và độ ẩm từ DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Đọc giá trị từ cảm biến MQ2 (nồng độ khói)
  int mq2Value = analogRead(MQ2_PIN);

  // Kiểm tra xem có lỗi khi đọc giá trị từ DHT11 không
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Lỗi đọc dữ liệu từ cảm biến DHT11!");
  } else {
    // In ra giá trị nhiệt độ và độ ẩm
    Serial.print("Nhiệt độ: ");
    Serial.print(temperature);
    Serial.println("°C");

    Serial.print("Độ ẩm: ");
    Serial.print(humidity);
    Serial.println("%");
  }

  // Kiểm tra giá trị MQ2 và in ra console
  if (mq2Value > 0) {
    Serial.print("Nồng độ khói (MQ2): ");
    Serial.println(mq2Value);
  } else {
    Serial.println("Không đọc được giá trị khói, kiểm tra cảm biến.");
  }

  // Điều khiển LED bật khi nhiệt độ > 29.5 độ C
  if (temperature > 29.5) {
    digitalWrite(LED_PIN, HIGH); // Bật LED
  } else {
    digitalWrite(LED_PIN, LOW);  // Tắt LED
  }

  delay(1000); // Đợi 1 giây trước khi đọc lại
}
