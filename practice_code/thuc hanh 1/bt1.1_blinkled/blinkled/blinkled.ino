// Khai báo các chân kết nối LED
const int LED1 = 2; // GPIO 
const int LED2 = 16; // GPIO 
const int LED3 = 17; // GPIO 

void setup() {
  // Cấu hình các chân LED là OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Khởi động Serial để in trạng thái
  Serial.begin(115200);
}

void loop() {
  // Bật LED1 và in trạng thái
  digitalWrite(LED1, HIGH);
  Serial.println("LED1: ON");
  delay(100); // Đợi 1 giây

  // Tắt LED1 và in trạng thái
  digitalWrite(LED1, LOW);
  Serial.println("LED1: OFF");

  // Bật LED2 và in trạng thái
  digitalWrite(LED2, HIGH);
  Serial.println("LED2: ON");
  delay(100); // Đợi 1 giây

  // Tắt LED2 và in trạng thái
  digitalWrite(LED2, LOW);
  Serial.println("LED2: OFF");

  // Bật LED3 và in trạng thái
  digitalWrite(LED3, HIGH);
  Serial.println("LED3: ON");
  delay(100); // Đợi 1 giây

  // Tắt LED3 và in trạng thái
  digitalWrite(LED3, LOW);
  Serial.println("LED3: OFF");
}
