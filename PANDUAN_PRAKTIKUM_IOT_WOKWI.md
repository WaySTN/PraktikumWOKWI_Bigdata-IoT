# PANDUAN LENGKAP PRAKTIKUM IoT WOKWI
## Acuan AI Agent — Pertemuan 1 & 2
### Mata Kuliah: Big Data IoT | UPN "Veteran" Jawa Timur 2026

---

> **INSTRUKSI UNTUK AI AGENT:**
> File ini adalah acuan lengkap dan otoritatif untuk membantu mahasiswa menyelesaikan praktikum IoT dengan Wokwi dari awal hingga selesai. Baca seluruh dokumen ini sebelum membantu. Ikuti urutan langkah dengan presisi. Jangan skip bagian apapun. Jika ada file yang perlu dibuat, buat langsung. Jika ada kode yang perlu ditulis, tulis lengkap tanpa placeholder.

---

## DAFTAR ISI

1. [Konteks & Tujuan Praktikum](#1-konteks--tujuan-praktikum)
2. [Struktur Folder Project](#2-struktur-folder-project)
3. [Setup VS Code & Wokwi Extension](#3-setup-vs-code--wokwi-extension)
4. [PERTEMUAN 1 — Sensor, Aktuator & Logika Otomasi](#4-pertemuan-1--sensor-aktuator--logika-otomasi)
   - [4.1 Komponen & Wiring](#41-komponen--wiring)
   - [4.2 File diagram.json](#42-file-diagramjson)
   - [4.3 File libraries.txt](#43-file-librariestxt)
   - [4.4 Source Code sketch — VERSI TUGAS LENGKAP](#44-source-code-sketch--versi-tugas-lengkap)
   - [4.5 Logika Program Penjelasan Detail](#45-logika-program-penjelasan-detail)
   - [4.6 Cara Menguji di Wokwi](#46-cara-menguji-di-wokwi)
   - [4.7 Tabel Pengujian Hari 1](#47-tabel-pengujian-hari-1)
   - [4.8 Checklist Selesai Hari 1](#48-checklist-selesai-hari-1)
5. [PERTEMUAN 2 — MQTT, Telemetry & Remote Control](#5-pertemuan-2--mqtt-telemetry--remote-control)
   - [5.1 Konsep MQTT](#51-konsep-mqtt)
   - [5.2 Struktur Topic MQTT](#52-struktur-topic-mqtt)
   - [5.3 File diagram.json (sama dengan hari 1)](#53-file-diagramjson-sama-dengan-hari-1)
   - [5.4 File libraries.txt (diperbarui)](#54-file-librariestxt-diperbarui)
   - [5.5 Source Code MQTT — VERSI TUGAS LENGKAP](#55-source-code-mqtt--versi-tugas-lengkap)
   - [5.6 Penjelasan Detail Setiap Fungsi](#56-penjelasan-detail-setiap-fungsi)
   - [5.7 Cara Setup MQTT Explorer](#57-cara-setup-mqtt-explorer)
   - [5.8 Tabel Pengujian Hari 2](#58-tabel-pengujian-hari-2)
   - [5.9 Troubleshooting](#59-troubleshooting)
   - [5.10 Checklist Selesai Hari 2](#510-checklist-selesai-hari-2)
6. [Format Laporan Praktikum](#6-format-laporan-praktikum)
7. [Rubrik Penilaian & Target Nilai](#7-rubrik-penilaian--target-nilai)

---

## 1. KONTEKS & TUJUAN PRAKTIKUM

### Studi Kasus
**Smart Classroom Monitor** — perangkat IoT virtual yang memantau kondisi ruang kelas komputer. Ketika suhu atau kelembapan melewati batas aman, sistem memberikan peringatan audio-visual. Data dikirim ke cloud via MQTT.

### Capaian yang Harus Dipenuhi

| Kode | Capaian | Bukti |
|------|---------|-------|
| CP-1 | Memahami arsitektur IoT | Laporan bagian dasar teori |
| CP-2 | Membuat rangkaian di Wokwi | Screenshot + diagram.json |
| CP-3 | Menulis kode sensor & aktuator | sketch.ino berjalan |
| CP-4 | Mengirim telemetry via MQTT | Payload terlihat di MQTT Explorer |
| CP-5 | Menganalisis hasil pengujian | Tabel uji + analisis tertulis |
| CP-6 | Laporan profesional | Dokumen laporan lengkap |

### Platform yang Digunakan
- **Simulator:** [Wokwi Online](https://wokwi.com) atau Wokwi VS Code Extension
- **Broker MQTT:** `broker.hivemq.com` port `1883`
- **MQTT Client:** MQTT Explorer (download: [mqtt-explorer.com](https://mqtt-explorer.com))
- **IDE:** VS Code dengan extension Wokwi

---

## 2. STRUKTUR FOLDER PROJECT

AI Agent harus membuat struktur folder ini terlebih dahulu:

```
praktikum-iot-wokwi/
├── pertemuan-1/
│   ├── diagram.json          ← wiring rangkaian Wokwi
│   ├── sketch.ino            ← kode Arduino utama
│   ├── libraries.txt         ← deklarasi library
│   └── wokwi.toml            ← konfigurasi simulasi VS Code
├── pertemuan-2/
│   ├── diagram.json          ← wiring rangkaian (sama + tidak ada perubahan fisik)
│   ├── sketch.ino            ← kode Arduino + MQTT
│   ├── libraries.txt         ← library tambahan PubSubClient
│   └── wokwi.toml            ← konfigurasi simulasi VS Code
└── PANDUAN_PRAKTIKUM_IOT_WOKWI.md   ← file ini
```

### File wokwi.toml (sama untuk kedua pertemuan)
```toml
[wokwi]
version = 1
firmware = 'sketch.ino.bin'
elf = 'sketch.ino.elf'
```

> **CATATAN AI AGENT:** Jika menggunakan PlatformIO, sesuaikan path firmware dengan output build PlatformIO. Jika menggunakan Arduino IDE via Wokwi extension, gunakan konfigurasi di atas.

---

## 3. SETUP VS CODE & WOKWI EXTENSION

### Langkah Setup (AI Agent bantu user satu per satu)

**Step 1 — Install Extension Wokwi di VS Code**
1. Buka VS Code
2. Tekan `Ctrl+Shift+X` buka Extensions
3. Cari `Wokwi Simulator`
4. Install extension dari Wokwi

**Step 2 — Aktivasi Lisensi Wokwi**
1. Tekan `Ctrl+Shift+P`
2. Ketik `Wokwi: Request a New License`
3. Ikuti instruksi browser untuk aktivasi gratis

**Step 3 — Install Arduino CLI atau PlatformIO**

Opsi A — Arduino CLI:
```bash
# Install Arduino CLI
# Download dari https://arduino.github.io/arduino-cli/

# Install board ESP32
arduino-cli core install esp32:esp32
```

Opsi B — PlatformIO (lebih disarankan untuk VS Code):
1. Install extension `PlatformIO IDE` di VS Code
2. Buat project baru: PlatformIO Home → New Project
3. Board: `Espressif ESP32 Dev Module`
4. Framework: `Arduino`

**Step 4 — Verifikasi**
- Buka folder `pertemuan-1/`
- Buka `diagram.json`
- Tekan `F1` → `Wokwi: Start Simulator`
- Simulator harus terbuka di panel sebelah kanan

---

## 4. PERTEMUAN 1 — SENSOR, AKTUATOR & LOGIKA OTOMASI

### 4.1 Komponen & Wiring

#### Daftar Komponen

| Komponen | Jumlah | Fungsi |
|----------|--------|--------|
| ESP32 DevKit V1 | 1 | Mikrokontroler utama |
| DHT22 | 1 | Sensor suhu & kelembapan |
| LED Merah | 1 | Indikator WARNING |
| LED Hijau | 1 | Indikator NORMAL (tugas tambahan) |
| Resistor 220Ω | 2 | Pembatas arus LED merah & hijau |
| Buzzer | 1 | Indikator audio WARNING |

#### Tabel Wiring PIN

| Dari (Komponen) | Pin Komponen | Ke (ESP32) | Pin ESP32 | Warna Kabel |
|-----------------|-------------|------------|-----------|-------------|
| DHT22 | VCC | ESP32 | 3V3 | Merah |
| DHT22 | GND | ESP32 | GND | Hitam |
| DHT22 | DATA/SDA | ESP32 | D15 | Hijau |
| LED Merah | Anoda (+) | ESP32 | D2 | Hijau |
| LED Merah | Katoda (−) | Resistor 220Ω → GND | GND | Hitam |
| LED Hijau | Anoda (+) | ESP32 | D5 | Hijau |
| LED Hijau | Katoda (−) | Resistor 220Ω → GND | GND | Hitam |
| Buzzer | Pin (+) | ESP32 | D4 | Hijau |
| Buzzer | Pin (−) | ESP32 | GND | Hitam |

> **PENTING:** LED Hijau menggunakan pin **D5** (ditambahkan untuk tugas). Resistor wajib dipasang seri sebelum GND untuk setiap LED.

---

### 4.2 File diagram.json

Simpan file ini sebagai `pertemuan-1/diagram.json`:

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
      "attrs": { "color": "red" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r1",
      "top": 120,
      "left": 340,
      "attrs": { "value": "220" }
    },
    {
      "type": "wokwi-led",
      "id": "led_hijau",
      "top": 160,
      "left": 280,
      "attrs": { "color": "green" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r2",
      "top": 200,
      "left": 340,
      "attrs": { "value": "220" }
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
    ["esp:3V3",   "dht1:VCC",        "red",   []],
    ["esp:GND.1", "dht1:GND",        "black", []],
    ["esp:D15",   "dht1:SDA",        "green", []],
    ["esp:D2",    "led_merah:A",     "green", []],
    ["led_merah:C", "r1:1",          "black", []],
    ["r1:2",      "esp:GND.2",       "black", []],
    ["esp:D5",    "led_hijau:A",     "green", []],
    ["led_hijau:C", "r2:1",          "black", []],
    ["r2:2",      "esp:GND.2",       "black", []],
    ["esp:D4",    "bz1:1",           "green", []],
    ["bz1:2",     "esp:GND.2",       "black", []]
  ],
  "dependencies": {}
}
```

---

### 4.3 File libraries.txt

Simpan file ini sebagai `pertemuan-1/libraries.txt`:

```
DHT sensor library for ESPx
```

---

### 4.4 Source Code sketch — VERSI TUGAS LENGKAP

Simpan file ini sebagai `pertemuan-1/sketch.ino`:

```cpp
/*
 * ============================================================
 * PRAKTIKUM IoT - PERTEMUAN 1
 * Sensor, Aktuator, dan Logika Otomasi
 * 
 * Studi Kasus: Smart Classroom Monitor
 * Platform   : ESP32 DevKit V1 (Wokwi Virtual)
 * Sensor     : DHT22 (suhu & kelembapan)
 * Aktuator   : LED Merah, LED Hijau, Buzzer
 * 
 * Fitur Tugas:
 * - Threshold suhu    : 28°C
 * - Threshold kelembapan : 75%
 * - LED Hijau untuk status NORMAL
 * - Status 4 varian: NORMAL, WARNING_SUHU,
 *   WARNING_KELEMBAPAN, WARNING_GANDA
 * 
 * UPN "Veteran" Jawa Timur 2026
 * ============================================================
 */

#include "DHTesp.h"

// ── PIN DEFINITION ──────────────────────────────────────────
const int DHT_PIN     = 15;
const int LED_MERAH   = 2;
const int LED_HIJAU   = 5;
const int BUZZER_PIN  = 4;

// ── THRESHOLD (DISESUAIKAN UNTUK TUGAS) ─────────────────────
const float BATAS_SUHU        = 28.0;   // Tugas: diubah dari 30 ke 28
const float BATAS_KELEMBAPAN  = 75.0;   // Tugas: diubah dari 80 ke 75

// ── OBJEK SENSOR ────────────────────────────────────────────
DHTesp dhtSensor;

// ── VARIABEL GLOBAL ──────────────────────────────────────────
int sampleCount = 0;  // Penghitung sampel pengujian

// ── ENUM STATUS (4 VARIAN SESUAI TUGAS) ─────────────────────
enum StatusSistem {
  NORMAL,
  WARNING_SUHU,
  WARNING_KELEMBAPAN,
  WARNING_GANDA
};

// ── FUNGSI: Tentukan status berdasarkan threshold ────────────
StatusSistem tentukanStatus(float suhu, float kelembapan) {
  bool suhuWarning        = suhu > BATAS_SUHU;
  bool kelembapanWarning  = kelembapan > BATAS_KELEMBAPAN;

  if (suhuWarning && kelembapanWarning) return WARNING_GANDA;
  if (suhuWarning)                      return WARNING_SUHU;
  if (kelembapanWarning)                return WARNING_KELEMBAPAN;
  return NORMAL;
}

// ── FUNGSI: Konversi enum status ke String ───────────────────
String statusKeString(StatusSistem status) {
  switch (status) {
    case NORMAL:               return "NORMAL";
    case WARNING_SUHU:         return "WARNING_SUHU";
    case WARNING_KELEMBAPAN:   return "WARNING_KELEMBAPAN";
    case WARNING_GANDA:        return "WARNING_GANDA";
    default:                   return "UNKNOWN";
  }
}

// ── FUNGSI: Kendalikan aktuator berdasarkan status ───────────
void kendalikanAktuator(StatusSistem status) {
  if (status == NORMAL) {
    // Kondisi NORMAL: LED Hijau ON, LED Merah OFF, Buzzer OFF
    digitalWrite(LED_HIJAU,  HIGH);
    digitalWrite(LED_MERAH,  LOW);
    noTone(BUZZER_PIN);
  } else {
    // Kondisi WARNING: LED Merah ON, LED Hijau OFF, Buzzer ON
    digitalWrite(LED_MERAH,  HIGH);
    digitalWrite(LED_HIJAU,  LOW);

    // Frekuensi buzzer berbeda per jenis warning
    if (status == WARNING_SUHU)         tone(BUZZER_PIN, 1000);
    else if (status == WARNING_KELEMBAPAN) tone(BUZZER_PIN, 1200);
    else if (status == WARNING_GANDA)   tone(BUZZER_PIN, 1500);
  }
}

// ── FUNGSI: Cetak header Serial Monitor ─────────────────────
void cetakHeader() {
  Serial.println("============================================");
  Serial.println(" PRAKTIKUM IoT - PERTEMUAN 1");
  Serial.println(" Smart Classroom Monitor - ESP32 Virtual");
  Serial.println("============================================");
  Serial.print("Threshold Suhu        : ");
  Serial.print(BATAS_SUHU, 1);
  Serial.println(" °C");
  Serial.print("Threshold Kelembapan  : ");
  Serial.print(BATAS_KELEMBAPAN, 1);
  Serial.println(" %");
  Serial.println("--------------------------------------------");
}

// ── SETUP ────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);

  // Inisialisasi pin aktuator
  pinMode(LED_MERAH,  OUTPUT);
  pinMode(LED_HIJAU,  OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Inisialisasi sensor DHT22
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // Nyalakan semua aktuator sebentar sebagai self-test
  digitalWrite(LED_MERAH, HIGH);
  digitalWrite(LED_HIJAU, HIGH);
  tone(BUZZER_PIN, 800);
  delay(500);
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_HIJAU, LOW);
  noTone(BUZZER_PIN);

  cetakHeader();
  Serial.println("Sistem siap. Memulai monitoring...\n");
}

// ── LOOP UTAMA ───────────────────────────────────────────────
void loop() {
  // Baca data sensor
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  // Validasi pembacaan sensor
  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("[ERROR] Gagal membaca sensor DHT22. Pastikan wiring benar.");
    delay(2000);
    return;
  }

  sampleCount++;

  // Tentukan status sistem
  StatusSistem status = tentukanStatus(data.temperature, data.humidity);

  // Kendalikan aktuator
  kendalikanAktuator(status);

  // Cetak ke Serial Monitor
  Serial.print("[");
  Serial.print(sampleCount);
  Serial.print("] ");
  Serial.print("Suhu: ");
  Serial.print(data.temperature, 1);
  Serial.print(" °C | ");
  Serial.print("Kelembapan: ");
  Serial.print(data.humidity, 1);
  Serial.print(" % | ");
  Serial.print("Status: ");
  Serial.print(statusKeString(status));

  // Indikator tambahan untuk analisis
  if (status != NORMAL) {
    Serial.print(" ⚠ [");
    if (status == WARNING_SUHU || status == WARNING_GANDA) {
      Serial.print("Suhu melewati ");
      Serial.print(BATAS_SUHU, 1);
      Serial.print("°C");
    }
    if (status == WARNING_GANDA) Serial.print(", ");
    if (status == WARNING_KELEMBAPAN || status == WARNING_GANDA) {
      Serial.print("Kelembapan melewati ");
      Serial.print(BATAS_KELEMBAPAN, 1);
      Serial.print("%");
    }
    Serial.print("]");
  }

  Serial.println();

  // Tunda 2 detik sebelum pembacaan berikutnya
  delay(2000);
}
```

---

### 4.5 Logika Program Penjelasan Detail

```
FLOWCHART PERTEMUAN 1:

START
  │
  ▼
setup():
  - Serial.begin(115200)
  - pinMode LED_MERAH, LED_HIJAU, BUZZER
  - dhtSensor.setup(D15, DHT22)
  - Self-test aktuator (0.5 detik)
  │
  ▼
loop():
  │
  ▼
Baca DHT22 → data.temperature & data.humidity
  │
  ├─ isnan? → [ERROR] print → delay 2s → kembali ke atas
  │
  ▼
tentukanStatus(suhu, kelembapan):
  ├─ suhu > 28 AND kelembapan > 75  → WARNING_GANDA
  ├─ suhu > 28                       → WARNING_SUHU
  ├─ kelembapan > 75                 → WARNING_KELEMBAPAN
  └─ else                            → NORMAL
  │
  ▼
kendalikanAktuator(status):
  ├─ NORMAL          → LED_HIJAU ON | LED_MERAH OFF | noTone
  ├─ WARNING_SUHU    → LED_MERAH ON | LED_HIJAU OFF | tone(1000)
  ├─ WARNING_KELEMBAPAN → LED_MERAH ON | LED_HIJAU OFF | tone(1200)
  └─ WARNING_GANDA   → LED_MERAH ON | LED_HIJAU OFF | tone(1500)
  │
  ▼
Print Serial Monitor → delay(2000) → kembali ke loop
```

**Penjelasan Threshold Tugas:**
- Threshold suhu diturunkan dari 30°C → **28°C** → WARNING lebih sering muncul di kondisi ruangan normal (lebih sensitif)
- Threshold kelembapan diturunkan dari 80% → **75%** → Sistem lebih cepat memberi peringatan kelembapan tinggi
- Dampak: frekuensi status WARNING meningkat, sistem lebih protektif

---

### 4.6 Cara Menguji di Wokwi

**Di Wokwi Online (wokwi.com):**
1. Buka [wokwi.com](https://wokwi.com) → New Project → ESP32
2. Copy-paste `diagram.json` ke tab diagram
3. Copy-paste `sketch.ino` ke editor kode
4. Tambah library: klik ikon library → cari `DHT sensor library for ESPx` → Add
5. Klik **▶ Start Simulation**
6. Buka **Serial Monitor** di bagian bawah

**Mengubah Nilai Sensor DHT22 untuk Pengujian:**
1. Klik komponen DHT22 di diagram
2. Panel kanan akan muncul slider/input
3. Ubah nilai `temperature` dan `humidity`
4. Amati perubahan di Serial Monitor dan kondisi LED

**Di VS Code + Wokwi Extension:**
1. Buka folder `pertemuan-1/` di VS Code
2. Tekan `F1` → `Wokwi: Start Simulator`
3. Simulator muncul di panel kanan
4. Untuk mengubah nilai DHT22, klik komponen di simulator

---

### 4.7 Tabel Pengujian Hari 1

Isi kolom **Hasil Aktual** dan **Keterangan** saat menjalankan simulasi:

| No | Suhu (°C) | Kelembapan (%) | Ekspektasi Status | Hasil Aktual | LED Merah | LED Hijau | Buzzer | Keterangan |
|----|-----------|----------------|-------------------|-------------|-----------|-----------|--------|------------|
| 1  | 25.0      | 60.0           | NORMAL            | _________   | OFF       | ON        | OFF    | Kondisi ideal ruang kelas |
| 2  | 29.0      | 65.0           | WARNING_SUHU      | _________   | ON        | OFF       | 1000Hz | Suhu > 28°C |
| 3  | 26.0      | 78.0           | WARNING_KELEMBAPAN| _________   | ON        | OFF       | 1200Hz | Kelembapan > 75% |
| 4  | 31.0      | 82.0           | WARNING_GANDA     | _________   | ON        | OFF       | 1500Hz | Keduanya melewati batas |
| 5  | 28.0      | 75.0           | NORMAL            | _________   | OFF       | ON        | OFF    | Tepat di batas (tidak melewati) |
| 6  | 28.1      | 75.1           | WARNING_GANDA     | _________   | ON        | OFF       | 1500Hz | Baru saja melewati batas |
| 7  | 35.0      | 55.0           | WARNING_SUHU      | _________   | ON        | OFF       | 1000Hz | Suhu ekstrem, kelembapan normal |

> **Instruksi AI Agent:** Bantu user mengisi kolom Hasil Aktual dengan melihat output Serial Monitor selama simulasi berjalan. Konfirmasi apakah hasil aktual sesuai ekspektasi.

---

### 4.8 Checklist Selesai Hari 1

Pastikan semua item ini terpenuhi sebelum lanjut ke Pertemuan 2:

- [ ] File `diagram.json` dibuat dan rangkaian tampil di Wokwi (ESP32 + DHT22 + 2 LED + 2 Resistor + Buzzer)
- [ ] File `sketch.ino` dibuat dan berhasil dikompilasi tanpa error
- [ ] Simulasi berjalan — Serial Monitor menampilkan data setiap 2 detik
- [ ] Self-test aktuator berjalan saat pertama kali start (semua LED + buzzer nyala 0.5 detik)
- [ ] Status NORMAL: LED Hijau ON, LED Merah OFF, Buzzer OFF ✓
- [ ] Status WARNING_SUHU: LED Merah ON, LED Hijau OFF, Buzzer 1000Hz ✓
- [ ] Status WARNING_KELEMBAPAN: LED Merah ON, LED Hijau OFF, Buzzer 1200Hz ✓
- [ ] Status WARNING_GANDA: LED Merah ON, LED Hijau OFF, Buzzer 1500Hz ✓
- [ ] Threshold suhu = 28°C, threshold kelembapan = 75% (bukan nilai default modul)
- [ ] Tabel pengujian 7 skenario telah diisi
- [ ] Screenshot rangkaian, serial monitor NORMAL, serial monitor WARNING diambil

---

## 5. PERTEMUAN 2 — MQTT, TELEMETRY & REMOTE CONTROL

### 5.1 Konsep MQTT

```
ARSITEKTUR MQTT PRAKTIKUM:

┌─────────────────┐     PUBLISH telemetry     ┌──────────────────────┐
│   ESP32 Virtual │ ─────────────────────────► │                      │
│   (Wokwi)       │                            │  broker.hivemq.com   │
│                 │ ◄─────────────────────────  │  (MQTT Broker)       │
└─────────────────┘    SUBSCRIBE control        └──────────────────────┘
                                                        │  ▲
                                                PUBLISH │  │ SUBSCRIBE
                                                control │  │ telemetry
                                                        ▼  │
                                                ┌──────────────────────┐
                                                │   MQTT Explorer /    │
                                                │   Node-RED           │
                                                │   (Client Pemantau)  │
                                                └──────────────────────┘
```

**Elemen MQTT:**

| Istilah | Penjelasan | Contoh dalam Praktikum |
|---------|-----------|------------------------|
| Broker | Server perantara pesan | `broker.hivemq.com:1883` |
| Client | Siapapun yang konek ke broker | ESP32, MQTT Explorer |
| Topic | Alamat logis pesan | `upnjatim/iot/2026/kelasA/kelompok1/telemetry` |
| Publish | Kirim pesan ke topic | ESP32 kirim JSON sensor tiap 5 detik |
| Subscribe | Pantau topic tertentu | MQTT Explorer pantau topic telemetry |
| Payload | Isi pesan | JSON berisi suhu, kelembapan, status |
| QoS 0 | Fire and forget | Digunakan dalam praktikum ini |

---

### 5.2 Struktur Topic MQTT

**Format yang digunakan:**
```
upnjatim/iot/{tahun}/{kelas}/{kelompok}/telemetry   ← ESP32 PUBLISH
upnjatim/iot/{tahun}/{kelas}/{kelompok}/control     ← ESP32 SUBSCRIBE
```

**Contoh untuk kelompok 1 kelas A:**
```
upnjatim/iot/2026/kelasA/kelompok01/telemetry
upnjatim/iot/2026/kelasA/kelompok01/control
```

> **WAJIB DIGANTI:** Sesuaikan `kelas` dan `kelompok` dengan data aktual. Ini mencegah bentrok dengan kelompok lain di broker publik.

**Payload JSON Telemetry yang Dikirim:**
```json
{
  "device_id": "esp32-kelompok01",
  "temperature": 27.50,
  "humidity": 68.20,
  "status": "NORMAL",
  "warning_reason": "none",
  "location": "ruang-kelas-A301",
  "sample_no": 42,
  "uptime_ms": 210000
}
```

**Perintah Kontrol yang Diterima:**

| Payload | Aksi ESP32 |
|---------|-----------|
| `LED_ON` | Nyalakan LED Merah |
| `LED_OFF` | Matikan LED Merah |
| `BUZZER_ON` | Buzzer berbunyi 1200Hz |
| `BUZZER_OFF` | Matikan Buzzer |
| `AUTO` | Kembali ke mode otomatis (aktuator ikuti sensor) |
| `MANUAL` | Mode manual — aktuator hanya dikendalikan via MQTT |
| `RESET_ALARM` | Matikan semua aktuator, kembali ke NORMAL |

---

### 5.3 File diagram.json (sama dengan hari 1)

Rangkaian fisik tidak berubah dari Pertemuan 1. Salin file `pertemuan-1/diagram.json` ke `pertemuan-2/diagram.json`. Tidak ada penambahan komponen hardware.

---

### 5.4 File libraries.txt (diperbarui)

Simpan sebagai `pertemuan-2/libraries.txt`:

```
DHT sensor library for ESPx
PubSubClient
```

---

### 5.5 Source Code MQTT — VERSI TUGAS LENGKAP

Simpan sebagai `pertemuan-2/sketch.ino`:

```cpp
/*
 * ============================================================
 * PRAKTIKUM IoT - PERTEMUAN 2
 * MQTT, Telemetry, dan Remote Control
 *
 * Studi Kasus: Smart Classroom Monitor + IoT Network
 * Platform   : ESP32 DevKit V1 (Wokwi Virtual)
 * WiFi       : Wokwi-GUEST (virtual, tidak perlu password)
 * Broker     : broker.hivemq.com:1883
 *
 * Fitur Tugas:
 * - device_id format kelompok
 * - Topic MQTT unik per kelompok
 * - Field JSON tambahan: location, sample_no, warning_reason
 * - Mode AUTO / MANUAL / RESET_ALARM
 * - Publish interval 5 detik
 *
 * PERHATIAN: Ganti KELAS dan KELOMPOK sesuai data aktual!
 *
 * UPN "Veteran" Jawa Timur 2026
 * ============================================================
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// ── KONFIGURASI — WAJIB DISESUAIKAN ─────────────────────────
const char* KELAS    = "kelasA";         // Ganti dengan kelas aktual
const char* KELOMPOK = "kelompok01";     // Ganti dengan nomor kelompok
const char* LOKASI   = "ruang-kelas-A301";  // Ganti dengan lokasi ruang

// ── KONFIGURASI WIFI ─────────────────────────────────────────
const char* WIFI_SSID     = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

// ── KONFIGURASI BROKER MQTT ──────────────────────────────────
const char* MQTT_SERVER = "broker.hivemq.com";
const int   MQTT_PORT   = 1883;

// ── TOPIC MQTT (auto-generate dari KELAS & KELOMPOK) ─────────
// Format: upnjatim/iot/2026/{kelas}/{kelompok}/telemetry
char TOPIC_TELEMETRY[100];
char TOPIC_CONTROL[100];
char DEVICE_ID[50];

// ── PIN DEFINITION ──────────────────────────────────────────
const int DHT_PIN    = 15;
const int LED_MERAH  = 2;
const int LED_HIJAU  = 5;
const int BUZZER_PIN = 4;

// ── THRESHOLD ────────────────────────────────────────────────
const float BATAS_SUHU       = 28.0;
const float BATAS_KELEMBAPAN = 75.0;

// ── OBJEK ────────────────────────────────────────────────────
DHTesp       dhtSensor;
WiFiClient   espClient;
PubSubClient mqttClient(espClient);

// ── STATE SISTEM ─────────────────────────────────────────────
enum ModeSistem { MODE_AUTO, MODE_MANUAL };
ModeSistem   modeSistem = MODE_AUTO;

unsigned long lastPublish   = 0;
unsigned long publishInterval = 5000;  // 5 detik
int           sampleNo      = 0;

// ── ENUM STATUS ──────────────────────────────────────────────
enum StatusSistem {
  NORMAL,
  WARNING_SUHU,
  WARNING_KELEMBAPAN,
  WARNING_GANDA
};

// ── FUNGSI: Tentukan status ──────────────────────────────────
StatusSistem tentukanStatus(float suhu, float kelembapan) {
  bool s = suhu > BATAS_SUHU;
  bool k = kelembapan > BATAS_KELEMBAPAN;
  if (s && k) return WARNING_GANDA;
  if (s)      return WARNING_SUHU;
  if (k)      return WARNING_KELEMBAPAN;
  return NORMAL;
}

// ── FUNGSI: Konversi status ke string ────────────────────────
const char* statusStr(StatusSistem st) {
  switch (st) {
    case WARNING_SUHU:        return "WARNING_SUHU";
    case WARNING_KELEMBAPAN:  return "WARNING_KELEMBAPAN";
    case WARNING_GANDA:       return "WARNING_GANDA";
    default:                  return "NORMAL";
  }
}

// ── FUNGSI: Warning reason ────────────────────────────────────
const char* warningReason(StatusSistem st) {
  switch (st) {
    case WARNING_SUHU:        return "suhu_melebihi_batas";
    case WARNING_KELEMBAPAN:  return "kelembapan_melebihi_batas";
    case WARNING_GANDA:       return "suhu_dan_kelembapan_melebihi_batas";
    default:                  return "none";
  }
}

// ── FUNGSI: Kendalikan aktuator (hanya di mode AUTO) ─────────
void kendalikanAktuatorAuto(StatusSistem st) {
  if (modeSistem == MODE_MANUAL) return;  // Manual mode: skip

  if (st == NORMAL) {
    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(LED_MERAH, LOW);
    noTone(BUZZER_PIN);
  } else {
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    if      (st == WARNING_SUHU)        tone(BUZZER_PIN, 1000);
    else if (st == WARNING_KELEMBAPAN)  tone(BUZZER_PIN, 1200);
    else if (st == WARNING_GANDA)       tone(BUZZER_PIN, 1500);
  }
}

// ── FUNGSI: MQTT Callback (terima perintah kontrol) ──────────
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  // Konversi payload ke String
  String pesan = "";
  for (unsigned int i = 0; i < length; i++) {
    pesan += (char)payload[i];
  }
  pesan.trim();

  Serial.print("[MQTT-CONTROL] Pesan diterima: ");
  Serial.println(pesan);

  // ── Proses Perintah ──────────────────────────────────────
  if (pesan == "LED_ON") {
    digitalWrite(LED_MERAH, HIGH);
    Serial.println("  → LED Merah ON");

  } else if (pesan == "LED_OFF") {
    digitalWrite(LED_MERAH, LOW);
    Serial.println("  → LED Merah OFF");

  } else if (pesan == "BUZZER_ON") {
    tone(BUZZER_PIN, 1200);
    Serial.println("  → Buzzer ON (1200Hz)");

  } else if (pesan == "BUZZER_OFF") {
    noTone(BUZZER_PIN);
    Serial.println("  → Buzzer OFF");

  } else if (pesan == "AUTO") {
    modeSistem = MODE_AUTO;
    Serial.println("  → Mode: AUTO (aktuator ikuti sensor)");

  } else if (pesan == "MANUAL") {
    modeSistem = MODE_MANUAL;
    Serial.println("  → Mode: MANUAL (aktuator via MQTT)");

  } else if (pesan == "RESET_ALARM") {
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);
    noTone(BUZZER_PIN);
    modeSistem = MODE_AUTO;
    Serial.println("  → RESET_ALARM: semua aktuator reset, mode AUTO");

  } else {
    Serial.print("  → Perintah tidak dikenal: ");
    Serial.println(pesan);
  }
}

// ── FUNGSI: Koneksi WiFi ─────────────────────────────────────
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
      Serial.println("\n[WiFi] GAGAL terhubung! Restart ESP32...");
      ESP.restart();
    }
  }

  Serial.println();
  Serial.println("[WiFi] Terhubung!");
  Serial.print("[WiFi] IP Address: ");
  Serial.println(WiFi.localIP());
}

// ── FUNGSI: Koneksi / Reconneksi MQTT ────────────────────────
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

      // Subscribe ke topic control
      mqttClient.subscribe(TOPIC_CONTROL);
      Serial.print("[MQTT] Subscribe ke: ");
      Serial.println(TOPIC_CONTROL);

    } else {
      Serial.print("[MQTT] Gagal, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" — coba lagi 3 detik...");

      if (mqttAttempt >= 5) {
        Serial.println("[MQTT] Terlalu banyak gagal, periksa koneksi internet.");
        break;
      }
      delay(3000);
    }
  }
}

// ── FUNGSI: Publish Telemetry ─────────────────────────────────
void publishTelemetry() {
  // Baca sensor
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("[ERROR] Gagal membaca DHT22!");
    return;
  }

  sampleNo++;

  // Tentukan status
  StatusSistem st = tentukanStatus(data.temperature, data.humidity);

  // Kendalikan aktuator (jika mode AUTO)
  kendalikanAktuatorAuto(st);

  // Buat payload JSON
  // Field tambahan tugas: location, sample_no, warning_reason
  char payload[350];
  snprintf(payload, sizeof(payload),
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
    DEVICE_ID,
    data.temperature,
    data.humidity,
    statusStr(st),
    warningReason(st),
    LOKASI,
    sampleNo,
    (modeSistem == MODE_AUTO ? "AUTO" : "MANUAL"),
    millis()
  );

  // Publish ke broker
  bool berhasil = mqttClient.publish(TOPIC_TELEMETRY, payload);

  // Log ke Serial Monitor
  Serial.print("[MQTT-PUB] Sample #");
  Serial.print(sampleNo);
  Serial.print(" | Suhu: ");
  Serial.print(data.temperature, 1);
  Serial.print("°C | Kelembapan: ");
  Serial.print(data.humidity, 1);
  Serial.print("% | Status: ");
  Serial.print(statusStr(st));
  Serial.print(" | Publish: ");
  Serial.println(berhasil ? "OK ✓" : "GAGAL ✗");

  if (!berhasil) {
    Serial.println("  [WARN] Publish gagal. Cek koneksi MQTT.");
  }
}

// ── SETUP ────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);

  // Bangun topic dan device ID dari kelas & kelompok
  snprintf(TOPIC_TELEMETRY, sizeof(TOPIC_TELEMETRY),
    "upnjatim/iot/2026/%s/%s/telemetry", KELAS, KELOMPOK);
  snprintf(TOPIC_CONTROL, sizeof(TOPIC_CONTROL),
    "upnjatim/iot/2026/%s/%s/control", KELAS, KELOMPOK);
  snprintf(DEVICE_ID, sizeof(DEVICE_ID),
    "esp32-%s", KELOMPOK);

  // Inisialisasi PIN
  pinMode(LED_MERAH,  OUTPUT);
  pinMode(LED_HIJAU,  OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Inisialisasi sensor
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // Header Serial
  Serial.println("============================================");
  Serial.println(" PRAKTIKUM IoT - PERTEMUAN 2");
  Serial.println(" MQTT Telemetry & Remote Control");
  Serial.println("============================================");
  Serial.print(" Device ID     : "); Serial.println(DEVICE_ID);
  Serial.print(" Topic TLM     : "); Serial.println(TOPIC_TELEMETRY);
  Serial.print(" Topic CTL     : "); Serial.println(TOPIC_CONTROL);
  Serial.print(" Broker        : "); Serial.print(MQTT_SERVER);
  Serial.print(":"); Serial.println(MQTT_PORT);
  Serial.println("--------------------------------------------");

  // Self-test aktuator
  digitalWrite(LED_HIJAU, HIGH);
  delay(300);
  digitalWrite(LED_MERAH, HIGH);
  delay(300);
  tone(BUZZER_PIN, 1000);
  delay(300);
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_HIJAU, LOW);
  noTone(BUZZER_PIN);

  // Koneksi WiFi
  connectWiFi();

  // Setup MQTT
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  // Koneksi MQTT pertama kali
  reconnectMQTT();

  Serial.println("\n[SYS] Sistem siap. Mulai mengirim telemetry...\n");
}

// ── LOOP UTAMA ───────────────────────────────────────────────
void loop() {
  // Pastikan MQTT tetap terhubung
  if (!mqttClient.connected()) {
    Serial.println("[MQTT] Koneksi terputus! Reconnect...");
    reconnectMQTT();
  }

  // Proses pesan MQTT masuk (callback)
  mqttClient.loop();

  // Publish telemetry setiap 5 detik (non-blocking dengan millis)
  unsigned long now = millis();
  if (now - lastPublish >= publishInterval) {
    lastPublish = now;
    publishTelemetry();
  }
}
```

---

### 5.6 Penjelasan Detail Setiap Fungsi

```
FLOWCHART PERTEMUAN 2:

START
  │
  ▼
setup():
  - Build topic dari KELAS & KELOMPOK (auto-generate)
  - pinMode LED + Buzzer
  - dhtSensor.setup(D15, DHT22)
  - Self-test aktuator
  - connectWiFi() → Wokwi-GUEST
  - mqttClient.setServer + setCallback
  - reconnectMQTT() → subscribe TOPIC_CONTROL
  │
  ▼
loop():
  │
  ├─ mqttClient.connected()? ─── NO ──► reconnectMQTT()
  │                                              │
  ▼                                              ▼
  mqttClient.loop()  ◄──────────────────── kembali
  (proses pesan masuk → callback dipanggil)
  │
  ├─ millis() - lastPublish >= 5000?
  │     YES → publishTelemetry()
  │              ├─ Baca DHT22
  │              ├─ tentukanStatus()
  │              ├─ kendalikanAktuatorAuto() [skip jika MANUAL]
  │              ├─ Build JSON payload
  │              └─ mqttClient.publish(TOPIC_TELEMETRY, payload)
  │
  └─ kembali ke atas loop

SAAT PESAN KONTROL DATANG (interrupt-style via mqttClient.loop):
  mqttCallback() dipanggil otomatis
  ├─ LED_ON/LED_OFF      → digitalWrite LED_MERAH
  ├─ BUZZER_ON/OFF       → tone / noTone
  ├─ AUTO                → modeSistem = MODE_AUTO
  ├─ MANUAL              → modeSistem = MODE_MANUAL
  └─ RESET_ALARM         → matikan semua + mode AUTO
```

**Mengapa pakai `millis()` bukan `delay()`?**
- `delay(5000)` = ESP32 berhenti total 5 detik → pesan MQTT dari topic control TIDAK akan diproses
- `millis()` = non-blocking → ESP32 terus memanggil `mqttClient.loop()` → callback tetap responsif

---

### 5.7 Cara Setup MQTT Explorer

**Download & Install:**
- Windows/Mac/Linux: [https://mqtt-explorer.com](https://mqtt-explorer.com)

**Membuat Koneksi:**
1. Buka MQTT Explorer
2. Klik **+** (New Connection)
3. Isi:
   - Name: `HiveMQ Publik`
   - Host: `broker.hivemq.com`
   - Port: `1883`
   - Protocol: `mqtt://`
4. Klik **Connect**

**Subscribe & Lihat Data:**
1. Setelah terhubung, di panel kiri cari topic `upnjatim`
2. Expand tree sampai ke `telemetry` kelompok kamu
3. Panel kanan menampilkan payload JSON terbaru

**Mengirim Perintah Kontrol:**
1. Di MQTT Explorer, klik **Publish**
2. Topic: `upnjatim/iot/2026/kelasA/kelompok01/control`
3. Payload: `LED_ON` (atau perintah lainnya)
4. Klik **Publish**
5. Amati perubahan LED di simulator Wokwi

---

### 5.8 Tabel Pengujian Hari 2

**A. Tabel Telemetry Sensor:**

| No | Suhu (°C) | Kelembapan (%) | Status Ekspektasi | Payload Diterima | OK? |
|----|-----------|----------------|-------------------|-----------------|-----|
| 1  | 25.0      | 60.0           | NORMAL             | _____________ | ___ |
| 2  | 29.0      | 65.0           | WARNING_SUHU       | _____________ | ___ |
| 3  | 26.0      | 78.0           | WARNING_KELEMBAPAN | _____________ | ___ |
| 4  | 31.0      | 82.0           | WARNING_GANDA      | _____________ | ___ |
| 5  | 28.0      | 74.0           | NORMAL             | _____________ | ___ |

**B. Tabel Uji Perintah Kontrol:**

| No | Perintah Dikirim | Topic | Ekspektasi | Hasil Aktual | OK? |
|----|-----------------|-------|-----------|-------------|-----|
| 1  | `LED_ON`        | .../control | LED Merah menyala | _______ | ___ |
| 2  | `LED_OFF`       | .../control | LED Merah mati    | _______ | ___ |
| 3  | `BUZZER_ON`     | .../control | Buzzer berbunyi 1200Hz | _______ | ___ |
| 4  | `BUZZER_OFF`    | .../control | Buzzer mati       | _______ | ___ |
| 5  | `MANUAL`        | .../control | Mode manual aktif (sensor tidak kendalikan aktuator) | _______ | ___ |
| 6  | `AUTO`          | .../control | Mode auto aktif kembali | _______ | ___ |
| 7  | `RESET_ALARM`   | .../control | Semua aktuator mati, mode AUTO | _______ | ___ |

---

### 5.9 Troubleshooting

| Masalah | Gejala di Serial Monitor | Penyebab | Solusi |
|---------|--------------------------|---------|--------|
| WiFi tidak konek | `....` terus tanpa "Terhubung!" | SSID salah, simulasi belum start | Pastikan `Wokwi-GUEST`, password kosong string `""`. Restart simulasi. |
| MQTT gagal konek | `rc=-2` atau `rc=-4` | Broker down / internet bermasalah | Coba ulang. Cek koneksi internet laptop. `rc=-2` = server tidak ditemukan. |
| Data tidak muncul di MQTT Explorer | Topic kosong di Explorer | Topic subscribe salah | Copy-paste exact topic dari Serial Monitor. Case-sensitive! |
| Payload JSON error/kosong | Publish OK tapi payload aneh | String `snprintf` overflow | Perbesar buffer `payload[350]` atau kurangi panjang field |
| LED tidak merespons | Pesan kontrol muncul tapi LED tidak berubah | Mode MANUAL aktif atau pin salah | Kirim `AUTO` dulu, lalu coba LED_ON |
| `rc=-1` MQTT | Connection timeout | Broker publik penuh / overload | Coba `test.mosquitto.org` port `1883` sebagai alternatif |
| Sensor NaN | `[ERROR] Gagal membaca DHT22!` | Wiring salah atau library tidak terload | Periksa `diagram.json` pin D15, pastikan library DHTesp terinstall |
| Publish selalu GAGAL | `Publish: GAGAL ✗` | MQTT terputus saat publish | `reconnectMQTT()` akan otomatis dipanggil di loop berikutnya |

**Broker Alternatif jika HiveMQ down:**
```
test.mosquitto.org   port 1883
broker.emqx.io       port 1883
```
Ganti nilai `MQTT_SERVER` di kode.

---

### 5.10 Checklist Selesai Hari 2

- [ ] `KELAS` dan `KELOMPOK` sudah diganti sesuai data aktual
- [ ] `LOKASI` sudah disesuaikan
- [ ] Library `PubSubClient` terinstall di Wokwi
- [ ] Serial Monitor menampilkan: `[WiFi] Terhubung!` dengan IP address
- [ ] Serial Monitor menampilkan: `[MQTT] Terhubung ke broker!`
- [ ] Serial Monitor menampilkan: `[MQTT] Subscribe ke: upnjatim/iot/...`
- [ ] Serial Monitor menampilkan publish tiap 5 detik: `[MQTT-PUB] Sample #N | ...`
- [ ] MQTT Explorer terhubung ke `broker.hivemq.com:1883`
- [ ] Payload JSON terlihat di MQTT Explorer (struktur lengkap dengan semua field)
- [ ] `LED_ON` berhasil menyalakan LED Merah dari MQTT Explorer
- [ ] `LED_OFF` berhasil mematikan LED Merah dari MQTT Explorer
- [ ] `BUZZER_ON` berhasil mengaktifkan buzzer dari MQTT Explorer
- [ ] `BUZZER_OFF` berhasil mematikan buzzer dari MQTT Explorer
- [ ] `MANUAL` dan `AUTO` berfungsi mengubah mode sistem
- [ ] `RESET_ALARM` berfungsi mereset semua aktuator
- [ ] Tabel pengujian A & B terisi lengkap
- [ ] Screenshot: Serial Monitor WiFi connected, MQTT connected, publish log
- [ ] Screenshot: MQTT Explorer menampilkan payload JSON kelompok

---

## 6. FORMAT LAPORAN PRAKTIKUM

Gunakan struktur ini untuk laporan (PDF/DOCX):

```
HALAMAN JUDUL
  - Judul: "Laporan Praktikum IoT - Simulasi Smart Classroom dengan Wokwi"
  - Nama, NIM, Kelas, Kelompok
  - Link Proyek Wokwi Pertemuan 1: ___________
  - Link Proyek Wokwi Pertemuan 2: ___________
  - Tanggal: ___________

BAB 1 - TUJUAN PRAKTIKUM
  Minimal 3 tujuan per pertemuan (total 6 tujuan)

BAB 2 - DASAR TEORI
  2.1 Internet of Things — definisi, arsitektur, aplikasi
  2.2 ESP32 — spesifikasi, fitur WiFi
  2.3 Sensor DHT22 — cara kerja, akurasi, range
  2.4 Aktuator (LED & Buzzer) — cara kerja di ESP32
  2.5 Protokol MQTT — publish/subscribe, broker, topic, payload, QoS
  2.6 JSON Payload — struktur, kegunaan dalam IoT
  2.7 Wokwi Simulator — fitur, kelebihan vs hardware nyata

BAB 3 - ALAT DAN BAHAN VIRTUAL
  Tabel komponen, library, software, akun yang digunakan

BAB 4 - DESAIN SISTEM
  4.1 Diagram Arsitektur (dari modul Gambar 1)
  4.2 Diagram Rangkaian / Wiring
  4.3 Flowchart Program (Pertemuan 1 dan 2)
  4.4 Struktur Topic MQTT

BAB 5 - LANGKAH KERJA
  5.1 Pertemuan 1: membuat rangkaian, konfigurasi kode, pengujian
  5.2 Pertemuan 2: konfigurasi MQTT, pengujian telemetry, pengujian kontrol

BAB 6 - SOURCE CODE
  6.1 sketch.ino Pertemuan 1 (lengkap)
  6.2 sketch.ino Pertemuan 2 (lengkap)
  6.3 diagram.json

BAB 7 - HASIL PENGUJIAN
  7.1 Tabel Pengujian Pertemuan 1 (7 skenario)
  7.2 Tabel Pengujian Telemetry Pertemuan 2 (5 skenario)
  7.3 Tabel Pengujian Kontrol Pertemuan 2 (7 perintah)
  7.4 Screenshot rangkaian Wokwi
  7.5 Screenshot Serial Monitor (semua kondisi)
  7.6 Screenshot MQTT Explorer (topic tree + payload)

BAB 8 - PEMBAHASAN
  - Apakah hasil sesuai ekspektasi? Jelaskan
  - Error yang muncul selama praktikum dan cara mengatasi (min. 1 kasus)
  - Perbedaan threshold 28°C vs 30°C: dampak pada frekuensi warning
  - Analisis payload JSON: mengapa format JSON dipilih untuk IoT
  - Keterbatasan simulasi vs perangkat nyata
  Minimal 700 kata

BAB 9 - KESIMPULAN DAN SARAN
  - Pembelajaran utama dari praktikum
  - Rencana pengembangan ke real device

DAFTAR PUSTAKA

LAMPIRAN
  - Semua screenshot
  - Link proyek Wokwi
```

---

## 7. RUBRIK PENILAIAN & TARGET NILAI

| Aspek | Bobot | Yang Harus Ada untuk Nilai Tinggi |
|-------|-------|-----------------------------------|
| Rangkaian Wokwi | 15% | Semua komponen (termasuk LED hijau), wiring benar, simulasi berjalan |
| Kode sensor & aktuator | 20% | 4 varian status, threshold tugas, LED hijau, serial monitor informatif |
| Implementasi MQTT | 20% | WiFi connect, MQTT stabil, topic unik, publish + subscribe |
| Dashboard/monitoring | 10% | Payload terlihat di MQTT Explorer/Node-RED |
| Pengujian & troubleshooting | 15% | Tabel lengkap, ada kasus error + solusi |
| Laporan | 15% | Struktur lengkap, screenshot jelas, analisis ≥700 kata |
| Kreativitas | 5% | Mode AUTO/MANUAL/RESET, warning_reason, location, sample_no |

**Target: ≥ 85 (Sangat Baik)**

---

## CATATAN AKHIR UNTUK AI AGENT

1. **Saat membantu user setup project:** Buat semua file sekaligus sesuai struktur folder di Bagian 2
2. **Saat user dapat error kompilasi:** Periksa versi library, pastikan `DHTesp.h` dan `PubSubClient.h` terinstall
3. **Saat WiFi tidak konek di Wokwi:** SSID harus persis `Wokwi-GUEST`, password harus string kosong `""`
4. **Saat MQTT tidak konek:** `rc=-2` = server tidak reachable (cek internet). `rc=-4` = timeout. Sarankan coba broker alternatif
5. **Saat topic tidak muncul di MQTT Explorer:** Pastikan ESP32 sudah publish minimal 1 kali, subscribe di Explorer ke `upnjatim/#` (wildcard)
6. **Untuk tugas:** Ingatkan user untuk selalu mengganti `KELAS` dan `KELOMPOK` di kode sesuai data aktual
7. **Untuk laporan:** Analisis minimal 700 kata di BAB 8 adalah syarat nilai tinggi — bantu user mengembangkan poin-poin analisis

---

*Dokumen ini dibuat berdasarkan Modul Praktikum IoT dengan Wokwi — 2 Pertemuan, Program Studi Sistem Informasi, UPN "Veteran" Jawa Timur 2026.*
