#include <WiFi.h>
const char *password = "11113333";
IPAddress local_IP(192, 168, 113, 10);
IPAddress gateway(192, 168, 101, 0);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  Serial.print("Configuring access point...");
  char ssid[64];
  sprintf(ssid, "ESP32-Dat", ESP.getChipModel());
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  WiFi.softAPConfig(local_IP, gateway, subnet);
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}

void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}