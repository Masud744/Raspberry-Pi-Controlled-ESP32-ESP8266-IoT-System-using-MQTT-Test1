// ESP32_HC-SR04_publish.ino
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "BDU-Hostel2";
const char* password = "dhaka1213";
const char* broker = "172.16.114.108";

#define TRIG_PIN 14   // change if you wired differently
#define ECHO_PIN 27   // after voltage divider
#define MAX_CM 400

WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("WiFi connecting");
  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
    if (millis() - t0 > 20000) { Serial.println("\nWiFi timeout"); break;}
  }
  Serial.println("\nWiFi IP: " + WiFi.localIP().toString());
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("MQTT connecting...");
    if (client.connect("ESP32_ultra")) {
      Serial.println("connected");
    } else {
      Serial.print("failed:"); Serial.print(client.state());
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  setupWiFi();
  client.setServer(broker, 1883);
}

unsigned long measureDistanceCm() {
  // send trigger 10us pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // wait for echo (timeout 30ms -> ~10m)
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL); // microseconds
  if (duration == 0) return 9999; // no echo
  unsigned long cm = duration / 58; // speed of sound approx
  if (cm > MAX_CM) return 9999;
  return cm;
}

void loop() {
  if (!client.connected()) reconnectMQTT();
  client.loop();

  unsigned long cm = measureDistanceCm();
  char buf[8];
  sprintf(buf, "%lu", cm);
  client.publish("iot/esp32/distance", buf);
  Serial.print("Distance: "); Serial.println(buf);

  delay(500); // publish interval
}
