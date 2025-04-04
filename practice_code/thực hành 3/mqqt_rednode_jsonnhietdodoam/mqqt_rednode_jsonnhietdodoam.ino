#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "HUTECH";
const char* password = "hutech@123";
const char* mqtt_server = "7c7482dac8184141b3fff5dc15c518db.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "VanDat";  // User
const char* mqtt_password = "MqqtDat1502";  // Password

WiFiClientSecure espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (100)
char msg[MSG_BUFFER_SIZE];
int value = 0;

// Topic duy nhất để gửi dữ liệu dạng JSON
const char* topic = "NguyenVanDat_2286300010/sensorData";

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
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(topic);  // Đăng ký nhận thông tin từ topic này
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
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

    // Tạo giá trị ngẫu nhiên cho nhiệt độ và độ ẩm
    int temperature = random(20, 30);  // Nhiệt độ ngẫu nhiên từ 20°C đến 30°C
    int humidity = random(40, 60);     // Độ ẩm ngẫu nhiên từ 40% đến 60%

    // Tạo chuỗi JSON
    String payload = "{";
    payload += "\"temperature\":";
    payload += String(temperature);
    payload += ", \"humidity\":";
    payload += String(humidity);
    payload += "}";

    // Chuyển đổi chuỗi JSON sang kiểu char* và gửi lên MQTT Broker
    payload.toCharArray(msg, MSG_BUFFER_SIZE);
    Serial.print("Gửi dữ liệu JSON: ");
    Serial.println(msg);
    client.publish(topic, msg);
  }
}
