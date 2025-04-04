#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "HUTECH";
const char* password = "hutech@123";
const char* mqtt_server = "7c7482dac8184141b3fff5dc15c518db.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "VanDat";  //User
const char* mqtt_password = "MqqtDat1502";  //Password

WiFiClientSecure espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

// Chân điều khiển LED (phải là chân hỗ trợ PWM)
const int ledPin = 2;  // Chọn chân phù hợp để điều khiển độ sáng LED

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String payloadStr = "";

  for (int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];  // Lấy toàn bộ nội dung của payload
  }
  
  Serial.println(payloadStr);  // In chuỗi payload nhận được

  // Chuyển chuỗi payload thành số nguyên để điều chỉnh độ sáng LED
  int brightness = payloadStr.toInt(); 
  if (brightness >= 0 && brightness <= 255) {
    analogWrite(ledPin, brightness);  // Điều chỉnh độ sáng từ 0 đến 255
    Serial.print("Độ sáng LED: ");
    Serial.println(brightness);
  } else {
    Serial.println("Giá trị không hợp lệ");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.publish("myOutTopic", "Hello World #");
      client.subscribe("NguyenVanDat_2286300010/led");  // Chủ đề điều khiển LED
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);  // Khởi tạo chân LED là OUTPUT
  Serial.begin(115200);
  setup_wifi();
  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
  unsigned long now = millis();
  
  if (now - lastMsg > 2000) {
    lastMsg = now;
    value = random(0, 256);  // Tạo giá trị ngẫu nhiên từ 0 đến 255
    snprintf(msg, MSG_BUFFER_SIZE, "%ld", value);
    Serial.print("Đang đẩy tin nhắn lên: ");
    Serial.println(msg);
    client.publish("NguyenVanDat_2286300010/data", msg);  // Gửi dữ liệu ngẫu nhiên
  }
}
