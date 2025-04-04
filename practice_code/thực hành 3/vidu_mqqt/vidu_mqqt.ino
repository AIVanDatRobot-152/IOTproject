#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
const char* ssid = "HUTECH";
const char* password = "hutech@123";
const char* mqtt_server =
  "7c7482dac8184141b3fff5dc15c518db.s1.eu.hivemq.cloud";
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
  if ((char)payload[0] == '0') {
    digitalWrite(BUILTIN_LED, LOW);
  } else if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_username,
                       mqtt_password)) {
      Serial.println("connected");
      client.publish("myOutTopic", "Hello World #");
      client.subscribe("myInTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);  // Initialize the BUILTIN_LEDpin as an output
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
    value = 100 + random(100);
    snprintf(msg, MSG_BUFFER_SIZE, "Gimme Gimme Love Dat :333  #%ld", value);
    Serial.print("Đang đẩy tin nhắn lên: ");
    Serial.println(msg);
    client.publish("myOutTopic", msg);
  }
}