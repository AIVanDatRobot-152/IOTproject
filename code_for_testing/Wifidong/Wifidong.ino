#include <WiFi.h>

const char* ssid = "IoT_101";

const char* password = "12345678";

void setup() {

  Serial.begin(115200);

  delay(10);

  Serial.print("Connecting to ");

  Serial.println(ssid);

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

void loop() {}