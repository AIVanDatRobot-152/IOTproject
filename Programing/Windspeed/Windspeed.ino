#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "HUTECH";
const char* password = "hutech@123";
const char* host = "https://api.openweathermap.org/data/2.5/weather?q=Saigon&appid=cdd74a0a46da43cecd0aaf5442ae3801";

void getWeather() {
  HTTPClient http;
  http.begin(host);
  int httpCode = http.GET();
  Serial.println(httpCode);
  if (httpCode == 200) {
    String payload = http.getString();
    Serial.println(payload);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);
    float wind = doc["wind"]["speed"];
    Serial.print("Wind Speed: ");
    Serial.print(wind);
  }
  http.end();
}

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
void loop() {
  getWeather();
  delay(3000);
}