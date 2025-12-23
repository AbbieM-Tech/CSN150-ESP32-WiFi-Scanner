#include <WiFi.h>

String encTypeToStr(wifi_auth_mode_t encType) {
  switch (encType) {
    case WIFI_AUTH_OPEN: return "OPEN";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2-ENT";
    case WIFI_AUTH_WPA3_PSK: return "WPA3";
    case WIFI_AUTH_WPA2_WPA3_PSK: return "WPA2/WPA3";
    default: return "UNKNOWN";
  }
}

int rssiBars(int rssi) {
  if (rssi >= -55) return 4;
  if (rssi >= -65) return 3;
  if (rssi >= -75) return 2;
  if (rssi >= -85) return 1;
  return 0;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);   // true = clear old connection info
  delay(200);

  Serial.println("ESP32 WiFi Scanner Started");
  Serial.println("Scanning without connecting (passive discovery only).");
  Serial.println("--------------------------------------------------");
}

void loop() {
  Serial.println("\nScanning for WiFi networks...");
  int n = WiFi.scanNetworks(false, true); // (async=false, show_hidden=true)

  if (n <= 0) {
    Serial.println("No networks found.");
  } else {
    Serial.print("Networks found: ");
    Serial.println(n);

    for (int i = 0; i < n; i++) {
      String ssid = WiFi.SSID(i);
      int rssi = WiFi.RSSI(i);
      int ch = WiFi.channel(i);
      String bssid = WiFi.BSSIDstr(i);
      String enc = encTypeToStr(WiFi.encryptionType(i));

      Serial.print(i + 1);
      Serial.print(") SSID: ");
      Serial.print(ssid.length() ? ssid : "<hidden>");
      Serial.print(" | RSSI: ");
      Serial.print(rssi);
      Serial.print(" dBm (");
      Serial.print(rssiBars(rssi));
      Serial.print("/4 bars)");
      Serial.print(" | CH: ");
      Serial.print(ch);
      Serial.print(" | ENC: ");
      Serial.print(enc);
      Serial.print(" | BSSID: ");
      Serial.println(bssid);

      delay(10);
    }
  }

  WiFi.scanDelete(); // frees memory from scan results
  Serial.println("--------------------------------------------------");
  delay(5000);
}