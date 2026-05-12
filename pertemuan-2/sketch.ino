/*
 * PRAKTIKUM IoT - PERTEMUAN 2
 * MQTT, Telemetry, dan Remote Control
 * Studi kasus: Smart Classroom Monitor + IoT Network
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

const char *KELAS = "pararel_B";
const char *KELOMPOK = "kelompok01";
const char *LOKASI = "twintowerB_lantai7_706";

const char *WIFI_SSID = "Wokwi-GUEST";
const char *WIFI_PASSWORD = "";

const char *MQTT_SERVER = "broker.hivemq.com";
const int MQTT_PORT = 1883;

char TOPIC_TELEMETRY[100];
char TOPIC_CONTROL[100];
char DEVICE_ID[50];

const int DHT_PIN = 15;
const int LED_MERAH = 2;
const int LED_HIJAU = 5;
const int BUZZER_PIN = 4;

const float BATAS_SUHU = 28.0;
const float BATAS_KELEMBAPAN = 75.0;

DHTesp dhtSensor;
WiFiClient espClient;
PubSubClient mqttClient(espClient);

enum ModeSistem { MODE_AUTO, MODE_MANUAL };
ModeSistem modeSistem = MODE_AUTO;

unsigned long lastPublish = 0;
unsigned long publishInterval = 5000;
int sampleNo = 0;

enum StatusSistem {
  NORMAL,
  WARNING_SUHU,
  WARNING_KELEMBAPAN,
  WARNING_GANDA
};

StatusSistem tentukanStatus(float suhu, float kelembapan) {
  bool suhuWarning = suhu > BATAS_SUHU;
  bool kelembapanWarning = kelembapan > BATAS_KELEMBAPAN;

  if (suhuWarning && kelembapanWarning) return WARNING_GANDA;
  if (suhuWarning) return WARNING_SUHU;
  if (kelembapanWarning) return WARNING_KELEMBAPAN;
  return NORMAL;
}

const char *statusStr(StatusSistem status) {
  switch (status) {
    case WARNING_SUHU:
      return "WARNING_SUHU";
    case WARNING_KELEMBAPAN:
      return "WARNING_KELEMBAPAN";
    case WARNING_GANDA:
      return "WARNING_GANDA";
    default:
      return "NORMAL";
  }
}

const char *warningReason(StatusSistem status) {
  switch (status) {
    case WARNING_SUHU:
      return "suhu_melebihi_batas";
    case WARNING_KELEMBAPAN:
      return "kelembapan_melebihi_batas";
    case WARNING_GANDA:
      return "suhu_dan_kelembapan_melebihi_batas";
    default:
      return "none";
  }
}

void kendalikanAktuatorAuto(StatusSistem status) {
  if (modeSistem == MODE_MANUAL) {
    return;
  }

  if (status == NORMAL) {
    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(LED_MERAH, LOW);
    noTone(BUZZER_PIN);
    return;
  }

  digitalWrite(LED_MERAH, HIGH);
  digitalWrite(LED_HIJAU, LOW);

  if (status == WARNING_SUHU) {
    tone(BUZZER_PIN, 1000);
  } else if (status == WARNING_KELEMBAPAN) {
    tone(BUZZER_PIN, 1200);
  } else if (status == WARNING_GANDA) {
    tone(BUZZER_PIN, 1500);
  }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  String pesan = "";

  for (unsigned int i = 0; i < length; i++) {
    pesan += static_cast<char>(payload[i]);
  }

  pesan.trim();

  Serial.print("[MQTT-CONTROL] Topic: ");
  Serial.println(topic);
  Serial.print("[MQTT-CONTROL] Pesan diterima: ");
  Serial.println(pesan);

  if (pesan == "LED_ON") {
    digitalWrite(LED_MERAH, HIGH);
    Serial.println("  -> LED Merah ON");
  } else if (pesan == "LED_OFF") {
    digitalWrite(LED_MERAH, LOW);
    Serial.println("  -> LED Merah OFF");
  } else if (pesan == "BUZZER_ON") {
    tone(BUZZER_PIN, 1200);
    Serial.println("  -> Buzzer ON (1200Hz)");
  } else if (pesan == "BUZZER_OFF") {
    noTone(BUZZER_PIN);
    Serial.println("  -> Buzzer OFF");
  } else if (pesan == "AUTO") {
    modeSistem = MODE_AUTO;
    Serial.println("  -> Mode: AUTO");
  } else if (pesan == "MANUAL") {
    modeSistem = MODE_MANUAL;
    Serial.println("  -> Mode: MANUAL");
  } else if (pesan == "RESET_ALARM") {
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);
    noTone(BUZZER_PIN);
    modeSistem = MODE_AUTO;
    Serial.println("  -> RESET_ALARM: aktuator reset, mode AUTO");
  } else {
    Serial.print("  -> Perintah tidak dikenal: ");
    Serial.println(pesan);
  }
}

void connectWiFi() {
  Serial.print("[WiFi] Menghubungkan ke ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 6);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempt++;

    if (attempt > 30) {
      Serial.println();
      Serial.println("[WiFi] GAGAL terhubung! Restart ESP32...");
      ESP.restart();
    }
  }

  Serial.println();
  Serial.println("[WiFi] Terhubung!");
  Serial.print("[WiFi] IP Address: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  int mqttAttempt = 0;

  while (!mqttClient.connected()) {
    mqttAttempt++;
    String clientId = String(DEVICE_ID) + "-" + String(random(0xffff), HEX);

    Serial.print("[MQTT] Koneksi percobaan ke-");
    Serial.print(mqttAttempt);
    Serial.print(" sebagai: ");
    Serial.println(clientId);

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("[MQTT] Terhubung ke broker!");
      mqttClient.subscribe(TOPIC_CONTROL);
      Serial.print("[MQTT] Subscribe ke: ");
      Serial.println(TOPIC_CONTROL);
    } else {
      Serial.print("[MQTT] Gagal, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" - coba lagi 3 detik...");

      if (mqttAttempt >= 5) {
        Serial.println("[MQTT] Terlalu banyak gagal, periksa koneksi internet.");
        break;
      }

      delay(3000);
    }
  }
}

void publishTelemetry() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("[ERROR] Gagal membaca DHT22!");
    return;
  }

  sampleNo++;

  StatusSistem status = tentukanStatus(data.temperature, data.humidity);
  kendalikanAktuatorAuto(status);

  char payload[350];
  snprintf(
      payload, sizeof(payload),
      "{"
      "\"device_id\":\"%s\","
      "\"temperature\":%.2f,"
      "\"humidity\":%.2f,"
      "\"status\":\"%s\","
      "\"warning_reason\":\"%s\","
      "\"location\":\"%s\","
      "\"sample_no\":%d,"
      "\"mode\":\"%s\","
      "\"uptime_ms\":%lu"
      "}",
      DEVICE_ID, data.temperature, data.humidity, statusStr(status),
      warningReason(status), LOKASI, sampleNo,
      (modeSistem == MODE_AUTO ? "AUTO" : "MANUAL"), millis());

  bool berhasil = mqttClient.publish(TOPIC_TELEMETRY, payload);

  Serial.print("[MQTT-PUB] Sample #");
  Serial.print(sampleNo);
  Serial.print(" | Suhu: ");
  Serial.print(data.temperature, 1);
  Serial.print("C | Kelembapan: ");
  Serial.print(data.humidity, 1);
  Serial.print("% | Status: ");
  Serial.print(statusStr(status));
  Serial.print(" | Publish: ");
  Serial.println(berhasil ? "OK" : "GAGAL");

  if (!berhasil) {
    Serial.println("  [WARN] Publish gagal. Cek koneksi MQTT.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  snprintf(
      TOPIC_TELEMETRY, sizeof(TOPIC_TELEMETRY),
      "upnjatim/iot/2026/%s/%s/telemetry", KELAS, KELOMPOK);
  snprintf(
      TOPIC_CONTROL, sizeof(TOPIC_CONTROL),
      "upnjatim/iot/2026/%s/%s/control", KELAS, KELOMPOK);
  snprintf(DEVICE_ID, sizeof(DEVICE_ID), "esp32-%s", KELOMPOK);

  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  Serial.println("============================================");
  Serial.println(" PRAKTIKUM IoT - PERTEMUAN 2");
  Serial.println(" MQTT Telemetry & Remote Control");
  Serial.println("============================================");
  Serial.print(" Device ID     : ");
  Serial.println(DEVICE_ID);
  Serial.print(" Topic TLM     : ");
  Serial.println(TOPIC_TELEMETRY);
  Serial.print(" Topic CTL     : ");
  Serial.println(TOPIC_CONTROL);
  Serial.print(" Broker        : ");
  Serial.print(MQTT_SERVER);
  Serial.print(":");
  Serial.println(MQTT_PORT);
  Serial.println("--------------------------------------------");

  digitalWrite(LED_HIJAU, HIGH);
  delay(300);
  digitalWrite(LED_MERAH, HIGH);
  delay(300);
  tone(BUZZER_PIN, 1000);
  delay(300);
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_HIJAU, LOW);
  noTone(BUZZER_PIN);

  connectWiFi();

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  reconnectMQTT();

  Serial.println();
  Serial.println("[SYS] Sistem siap. Mulai mengirim telemetry...");
  Serial.println();
}

void loop() {
  if (!mqttClient.connected()) {
    Serial.println("[MQTT] Koneksi terputus! Reconnect...");
    reconnectMQTT();
  }

  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastPublish >= publishInterval) {
    lastPublish = now;
    publishTelemetry();
  }
}
