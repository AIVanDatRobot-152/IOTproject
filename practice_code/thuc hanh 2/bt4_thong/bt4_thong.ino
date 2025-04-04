#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "HUTECH";
const char* password = "hutech@123";
const char* host = "https://api.openweathermap.org/data/2.5/weather?q=Hue&appid=cdd74a0a46da43cecd0aaf5442ae3801";

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
    String weather = doc["weather"][0]["main"];
    float temp = doc["main"]["temp"];
    float humidity = doc["main"]["humidity"];
    Serial.print("Weather: ");
    Serial.print(weather);
    float doC = temp - 273;
    Serial.print(" | doC: ");
    Serial.print(doC);
    Serial.print(" | Humidity: ");
    Serial.println(humidity);
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