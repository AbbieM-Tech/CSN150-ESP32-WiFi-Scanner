# ESP32 Wi‑Fi Scanner (Passive Network Discovery)

A simple ESP32 sketch that **scans** for nearby Wi‑Fi networks and prints results to the **Arduino Serial Monitor**—including **SSID**, **signal strength (RSSI)**, **channel**, **BSSID**, and **encryption type**.

## 1) Project overview & resources

### What this tool does
- Sets the ESP32 to **Station mode** (listener/client mode).
- Runs `WiFi.scanNetworks()` repeatedly.
- Displays nearby network metadata (name, signal, channel, encryption).

### What this tool does NOT do
- It **does not connect** to any Wi‑Fi network.
- It **does not capture packets**, passwords, or user data.
- It **does not attempt any intrusion**—this is visibility/measurement only.

### Recommended resources
- ESP32 Arduino Wi‑Fi API (Espressif Arduino‑ESP32 docs): https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html
- Official Arduino “Scan Networks” example (conceptual reference): https://www.arduino.cc/en/Tutorial/ScanNetworks
- Arduino‑ESP32 WiFiScan example sketch (reference implementation): https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiScan/WiFiScan.ino

---

## 2) Step‑by‑step installation / configuration

### Hardware
- ESP32 board (works on most ESP32 dev boards; ESP32‑CAM also works for scanning)
- USB cable / serial adapter (if using ESP32‑CAM)

### Software
- Arduino IDE 2.x
- ESP32 board package installed in Arduino IDE (Boards Manager)

### Arduino IDE setup (ESP32 boards package)
1. Open **Arduino IDE** → **Tools** → **Board** → **Boards Manager…**
2. Search: **ESP32**
3. Install: **“esp32 by Espressif Systems”**
4. Select your board:
   - Example: **AI Thinker ESP32‑CAM** (if that’s what you have)  
   - Or any ESP32 Dev Module you’re using
5. Select the correct **Port** (Tools → Port).

### Upload & Serial Monitor
1. Click **Upload**.
2. If you use ESP32‑CAM: you may need to hold **BOOT** while uploading, then release when upload starts (depends on your adapter/wiring).
3. Open **Tools → Serial Monitor**.
4. Set baud rate to **115200** (must match `Serial.begin(115200);`).

---

## 3) Running the demo

1. Upload the sketch.
2. Open Serial Monitor at **115200 baud**.
3. You should see:
   - “Scanning for WiFi networks…”
   - A numbered list of networks + RSSI + channel + encryption type

### Sample output
```
Networks found: 6
1) SSID: MyWiFi | RSSI: -52 dBm (4/4 bars) | CH: 6 | ENC: WPA2 | BSSID: AA:BB:CC:DD:EE:FF
2) SSID: <hidden> | RSSI: -79 dBm (2/4 bars) | CH: 11 | ENC: WPA2/WPA3 | BSSID: 11:22:33:44:55:66
--------------------------------------------------
```

---

## 4) Code notes (how it works)

### Key calls
- `WiFi.mode(WIFI_STA);`  
  Sets the ESP32 to station mode for scanning/listening.
- `WiFi.scanNetworks(...)`  
  Performs a scan and returns the number of detected networks.
- `WiFi.SSID(i)`, `WiFi.RSSI(i)`, `WiFi.channel(i)`, `WiFi.BSSIDstr(i)`  
  Reads details for each network entry.
- `WiFi.encryptionType(i)`  
  Returns the encryption/auth mode as an enum value (we map it to readable text).
- `WiFi.scanDelete()`  
  Frees memory used by the scan results.

---

## 5) Troubleshooting notes & challenges encountered

### A) Compile error: `Serial` has no member named `prinln`
**Cause:** typo — `prinln` missing the `t`.  
**Fix:** change to `Serial.println(...)`.

### B) Serial Monitor shows “gibberish”
**Cause:** baud rate mismatch.  
**Fix:** set Serial Monitor to **115200**.

### C) Upload fails / stuck (ESP32‑CAM common)
- Try holding **BOOT** while clicking Upload.
- Check you selected the correct **Board** and **Port**.
- Make sure your serial adapter is 3.3V logic and wired correctly.

### D) Some networks show `<hidden>`
That means the SSID is not broadcast (hidden SSID). The network may still exist and be detected, but its name isn’t advertised.

---

## 6) Ethical & responsible use
This project is intended for **authorized** learning and measurement:
- Only scan in environments where you have permission (your home, lab, classroom demo).
- Don’t use the results to target networks you don’t own or control.
- Avoid publishing full BSSIDs or identifiable network names publicly unless approved.
