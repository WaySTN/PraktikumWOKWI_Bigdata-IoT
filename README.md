# Praktikum Big Data IoT dengan Wokwi

Proyek ini berisi implementasi praktikum **Big Data IoT** menggunakan **ESP32 virtual di Wokwi** untuk studi kasus **Smart Classroom Monitor**. Sistem memantau suhu dan kelembapan menggunakan sensor **DHT22**, mengendalikan **LED** dan **buzzer** sebagai indikator, lalu pada tahap lanjutan mengirim data telemetry ke **broker MQTT** dan menerima perintah remote control.

Repository ini disusun untuk 2 pertemuan:

- **Pertemuan 1**: sensor, aktuator, dan logika otomasi lokal
- **Pertemuan 2**: MQTT telemetry dan remote control

## Fitur

- Simulasi ESP32 + DHT22 + LED merah + LED hijau + buzzer di Wokwi
- Threshold suhu `28 C` dan kelembapan `75%`
- 4 status sistem:
  - `NORMAL`
  - `WARNING_SUHU`
  - `WARNING_KELEMBAPAN`
  - `WARNING_GANDA`
- Telemetry MQTT ke broker publik `broker.hivemq.com:1883`
- Remote control MQTT:
  - `LED_ON`
  - `LED_OFF`
  - `BUZZER_ON`
  - `BUZZER_OFF`
  - `MANUAL`
  - `AUTO`
  - `RESET_ALARM`
- Laporan praktikum lengkap dan hasil pengujian terdokumentasi

## Struktur Repository

```text
praktikumbigdata_kelompok1/
|- pertemuan-1/
|  |- .vscode/
|  |- src/
|  |- ss_pertemuan1/
|  |- diagram.json
|  |- libraries.txt
|  |- platformio.ini
|  |- sketch.ino
|  `- wokwi.toml
|- pertemuan-2/
|  |- .vscode/
|  |- src/
|  |- ss_pertemuan2/
|  |- diagram.json
|  |- libraries.txt
|  |- platformio.ini
|  |- sketch.ino
|  `- wokwi.toml
|- HASIL_PENGUJIAN.md
`- README.md
```

## Konfigurasi Project

Konfigurasi identitas project pada Pertemuan 2:

- `KELAS`: `pararel_B`
- `KELOMPOK`: `kelompok01`
- `LOKASI`: `twintowerB_lantai7_706`

Topic MQTT yang digunakan:

- Telemetry: `upnjatim/iot/2026/pararel_B/kelompok01/telemetry`
- Control: `upnjatim/iot/2026/pararel_B/kelompok01/control`

## Prasyarat

Untuk menjalankan project dari VS Code:

- [VS Code](https://code.visualstudio.com/)
- Extension `Wokwi Simulator`
- Extension `PlatformIO IDE`
- MQTT Explorer desktop untuk monitoring MQTT

## Cara Mencoba Project

### 1. Menjalankan Pertemuan 1

1. Buka folder [pertemuan-1](./pertemuan-1) sebagai workspace terpisah di VS Code.
2. Jalankan `PlatformIO: Build`.
3. Jalankan `Wokwi: Start Simulator`.
4. Ubah nilai `temperature` dan `humidity` pada komponen DHT22.
5. Amati output di terminal Wokwi:
   - status sistem
   - LED merah
   - LED hijau
   - buzzer

Skenario pengujian utama:

| Suhu (C) | Kelembapan (%) | Ekspektasi |
|----------|----------------|------------|
| 25.0 | 60.0 | `NORMAL` |
| 29.0 | 65.0 | `WARNING_SUHU` |
| 26.0 | 78.0 | `WARNING_KELEMBAPAN` |
| 31.0 | 82.0 | `WARNING_GANDA` |
| 28.0 | 75.0 | `NORMAL` |

### 2. Menjalankan Pertemuan 2

1. Buka folder [pertemuan-2](./pertemuan-2) sebagai workspace terpisah di VS Code.
2. Jalankan `PlatformIO: Build`.
3. Jalankan `Wokwi: Start Simulator`.
4. Pastikan terminal menampilkan:
   - koneksi WiFi berhasil
   - koneksi broker MQTT berhasil
   - subscribe ke topic control berhasil
   - publish telemetry periodik berhasil
5. Buka MQTT Explorer desktop dan connect ke:
   - Host: `broker.hivemq.com`
   - Port: `1883`
   - Protocol: `mqtt://`
   - TLS: `OFF`
6. Subscribe atau lihat tree topic:
   - `upnjatim/iot/2026/pararel_B/kelompok01/telemetry`
7. Verifikasi payload JSON telemetry.
8. Kirim perintah ke topic control untuk menguji remote control.

### 3. Payload Telemetry

Contoh payload yang dikirim:

```json
{
  "device_id": "esp32-kelompok01",
  "temperature": 26.00,
  "humidity": 60.00,
  "status": "NORMAL",
  "warning_reason": "none",
  "location": "twintowerB_lantai7_706",
  "sample_no": 79,
  "mode": "AUTO",
  "uptime_ms": 395005
}
```

### 4. Perintah Control MQTT

Gunakan topic berikut:

```text
upnjatim/iot/2026/pararel_B/kelompok01/control
```

Payload yang didukung:

- `LED_ON`
- `LED_OFF`
- `BUZZER_ON`
- `BUZZER_OFF`
- `MANUAL`
- `AUTO`
- `RESET_ALARM`

## Hasil Akhir

Seluruh pengujian utama telah berhasil dilakukan:

- Pengujian 7 skenario Pertemuan 1: **selesai**
- Pengujian telemetry MQTT Pertemuan 2: **selesai**
- Pengujian control MQTT Pertemuan 2: **selesai**
- Screenshot bukti praktikum: **tersedia**
- Laporan praktikum: **tersedia**

Dokumen hasil pengujian:

- [Hasil Pengujian](./HASIL_PENGUJIAN.md)

Folder screenshot:

- [Screenshot Pertemuan 1](./pertemuan-1/ss_pertemuan1)
- [Screenshot Pertemuan 2](./pertemuan-2/ss_pertemuan2)

## Catatan

- `diagram.json` Pertemuan 2 menggunakan rangkaian yang sama dengan Pertemuan 1.
- `wokwi.toml` di setiap folder diarahkan ke output build PlatformIO.
- Jika ingin memakai data kelompok lain, ubah nilai `KELAS`, `KELOMPOK`, dan `LOKASI` pada file `pertemuan-2/src/main.cpp`.
