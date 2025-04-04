#include "DHT.h"

// Khai báo chân kết nối với cảm biến DHT11 và loại cảm biến
#define DHTPIN 15     // Chân kết nối DHT11 (giả sử chân GPIO 15)
#define DHTTYPE DHT11 // Định nghĩa loại cảm biến là DHT11

// Khởi tạo đối tượng DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Bắt đầu Serial để in ra dữ liệu
  Serial.begin(9600);

  // Khởi tạo cảm biến DHT
  dht.begin();
}

void loop() {
  // Đọc giá trị từ cảm biến DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Kiểm tra nếu việc đọc giá trị có lỗi
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Lỗi khi đọc từ cảm biến DHT11!");
  } else {
    // In giá trị nhiệt độ và độ ẩm lên Serial Monitor
    Serial.print("Nhiệt độ: ");
    Serial.print(temperature);
    Serial.print(" °C\t");
    Serial.print("Độ ẩm: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // Chờ 2 giây trước khi thực hiện lần đọc tiếp theo
  delay(2000);
}
