// ESP8266_LED_subscribe.ino
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "BDU-Hostel2";
const char* password = "dhaka1213";
const char* broker = "172.16.114.108";

#define LED_PIN D5

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (unsigned int i=0;i<length;i++) msg += (char)payload[i];
  msg.trim();
  Serial.print("Got: ");
  Serial.println(msg);
  if (msg == "ON") digitalWrite(LED_PIN, HIGH);
  else digitalWrite(LED_PIN, LOW);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266_LED")) {
      client.subscribe("iot/esp8266/led");
      Serial.println("Subscribed to iot/esp8266/led");
    } else {
      delay(500);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  WiFi.begin(ssid, password);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.println("\nWiFi connected: " + WiFi.localIP().toString());
  client.setServer(broker, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
