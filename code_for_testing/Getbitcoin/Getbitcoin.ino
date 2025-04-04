#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "HUTECH";
const char* password = "hutech@123";
const char* host = "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=USD";

void getBitCoin()
{
  HTTPClient http;
  http.begin(host);
  int httpCode = http.GET();
  Serial.println(httpCode);
  if (httpCode == 200)
  {
    String payload = http.getString();
    Serial.println(payload);
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
  getBitCoin();
  delay(3000);
}