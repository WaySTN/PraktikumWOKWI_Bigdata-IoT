# Hasil Pengujian Praktikum IoT Wokwi

Dokumen ini disiapkan untuk mencatat hasil simulasi sesuai task pada [README.md](./README.md) dan panduan utama.

## Identitas Project

- KELAS: `pararel_B`
- KELOMPOK: `kelompok01`
- LOKASI: `twintowerB_lantai7_706`
- Topic telemetry: `upnjatim/iot/2026/pararel_B/kelompok01/telemetry`
- Topic control: `upnjatim/iot/2026/pararel_B/kelompok01/control`

## Pertemuan 1

File yang dipakai:

- [pertemuan-1/diagram.json](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-1/diagram.json)
- [pertemuan-1/sketch.ino](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-1/sketch.ino)
- [pertemuan-1/libraries.txt](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-1/libraries.txt)

### Checklist Run

- [x] Folder `pertemuan-1` dibuka sebagai workspace terpisah
- [x] `PlatformIO: Build` berhasil
- [x] Wokwi simulator `pertemuan-1` berhasil start
- [x] Library `DHT sensor library for ESPx` aktif
- [x] Self-test LED merah, LED hijau, dan buzzer berjalan saat boot
- [x] Serial Monitor menampilkan data tiap 2 detik

### Tabel Pengujian Hari 1

| No | Suhu (C) | Kelembapan (%) | Ekspektasi Status | Hasil Aktual | LED Merah | LED Hijau | Buzzer | Keterangan |
|----|----------|----------------|-------------------|--------------|-----------|-----------|--------|------------|
| 1 | 25.0 | 60.0 | NORMAL | NORMAL | OFF | ON | OFF | Kondisi ideal ruang kelas, hasil sesuai ekspektasi |
| 2 | 29.0 | 65.0 | WARNING_SUHU | WARNING_SUHU | ON | OFF | 1000Hz | Suhu > 28C, hasil sesuai ekspektasi |
| 3 | 26.0 | 78.0 | WARNING_KELEMBAPAN | WARNING_KELEMBAPAN | ON | OFF | 1200Hz | Kelembapan > 75%, hasil sesuai ekspektasi |
| 4 | 31.0 | 82.0 | WARNING_GANDA | WARNING_GANDA | ON | OFF | 1500Hz | Keduanya melewati batas, hasil sesuai ekspektasi |
| 5 | 28.0 | 75.0 | NORMAL | NORMAL | OFF | ON | OFF | Tepat di batas, sistem tetap NORMAL |
| 6 | 28.1 | 75.1 | WARNING_GANDA | WARNING_GANDA | ON | OFF | 1500Hz | Baru melewati batas, warning langsung aktif |
| 7 | 35.0 | 55.0 | WARNING_SUHU | WARNING_SUHU | ON | OFF | 1000Hz | Suhu tinggi, kelembapan normal, hasil sesuai ekspektasi |

### Bukti yang Harus Diambil

- [x] Screenshot rangkaian `pertemuan-1`
- [x] Screenshot Serial Monitor kondisi `NORMAL`
- [x] Screenshot Serial Monitor kondisi `WARNING_SUHU`
- [x] Screenshot Serial Monitor kondisi `WARNING_KELEMBAPAN`
- [x] Screenshot Serial Monitor kondisi `WARNING_GANDA`

Lokasi screenshot:

- [Screenshot 2026-05-12 143851.png](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20143851.png)
- [Screenshot 2026-05-12 183238.png](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20183238.png)
- [Screenshot 2026-05-12 183359.png](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20183359.png)
- [Screenshot 2026-05-12 183456.png](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20183456.png)
- [Screenshot 2026-05-12 183535.png](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-1/ss_pertemuan1/Screenshot%202026-05-12%20183535.png)

## Pertemuan 2

File yang dipakai:

- [pertemuan-2/diagram.json](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-2/diagram.json)
- [pertemuan-2/sketch.ino](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-2/sketch.ino)
- [pertemuan-2/libraries.txt](C:/laragon/www/praktikumbigdata_kelompok1/pertemuan-2/libraries.txt)

### Checklist Run

- [x] Folder `pertemuan-2` dibuka sebagai workspace terpisah
- [x] `PlatformIO: Build` berhasil
- [x] Wokwi simulator `pertemuan-2` berhasil start
- [x] WiFi `Wokwi-GUEST` terhubung
- [x] MQTT broker `broker.hivemq.com:1883` terhubung
- [x] Subscribe topic control berhasil
- [x] Publish telemetry muncul tiap 5 detik
- [x] MQTT Explorer terhubung ke broker

### Tabel Pengujian Telemetry

| No | Suhu (C) | Kelembapan (%) | Status Ekspektasi | Payload Diterima | OK? |
|----|----------|----------------|-------------------|------------------|-----|
| 1 | 25.0 | 60.0 | NORMAL | JSON diterima, status `NORMAL`, field payload lengkap | Ya |
| 2 | 29.0 | 65.0 | WARNING_SUHU | JSON diterima, status `WARNING_SUHU`, payload sesuai kondisi sensor | Ya |
| 3 | 26.0 | 78.0 | WARNING_KELEMBAPAN | JSON diterima, status `WARNING_KELEMBAPAN`, payload sesuai kondisi sensor | Ya |
| 4 | 31.0 | 82.0 | WARNING_GANDA | JSON diterima, status `WARNING_GANDA`, payload sesuai kondisi sensor | Ya |
| 5 | 28.0 | 74.0 | NORMAL | JSON diterima, status `NORMAL`, nilai masih di bawah threshold | Ya |

### Tabel Pengujian Control MQTT

| No | Perintah Dikirim | Topic | Ekspektasi | Hasil Aktual | OK? |
|----|------------------|-------|------------|--------------|-----|
| 1 | `LED_ON` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | LED Merah menyala | LED merah menyala dan log `MQTT-CONTROL` muncul di terminal | Ya |
| 2 | `LED_OFF` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | LED Merah mati | LED merah mati dan log kontrol diterima | Ya |
| 3 | `BUZZER_ON` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Buzzer bunyi 1200Hz | Buzzer aktif dan log kontrol diterima | Ya |
| 4 | `BUZZER_OFF` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Buzzer mati | Buzzer mati dan log kontrol diterima | Ya |
| 5 | `MANUAL` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Mode manual aktif | Mode sistem berubah ke `MANUAL` sesuai log terminal | Ya |
| 6 | `AUTO` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Mode auto aktif kembali | Mode sistem kembali ke `AUTO` sesuai log terminal | Ya |
| 7 | `RESET_ALARM` | `upnjatim/iot/2026/pararel_B/kelompok01/control` | Aktuator reset dan AUTO | Aktuator reset, mode kembali `AUTO`, dan log kontrol tampil | Ya |

### Payload Minimal yang Harus Terlihat

```json
{
  "device_id": "esp32-kelompok01",
  "temperature": 27.50,
  "humidity": 68.20,
  "status": "NORMAL",
  "warning_reason": "none",
  "location": "twintowerB_lantai7_706",
  "sample_no": 1,
  "mode": "AUTO",
  "uptime_ms": 5000
}
```

### Bukti yang Harus Diambil

- [x] Screenshot Serial Monitor saat WiFi connect
- [x] Screenshot Serial Monitor saat MQTT connect
- [x] Screenshot Serial Monitor saat publish telemetry
- [x] Screenshot MQTT Explorer menampilkan topic telemetry
- [x] Screenshot MQTT Explorer menampilkan payload JSON
- [x] Screenshot saat uji `LED_ON` atau `RESET_ALARM`

## Status Task Aktual

- [x] Struktur workspace praktikum dibuat
- [x] File pertemuan 1 lengkap
- [x] File pertemuan 2 lengkap
- [x] Struktur PlatformIO per folder siap
- [x] KELAS diisi: `pararel_B`
- [x] KELOMPOK diisi: `kelompok01`
- [x] LOKASI diisi: `twintowerB_lantai7_706`
- [x] Uji 7 skenario pertemuan 1
- [x] Uji telemetry MQTT pertemuan 2
- [x] Uji perintah control MQTT
- [x] Pengambilan screenshot bukti
- [x] Penyusunan laporan praktikum
