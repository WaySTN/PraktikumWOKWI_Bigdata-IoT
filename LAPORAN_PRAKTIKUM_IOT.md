# LAPORAN PRAKTIKUM IoT
## Simulasi Smart Classroom Monitor dengan Wokwi

**Nama**: [Isi Nama Lengkap]  
**NIM**: [Isi NIM]  
**Kelas**: `pararel_B`  
**Kelompok**: `kelompok01`  
**Lokasi Simulasi**: `twintowerB_lantai7_706`  
**Mata Kuliah**: Big Data IoT  
**Program Studi**: Sistem Informasi  
**Universitas**: UPN "Veteran" Jawa Timur  
**Tahun**: 2026  
**Link Proyek Wokwi Pertemuan 1**: Belum dipublikasikan  
**Link Proyek Wokwi Pertemuan 2**: Belum dipublikasikan  
**Tanggal**: 12 Mei 2026  

<div style="page-break-after: always;"></div>

## BAB 1 - TUJUAN PRAKTIKUM

Praktikum ini dilaksanakan untuk memahami penerapan konsep Internet of Things secara bertahap, mulai dari pembacaan sensor dan pengendalian aktuator secara lokal hingga pengiriman data ke broker MQTT dan pengendalian perangkat secara jarak jauh. Pada Pertemuan 1, tujuan utama praktikum adalah membangun rangkaian virtual berbasis ESP32 dan DHT22 di Wokwi, menerapkan logika otomasi berbasis threshold suhu dan kelembapan, serta mengamati respons LED dan buzzer terhadap perubahan kondisi lingkungan.

Pada Pertemuan 2, tujuan praktikum berkembang ke arah komunikasi data dan integrasi jaringan. Praktikum bertujuan menghubungkan ESP32 virtual ke jaringan WiFi Wokwi, mengirim data telemetry ke broker MQTT publik, menampilkan data tersebut melalui MQTT Explorer, serta menguji mekanisme remote control melalui topic MQTT untuk menyalakan LED, buzzer, dan mengubah mode operasi sistem.

Secara keseluruhan, praktikum ini juga bertujuan melatih kemampuan mahasiswa dalam melakukan pengujian, menganalisis hasil aktual terhadap ekspektasi, mendokumentasikan bukti praktikum berupa screenshot dan tabel uji, serta menyusun laporan teknis yang sistematis dan profesional.

## BAB 2 - DASAR TEORI

### 2.1 Internet of Things

Internet of Things adalah konsep di mana perangkat fisik dilengkapi sensor, aktuator, kemampuan pemrosesan, serta konektivitas jaringan agar dapat saling bertukar data dan menjalankan fungsi otomatis maupun terintegrasi dengan sistem lain. Dalam arsitektur sederhana, alur IoT terdiri atas lapisan sensor atau device layer, lapisan komunikasi jaringan, lapisan pemrosesan data atau platform, dan lapisan aplikasi yang digunakan pengguna untuk monitoring atau kendali. Pada praktikum ini, ESP32 bertindak sebagai device utama, DHT22 sebagai sensor lingkungan, LED dan buzzer sebagai aktuator, broker MQTT sebagai media pertukaran pesan, dan MQTT Explorer sebagai alat monitoring data.

### 2.2 ESP32

ESP32 adalah mikrokontroler yang banyak digunakan pada pengembangan sistem IoT karena memiliki kemampuan pemrosesan yang cukup baik, mendukung WiFi, hemat biaya, dan didukung oleh ekosistem library yang luas. ESP32 cocok untuk kasus monitoring dan otomasi karena mampu membaca sensor, mengendalikan aktuator, dan melakukan komunikasi jaringan dalam satu perangkat. Dalam simulasi ini, ESP32 berfungsi membaca suhu dan kelembapan dari DHT22, menentukan status sistem berdasarkan threshold, mengendalikan LED dan buzzer, serta pada Pertemuan 2 mengirim dan menerima data MQTT.

### 2.3 Sensor DHT22

DHT22 adalah sensor digital yang umum digunakan untuk mengukur suhu dan kelembapan. Sensor ini mengirimkan data digital ke mikrokontroler sehingga pemrosesan menjadi lebih sederhana dibanding sensor analog. DHT22 dipilih dalam praktikum karena cukup representatif untuk studi kasus ruang kelas pintar. Dengan memanipulasi nilai suhu dan kelembapan pada simulator, pengguna dapat memverifikasi apakah logika pengambilan keputusan dalam program berjalan sesuai dengan rancangan.

### 2.4 Aktuator LED dan Buzzer

Aktuator adalah komponen output yang memberikan respons terhadap kondisi tertentu. Pada praktikum ini digunakan dua LED dan satu buzzer. LED hijau berfungsi menunjukkan kondisi normal, sedangkan LED merah menunjukkan kondisi warning. Buzzer digunakan sebagai alarm audio ketika parameter melebihi batas aman. Kombinasi indikator visual dan audio ini penting karena meniru kebutuhan sistem monitoring nyata yang harus cepat memberi peringatan kepada pengguna.

### 2.5 Protokol MQTT

MQTT adalah protokol komunikasi ringan berbasis model publish dan subscribe yang sangat populer pada sistem IoT. MQTT bekerja melalui broker yang menjadi perantara antara publisher dan subscriber. Perangkat tidak perlu berkomunikasi langsung satu sama lain, melainkan cukup mengirim atau membaca data melalui topic tertentu. Kelebihan MQTT adalah ringan, sederhana, dan cocok untuk perangkat dengan sumber daya terbatas. Pada praktikum ini, ESP32 mem-publish telemetry ke topic tertentu dan melakukan subscribe pada topic control untuk menerima perintah dari MQTT Explorer.

### 2.6 JSON Payload

JSON adalah format pertukaran data berbasis pasangan key dan value yang mudah dibaca manusia maupun diproses aplikasi. JSON sangat sering dipakai pada IoT karena struktur datanya ringkas, fleksibel, dan dapat membawa beberapa atribut sekaligus dalam satu pesan. Pada praktikum ini payload telemetry berisi `device_id`, `temperature`, `humidity`, `status`, `warning_reason`, `location`, `sample_no`, `mode`, dan `uptime_ms`. Struktur ini memudahkan monitoring, pelacakan identitas perangkat, dan analisis data.

### 2.7 Wokwi Simulator

Wokwi adalah simulator elektronik berbasis web dan VS Code yang memudahkan pengembangan sistem embedded tanpa perangkat fisik. Melalui Wokwi, pengguna dapat membangun rangkaian virtual, menjalankan kode ESP32, memanipulasi nilai sensor, dan mengamati keluaran sistem secara langsung. Pada praktikum ini, Wokwi sangat membantu karena memungkinkan pengujian sensor, aktuator, dan koneksi MQTT secara aman, cepat, dan dapat diulang tanpa risiko kerusakan perangkat keras.

## BAB 3 - ALAT DAN BAHAN VIRTUAL

| No | Nama | Jenis | Fungsi |
|----|------|-------|--------|
| 1 | ESP32 DevKit V1 | Hardware virtual | Mikrokontroler utama |
| 2 | DHT22 | Sensor virtual | Membaca suhu dan kelembapan |
| 3 | LED Merah | Aktuator virtual | Indikator warning |
| 4 | LED Hijau | Aktuator virtual | Indikator normal |
| 5 | Resistor 220 ohm | Komponen virtual | Pembatas arus LED |
| 6 | Buzzer | Aktuator virtual | Alarm suara |
| 7 | Wokwi Simulator | Software | Menjalankan simulasi rangkaian dan kode |
| 8 | VS Code | Software | Editor dan integrasi simulator |
| 9 | PlatformIO IDE | Extension VS Code | Build firmware ESP32 |
| 10 | MQTT Explorer | Software | Monitoring topic dan payload MQTT |
| 11 | Broker HiveMQ Public | Layanan jaringan | Perantara publish dan subscribe MQTT |
| 12 | Library DHT sensor library for ESPx | Library | Membaca DHT22 |
| 13 | Library PubSubClient | Library | Komunikasi MQTT |

## BAB 4 - DESAIN SISTEM

### 4.1 Diagram Arsitektur

Arsitektur sistem pada praktikum ini dapat digambarkan sebagai berikut:

```text
            +----------------------+
            |     MQTT Explorer    |
            | Monitoring & Control |
            +----------+-----------+
                       |
                       | MQTT Publish/Subscribe
                       v
            +----------------------+
            |  broker.hivemq.com   |
            |      MQTT Broker     |
            +----------+-----------+
                       ^
                       |
                       | WiFi + MQTT
                       |
            +----------+-----------+
            |        ESP32         |
            |  Logic + Telemetry   |
            +----+-----------+-----+
                 |           |
                 |           +----------------------+
                 |                                  |
                 v                                  v
          +-------------+                   +-----------------+
          |   DHT22     |                   | LED + Buzzer    |
          | Suhu/Kelemb |                   | Indikator alarm |
          +-------------+                   +-----------------+
```

Pada Pertemuan 1, arsitektur berhenti pada pembacaan sensor dan kendali aktuator lokal. Pada Pertemuan 2, sistem diperluas dengan konektivitas WiFi dan broker MQTT sehingga data dapat dipantau dari luar dan perangkat dapat menerima perintah jarak jauh.

### 4.2 Diagram Rangkaian dan Wiring

Rangkaian yang digunakan terdiri dari satu ESP32, satu DHT22, satu LED merah, satu LED hijau, dua resistor 220 ohm, dan satu buzzer. Wiring utama adalah:

- DHT22 VCC ke 3V3 ESP32
- DHT22 GND ke GND ESP32
- DHT22 SDA ke GPIO 15
- LED merah ke GPIO 2
- LED hijau ke GPIO 5
- Buzzer ke GPIO 4

Dokumentasi rangkaian Pertemuan 1:

<img src="pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20143851.png" width="650">

Dokumentasi rangkaian Pertemuan 2:

<img src="pertemuan-2/ss_pertemuan2/Screenshot%202026-05-12%20190646.png" width="650">

### 4.3 Flowchart Program

#### Flowchart Pertemuan 1

```text
START
  |
  v
Inisialisasi Serial, pin LED, pin buzzer, dan DHT22
  |
  v
Self-test aktuator
  |
  v
Baca suhu dan kelembapan
  |
  +--> Jika pembacaan gagal -> tampilkan error -> ulangi
  |
  v
Bandingkan nilai dengan threshold
  |
  +--> suhu > 28 dan kelembapan > 75 -> WARNING_GANDA
  +--> suhu > 28 -> WARNING_SUHU
  +--> kelembapan > 75 -> WARNING_KELEMBAPAN
  +--> selain itu -> NORMAL
  |
  v
Kendalikan LED dan buzzer sesuai status
  |
  v
Cetak hasil ke terminal
  |
  v
Delay 2 detik dan ulangi
```

#### Flowchart Pertemuan 2

```text
START
  |
  v
Inisialisasi Serial, pin, sensor, WiFi, dan MQTT
  |
  v
Bangun topic telemetry dan control
  |
  v
Connect WiFi
  |
  v
Connect broker MQTT dan subscribe topic control
  |
  v
Loop utama:
  - mqttClient.loop()
  - jika koneksi putus -> reconnect
  - setiap 5 detik baca sensor
  - tentukan status
  - jika mode AUTO kendalikan aktuator
  - bentuk payload JSON
  - publish ke topic telemetry
  - jika pesan control masuk, callback memproses perintah
```

### 4.4 Struktur Topic MQTT

Topic yang digunakan pada praktikum ini adalah:

```text
upnjatim/iot/2026/pararel_B/kelompok01/telemetry
upnjatim/iot/2026/pararel_B/kelompok01/control
```

Topic telemetry digunakan ESP32 untuk mengirim data sensor dan status sistem ke broker. Topic control digunakan oleh MQTT Explorer untuk mengirim perintah jarak jauh ke ESP32. Pemisahan topic ini membuat alur data lebih rapi, mudah dipantau, dan aman dari benturan dengan kelompok lain.

## BAB 5 - LANGKAH KERJA

### 5.1 Pertemuan 1

Langkah kerja Pertemuan 1 dimulai dengan membuka folder proyek `pertemuan-1` pada VS Code, memastikan file `diagram.json`, `sketch.ino`, `libraries.txt`, `platformio.ini`, dan `wokwi.toml` tersedia, lalu menjalankan proses build dengan PlatformIO. Setelah build berhasil, simulator Wokwi dijalankan untuk memverifikasi bahwa rangkaian tampil dengan benar dan terminal serial menampilkan keluaran program.

Setelah sistem aktif, dilakukan pengujian bertahap dengan mengubah parameter `temperature` dan `humidity` pada komponen DHT22 di Wokwi. Setiap perubahan diuji dengan menunggu pembacaan berikutnya lalu mengamati status yang muncul pada terminal, kondisi LED merah dan hijau, serta bunyi buzzer. Pengujian dilakukan pada tujuh skenario yang mewakili kondisi normal, warning suhu, warning kelembapan, warning ganda, kondisi tepat pada batas, kondisi sedikit di atas batas, dan suhu tinggi dengan kelembapan normal.

Hasil dari setiap pengujian dicatat ke dalam tabel dan dibandingkan dengan ekspektasi logika program. Selain itu, diambil screenshot rangkaian dan beberapa kondisi output sebagai bukti visual.

### 5.2 Pertemuan 2

Pada Pertemuan 2, folder `pertemuan-2` dibuka dan dibuild menggunakan PlatformIO. Setelah simulator berjalan, terminal Wokwi diamati untuk memastikan ESP32 berhasil terhubung ke jaringan `Wokwi-GUEST`, mendapatkan alamat IP, terkoneksi ke broker `broker.hivemq.com:1883`, dan melakukan subscribe ke topic control.

Langkah berikutnya adalah menghubungkan aplikasi MQTT Explorer desktop ke broker HiveMQ publik. Setelah koneksi berhasil, dilakukan subscribe ke topic `upnjatim/iot/2026/pararel_B/kelompok01/#` sehingga tree topic dan payload JSON telemetry dapat terlihat. Pada tahap ini diverifikasi bahwa payload yang dikirim ESP32 berisi identitas perangkat, suhu, kelembapan, status, alasan warning, lokasi, nomor sampel, mode, dan uptime.

Setelah telemetry dapat dipantau, dilakukan uji remote control dengan mengirim perintah `LED_ON`, `LED_OFF`, `BUZZER_ON`, `BUZZER_OFF`, `MANUAL`, `AUTO`, dan `RESET_ALARM` melalui topic control. Setiap perintah dikonfirmasi melalui perubahan aktuator pada Wokwi serta log `MQTT-CONTROL` pada terminal.

## BAB 6 - SOURCE CODE

### 6.1 Kode Program Pertemuan 1

```cpp
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
```

### 6.2 Kode Program Pertemuan 2

```cpp
#include <Arduino.h>
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
```

### 6.3 File diagram.json

```json
{
  "version": 1,
  "author": "Praktikum IoT UPN Veteran Jawa Timur 2026",
  "editor": "wokwi",
  "parts": [
    {
      "type": "wokwi-esp32-devkit-v1",
      "id": "esp",
      "top": 10,
      "left": 0,
      "attrs": {}
    },
    {
      "type": "wokwi-dht22",
      "id": "dht1",
      "top": -80,
      "left": 280,
      "attrs": {
        "temperature": "26",
        "humidity": "60"
      }
    },
    {
      "type": "wokwi-led",
      "id": "led_merah",
      "top": 80,
      "left": 280,
      "attrs": {
        "color": "red"
      }
    },
    {
      "type": "wokwi-resistor",
      "id": "r1",
      "top": 120,
      "left": 340,
      "attrs": {
        "value": "220"
      }
    },
    {
      "type": "wokwi-led",
      "id": "led_hijau",
      "top": 160,
      "left": 280,
      "attrs": {
        "color": "green"
      }
    },
    {
      "type": "wokwi-resistor",
      "id": "r2",
      "top": 200,
      "left": 340,
      "attrs": {
        "value": "220"
      }
    },
    {
      "type": "wokwi-buzzer",
      "id": "bz1",
      "top": 260,
      "left": 280,
      "attrs": {}
    }
  ],
  "connections": [
    ["esp:TX0", "$serialMonitor:RX", "", []],
    ["esp:RX0", "$serialMonitor:TX", "", []],
    ["esp:3V3", "dht1:VCC", "red", []],
    ["esp:GND.1", "dht1:GND", "black", []],
    ["esp:D15", "dht1:SDA", "green", []],
    ["esp:D2", "led_merah:A", "green", []],
    ["led_merah:C", "r1:1", "black", []],
    ["r1:2", "esp:GND.2", "black", []],
    ["esp:D5", "led_hijau:A", "green", []],
    ["led_hijau:C", "r2:1", "black", []],
    ["r2:2", "esp:GND.2", "black", []],
    ["esp:D4", "bz1:1", "green", []],
    ["bz1:2", "esp:GND.2", "black", []]
  ],
  "dependencies": {}
}
```

## BAB 7 - HASIL PENGUJIAN

### 7.1 Tabel Pengujian Pertemuan 1

| No | Suhu (C) | Kelembapan (%) | Ekspektasi Status | Hasil Aktual | LED Merah | LED Hijau | Buzzer | Keterangan |
|----|----------|----------------|-------------------|--------------|-----------|-----------|--------|------------|
| 1 | 25.0 | 60.0 | NORMAL | NORMAL | OFF | ON | OFF | Kondisi ideal ruang kelas, hasil sesuai ekspektasi |
| 2 | 29.0 | 65.0 | WARNING_SUHU | WARNING_SUHU | ON | OFF | 1000Hz | Suhu > 28C, hasil sesuai ekspektasi |
| 3 | 26.0 | 78.0 | WARNING_KELEMBAPAN | WARNING_KELEMBAPAN | ON | OFF | 1200Hz | Kelembapan > 75%, hasil sesuai ekspektasi |
| 4 | 31.0 | 82.0 | WARNING_GANDA | WARNING_GANDA | ON | OFF | 1500Hz | Keduanya melewati batas, hasil sesuai ekspektasi |
| 5 | 28.0 | 75.0 | NORMAL | NORMAL | OFF | ON | OFF | Tepat di batas, sistem tetap NORMAL |
| 6 | 28.1 | 75.1 | WARNING_GANDA | WARNING_GANDA | ON | OFF | 1500Hz | Baru melewati batas, warning langsung aktif |
| 7 | 35.0 | 55.0 | WARNING_SUHU | WARNING_SUHU | ON | OFF | 1000Hz | Suhu tinggi, kelembapan normal, hasil sesuai ekspektasi |

### 7.2 Tabel Pengujian Telemetry Pertemuan 2

| No | Suhu (C) | Kelembapan (%) | Status Ekspektasi | Payload Diterima | OK? |
|----|----------|----------------|-------------------|------------------|-----|
| 1 | 25.0 | 60.0 | NORMAL | JSON diterima, status `NORMAL`, field payload lengkap | Ya |
| 2 | 29.0 | 65.0 | WARNING_SUHU | JSON diterima, status `WARNING_SUHU`, payload sesuai kondisi sensor | Ya |
| 3 | 26.0 | 78.0 | WARNING_KELEMBAPAN | JSON diterima, status `WARNING_KELEMBAPAN`, payload sesuai kondisi sensor | Ya |
| 4 | 31.0 | 82.0 | WARNING_GANDA | JSON diterima, status `WARNING_GANDA`, payload sesuai kondisi sensor | Ya |
| 5 | 28.0 | 74.0 | NORMAL | JSON diterima, status `NORMAL`, nilai masih di bawah threshold | Ya |

### 7.3 Tabel Pengujian Control MQTT

| No | Perintah Dikirim | Topic | Ekspektasi | Hasil Aktual | OK? |
|----|------------------|-------|------------|--------------|-----|
| 1 | `LED_ON` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | LED Merah menyala | LED merah menyala dan log `MQTT-CONTROL` muncul di terminal | Ya |
| 2 | `LED_OFF` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | LED Merah mati | LED merah mati dan log kontrol diterima | Ya |
| 3 | `BUZZER_ON` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Buzzer bunyi 1200Hz | Buzzer aktif dan log kontrol diterima | Ya |
| 4 | `BUZZER_OFF` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Buzzer mati | Buzzer mati dan log kontrol diterima | Ya |
| 5 | `MANUAL` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Mode manual aktif | Mode sistem berubah ke `MANUAL` sesuai log terminal | Ya |
| 6 | `AUTO` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Mode auto aktif kembali | Mode sistem kembali ke `AUTO` sesuai log terminal | Ya |
| 7 | `RESET_ALARM` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Aktuator reset dan AUTO | Aktuator reset, mode kembali `AUTO`, dan log kontrol tampil | Ya |

### 7.4 Screenshot Rangkaian dan Kondisi Pertemuan 1

**Gambar 1. Rangkaian virtual Pertemuan 1**

<img src="pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20143851.png" width="650">

**Gambar 2. Kondisi WARNING_SUHU**

<img src="pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20183238.png" width="650">

**Gambar 3. Kondisi WARNING_KELEMBAPAN**

<img src="pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20183359.png" width="650">

**Gambar 4. Kondisi WARNING_GANDA**

<img src="pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20183456.png" width="650">

**Gambar 5. Kondisi NORMAL**

<img src="pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20183535.png" width="650">

### 7.5 Screenshot Serial Monitor Pertemuan 2

**Gambar 6. Header sistem dan identitas topic MQTT**

<img src="pertemuan-2/ss_pertemuan2/Screenshot%202026-05-12%20192320.png" width="700">

**Gambar 7. Koneksi WiFi berhasil**

<img src="pertemuan-2/ss_pertemuan2/Screenshot%202026-05-12%20192344.png" width="700">

**Gambar 8. MQTT connect dan subscribe berhasil**

<img src="pertemuan-2/ss_pertemuan2/Screenshot%202026-05-12%20192413.png" width="700">

**Gambar 9. Telemetry dipublish periodik**

<img src="pertemuan-2/ss_pertemuan2/Screenshot%202026-05-12%20192430.png" width="700">

### 7.6 Screenshot MQTT Explorer dan Control

**Gambar 10. Payload JSON telemetry pada MQTT Explorer**

<img src="pertemuan-2/ss_pertemuan2/Screenshot%202026-05-12%20223452.png" width="700">

**Gambar 11. Uji kontrol MQTT `LED_ON` berhasil**

<img src="pertemuan-2/ss_pertemuan2/Screenshot%202026-05-12%20222914.png" width="700">

## BAB 8 - PEMBAHASAN

Hasil praktikum menunjukkan bahwa sistem Smart Classroom Monitor yang dibangun pada simulator Wokwi telah bekerja sesuai tujuan perancangan. Pada Pertemuan 1, fokus utama adalah verifikasi logika lokal antara sensor DHT22, proses penentuan status, dan respons aktuator. Seluruh skenario pengujian memperlihatkan hubungan yang konsisten antara nilai suhu dan kelembapan dengan status yang dihasilkan sistem. Ketika suhu dan kelembapan berada di bawah ambang yang telah ditetapkan, sistem menampilkan status `NORMAL`, LED hijau menyala, LED merah mati, dan buzzer tidak aktif. Kondisi ini menunjukkan bahwa jalur pembacaan sensor, pengolahan logika, dan pengendalian aktuator telah saling terhubung dengan benar.

Aspek yang penting pada Pertemuan 1 adalah penggunaan threshold yang lebih sensitif dibanding nilai default modul, yaitu 28 C untuk suhu dan 75% untuk kelembapan. Perubahan ini membuat sistem lebih responsif terhadap kondisi ruang yang mulai tidak ideal. Hasil pengujian membuktikan bahwa ketika suhu dinaikkan menjadi 29.0 C dengan kelembapan tetap 65.0%, sistem segera menghasilkan `WARNING_SUHU`, menyalakan LED merah, mematikan LED hijau, dan mengaktifkan buzzer 1000 Hz. Saat kelembapan dinaikkan menjadi 78.0% dengan suhu 26.0 C, sistem memberikan `WARNING_KELEMBAPAN` dan membunyikan buzzer 1200 Hz. Ketika kedua parameter melewati batas secara bersamaan, status berubah menjadi `WARNING_GANDA` dan buzzer meningkat ke 1500 Hz. Ini menunjukkan bahwa logika pemilihan tingkat warning tidak hanya berjalan, tetapi juga cukup informatif karena tiap kondisi dibedakan dengan frekuensi alarm yang berbeda.

Pengujian pada nilai batas memberikan hasil yang sangat penting untuk analisis logika program. Pada skenario suhu 28.0 C dan kelembapan 75.0%, sistem tetap menghasilkan status `NORMAL`. Hal ini terjadi karena pada kode digunakan operator perbandingan `>` dan bukan `>=`. Artinya, kondisi warning baru aktif bila nilai benar-benar melewati threshold. Pada skenario 28.1 C dan 75.1%, status langsung berubah menjadi `WARNING_GANDA`. Perbedaan dua skenario ini memperlihatkan bahwa batas sistem bekerja presisi dan dapat dijelaskan secara akademik. Dalam konteks monitoring ruang kelas, perilaku ini bermanfaat karena mencegah alarm aktif terlalu dini saat nilai masih tepat di ambang, tetapi tetap cepat bereaksi ketika nilai melampaui batas.

Pertemuan 2 memperluas sistem dari otomasi lokal menjadi sistem IoT yang benar-benar terhubung ke jaringan. Dari hasil pengujian, ESP32 virtual berhasil terhubung ke `Wokwi-GUEST`, memperoleh alamat IP, tersambung ke broker `broker.hivemq.com`, dan berlangganan pada topic control. Keberhasilan ini membuktikan bahwa konfigurasi jaringan, library komunikasi, dan topic MQTT telah disusun dengan benar. Selain itu, log terminal menunjukkan bahwa ESP32 secara periodik mengirim telemetry setiap lima detik menggunakan pendekatan non-blocking berbasis `millis()`. Penggunaan `millis()` sangat penting karena memungkinkan perangkat tetap responsif terhadap pesan control meskipun sedang melakukan pengiriman data berkala.

Payload telemetry yang diterima di MQTT Explorer memperlihatkan bahwa data yang dikirim tidak hanya berupa suhu dan kelembapan, tetapi juga menyertakan `device_id`, `status`, `warning_reason`, `location`, `sample_no`, `mode`, dan `uptime_ms`. Struktur ini memberikan keuntungan besar dalam konteks IoT dan Big Data. Pertama, data menjadi lebih kaya konteks sehingga satu payload tidak sekadar menyimpan angka mentah, tetapi juga identitas perangkat dan lokasi pengukuran. Kedua, data seperti `sample_no` dan `uptime_ms` membantu pelacakan urutan serta kondisi operasi perangkat. Ketiga, `warning_reason` mempermudah sistem monitoring atau dashboard untuk menampilkan alasan alarm tanpa harus menghitung ulang logika threshold di sisi aplikasi. Inilah alasan mengapa format JSON sangat cocok digunakan, karena ia fleksibel, mudah dibaca manusia, dan kompatibel dengan banyak platform analitik maupun dashboard.

Pengujian remote control juga menunjukkan bahwa model publish-subscribe berjalan efektif. Ketika perintah seperti `LED_ON`, `LED_OFF`, `BUZZER_ON`, `BUZZER_OFF`, `MANUAL`, `AUTO`, dan `RESET_ALARM` dikirim melalui topic control, ESP32 menerima pesan tersebut dan menampilkan log `MQTT-CONTROL` pada terminal. Pengamatan visual juga memperlihatkan perubahan langsung pada LED dan buzzer. Ini membuktikan bahwa integrasi dua arah sudah berhasil: perangkat tidak hanya dapat mengirim data ke cloud, tetapi juga dapat menerima instruksi dari luar. Fitur `MANUAL` dan `AUTO` memperlihatkan desain sistem yang lebih matang karena perangkat dapat dipindah dari mode otomatis ke mode interaktif tanpa harus mengubah firmware. Fitur `RESET_ALARM` juga berguna karena memberikan satu perintah untuk mengembalikan sistem ke kondisi dasar.

Selama proses praktikum, terdapat beberapa kendala teknis yang justru memperkaya pemahaman. Salah satu kendala adalah Wokwi Terminal sempat kosong walaupun simulasi berjalan. Setelah dianalisis, penyebabnya adalah koneksi serial monitor belum didefinisikan pada `diagram.json`. Solusi yang diterapkan adalah menambahkan koneksi `esp:TX0` ke `$serialMonitor:RX` dan `esp:RX0` ke `$serialMonitor:TX`. Kendala lain terjadi saat MQTT Explorer extension di VS Code tidak menampilkan payload telemetry dengan baik. Solusi yang lebih efektif adalah menggunakan MQTT Explorer desktop portable dan mengatur subscription yang sesuai. Dari sini dapat dipahami bahwa keberhasilan sistem IoT tidak hanya bergantung pada kode mikrokontroler, tetapi juga pada konfigurasi tool pendukung.

Walaupun hasil simulasi sangat baik, ada keterbatasan yang perlu dicatat. Wokwi tidak sepenuhnya merepresentasikan kondisi perangkat nyata. Pada perangkat asli, pembacaan sensor dapat dipengaruhi noise, kualitas catu daya, kualitas kabel, dan latensi jaringan yang lebih bervariasi. Broker publik juga dapat mengalami beban tinggi atau konflik topic bila penamaan tidak unik. Selain itu, buzzer dan LED di simulator hanya memberikan indikasi visual atau logis, bukan karakteristik elektrik sebenarnya. Oleh karena itu, keberhasilan di Wokwi harus dipandang sebagai validasi logika dan integrasi awal, bukan jaminan absolut bahwa sistem akan langsung identik ketika dipindah ke hardware fisik.

Secara keseluruhan, hasil praktikum sudah sesuai ekspektasi dan menunjukkan bahwa konsep IoT pada level device, komunikasi, dan aplikasi dapat diimplementasikan dengan baik. Pertemuan 1 berhasil membuktikan pengendalian lokal berbasis threshold, sedangkan Pertemuan 2 membuktikan komunikasi telemetry dan kontrol jarak jauh. Dari sudut pandang pembelajaran, praktikum ini sangat relevan karena menggabungkan pemrograman embedded, logika otomasi, komunikasi jaringan, dan dokumentasi hasil uji dalam satu alur kerja yang utuh.

## BAB 9 - KESIMPULAN DAN SARAN

Berdasarkan hasil praktikum, dapat disimpulkan bahwa simulasi Smart Classroom Monitor berbasis ESP32 di Wokwi berhasil dirancang, dijalankan, dan diuji secara menyeluruh. Sistem mampu membaca suhu dan kelembapan dari DHT22, menentukan status berdasarkan threshold 28 C dan 75%, serta mengendalikan LED dan buzzer sesuai kondisi normal maupun warning. Integrasi MQTT pada Pertemuan 2 juga berhasil, ditunjukkan oleh koneksi ke broker publik, pengiriman payload JSON telemetry, dan penerimaan perintah control dari MQTT Explorer.

Praktikum ini memberikan pembelajaran penting mengenai hubungan antara sensor, logika perangkat, jaringan, dan aplikasi monitoring. Mahasiswa tidak hanya memahami bagaimana perangkat membaca data, tetapi juga bagaimana data tersebut dikirim, dipantau, dan digunakan untuk mengendalikan perangkat secara jarak jauh. Penggunaan format JSON dan topic MQTT yang terstruktur juga menunjukkan praktik baik dalam membangun sistem IoT yang mudah dikembangkan lebih lanjut.

Sebagai saran pengembangan, sistem ini dapat diperluas ke perangkat nyata dengan menambahkan dashboard seperti Node-RED atau ThingsBoard, menyimpan data ke database untuk analisis historis, serta menambahkan sensor lain seperti sensor cahaya atau kualitas udara. Selain itu, sistem dapat ditingkatkan dengan penggunaan autentikasi broker, topik yang lebih aman, dan mekanisme notifikasi otomatis agar lebih mendekati implementasi IoT pada dunia nyata.

## DAFTAR PUSTAKA

1. Espressif Systems. *ESP32 Series Datasheet*. Espressif.
2. Aosong. *DHT22 / AM2302 Digital Temperature and Humidity Sensor Datasheet*.
3. MQTT.org. *MQTT Version 3.1.1 Overview*.
4. HiveMQ. *MQTT Essentials*. HiveMQ Documentation and Blog.
5. Wokwi. *Wokwi Simulator Documentation*.
6. Knolleary. *PubSubClient Library for Arduino*.
7. beegee-tokyo. *DHT sensor library for ESPx*.

## LAMPIRAN

### Lampiran A - Daftar Screenshot Pertemuan 1

- `pertemuan-1/ss_pertemuan1/Screenshot 2026-05-12 143851.png`
- `pertemuan-1/ss_pertemuan1/Screenshot 2026-05-12 183238.png`
- `pertemuan-1/ss_pertemuan1/Screenshot 2026-05-12 183359.png`
- `pertemuan-1/ss_pertemuan1/Screenshot 2026-05-12 183456.png`
- `pertemuan-1/ss_pertemuan1/Screenshot 2026-05-12 183535.png`

### Lampiran B - Daftar Screenshot Pertemuan 2

- `pertemuan-2/ss_pertemuan2/Screenshot 2026-05-12 190646.png`
- `pertemuan-2/ss_pertemuan2/Screenshot 2026-05-12 192320.png`
- `pertemuan-2/ss_pertemuan2/Screenshot 2026-05-12 192344.png`
- `pertemuan-2/ss_pertemuan2/Screenshot 2026-05-12 192413.png`
- `pertemuan-2/ss_pertemuan2/Screenshot 2026-05-12 192430.png`
- `pertemuan-2/ss_pertemuan2/Screenshot 2026-05-12 222914.png`
- `pertemuan-2/ss_pertemuan2/Screenshot 2026-05-12 223452.png`
