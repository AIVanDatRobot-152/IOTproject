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
      client.publish("myOutTopic", "Hello World #");
      client.subscribe("NguyenVanDat_2286300010/temperature");  // Chủ đề nhiệt độ
      client.subscribe("NguyenVanDat_2286300010/humidity");     // Chủ đề độ ẩm
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
    int temperature = random(20, 30);  // Giá trị ngẫu nhiên cho nhiệt độ từ 20°C đến 30°C
    int humidity = random(40, 60);     // Giá trị ngẫu nhiên cho độ ẩm từ 40% đến 60%

    // Publish nhiệt độ với đơn vị °C
    snprintf(msg, MSG_BUFFER_SIZE, "%d°C", temperature);
    Serial.print("Đang đẩy nhiệt độ: ");
    Serial.println(msg);
    client.publish("NguyenVanDat_2286300010/temperature", msg);

    // Publish độ ẩm với đơn vị %
    snprintf(msg, MSG_BUFFER_SIZE, "%d%%", humidity);
    Serial.print("Đang đẩy độ ẩm: ");
    Serial.println(msg);
    client.publish("NguyenVanDat_2286300010/humidity", msg);
  }
}
