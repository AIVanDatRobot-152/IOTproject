
#define DHTPIN 16    // Chân G16 cho DHT11
#define DHTTYPE DHT11  // Loại cảm biến DHT11

DHT dht(DHTPIN, DHTTYPE);

// Hàm đọc và gửi dữ liệu nhiệt độ và độ ẩm lên Blynk
void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Nhiệt độ bằng độ C

  if (isnan(h) || isnan(t)) {
    Serial.println("Lỗi đọc dữ liệu từ cảm biến DHT11!");
    return;
  }

  // Hiển thị dữ liệu lên serial
  Serial.print("Nhiệt độ: ");
  Serial.print(t);
  Serial.print(" °C, Độ ẩm: ");
  Serial.print(h);
  Serial.println(" %");

  // Gửi dữ liệu lên Blynk
  Blynk.virtualWrite(V1, t);  // Gửi nhiệt độ đến Blynk V1
  Blynk.virtualWrite(V2, h);  // Gửi độ ẩm đến Blynk V2
}

void setup() {
  // Debug console
  Serial.begin(115200);
  delay(1000);

  // Kết nối Blynk
  Blynk.begin(auth, ssid, pass);
  
  // Khởi động cảm biến DHT11
  dht.begin();

  // Đặt timer để đọc dữ liệu mỗi 2 giây
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
