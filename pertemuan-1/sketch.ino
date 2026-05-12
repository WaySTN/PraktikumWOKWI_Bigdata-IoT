/*
 * PRAKTIKUM IoT - PERTEMUAN 1
 * Sensor, Aktuator, dan Logika Otomasi
 * Studi kasus: Smart Classroom Monitor
 */

#include "DHTesp.h"

const int DHT_PIN = 15;
const int LED_MERAH = 2;
const int LED_HIJAU = 5;
const int BUZZER_PIN = 4;

const float BATAS_SUHU = 28.0;
const float BATAS_KELEMBAPAN = 75.0;

DHTesp dhtSensor;
int sampleCount = 0;

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

String statusKeString(StatusSistem status) {
  switch (status) {
    case NORMAL:
      return "NORMAL";
    case WARNING_SUHU:
      return "WARNING_SUHU";
    case WARNING_KELEMBAPAN:
      return "WARNING_KELEMBAPAN";
    case WARNING_GANDA:
      return "WARNING_GANDA";
    default:
      return "UNKNOWN";
  }
}

void kendalikanAktuator(StatusSistem status) {
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

void cetakHeader() {
  Serial.println("============================================");
  Serial.println(" PRAKTIKUM IoT - PERTEMUAN 1");
  Serial.println(" Smart Classroom Monitor - ESP32 Virtual");
  Serial.println("============================================");
  Serial.print("Threshold Suhu        : ");
  Serial.print(BATAS_SUHU, 1);
  Serial.println(" C");
  Serial.print("Threshold Kelembapan  : ");
  Serial.print(BATAS_KELEMBAPAN, 1);
  Serial.println(" %");
  Serial.println("--------------------------------------------");
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  digitalWrite(LED_MERAH, HIGH);
  digitalWrite(LED_HIJAU, HIGH);
  tone(BUZZER_PIN, 800);
  delay(500);
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_HIJAU, LOW);
  noTone(BUZZER_PIN);

  cetakHeader();
  Serial.println("Sistem siap. Memulai monitoring...");
  Serial.println();
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("[ERROR] Gagal membaca sensor DHT22. Pastikan wiring benar.");
    delay(2000);
    return;
  }

  sampleCount++;

  StatusSistem status = tentukanStatus(data.temperature, data.humidity);
  kendalikanAktuator(status);

  Serial.print("[");
  Serial.print(sampleCount);
  Serial.print("] Suhu: ");
  Serial.print(data.temperature, 1);
  Serial.print(" C | Kelembapan: ");
  Serial.print(data.humidity, 1);
  Serial.print(" % | Status: ");
  Serial.print(statusKeString(status));

  if (status != NORMAL) {
    Serial.print(" [");
    if (status == WARNING_SUHU || status == WARNING_GANDA) {
      Serial.print("Suhu melewati ");
      Serial.print(BATAS_SUHU, 1);
      Serial.print("C");
    }
    if (status == WARNING_GANDA) {
      Serial.print(", ");
    }
    if (status == WARNING_KELEMBAPAN || status == WARNING_GANDA) {
      Serial.print("Kelembapan melewati ");
      Serial.print(BATAS_KELEMBAPAN, 1);
      Serial.print("%");
    }
    Serial.print("]");
  }

  Serial.println();
  delay(2000);
}
