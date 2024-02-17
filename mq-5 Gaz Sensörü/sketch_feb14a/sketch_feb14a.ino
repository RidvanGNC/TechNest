#include <SoftwareSerial.h>
//MuhammedcaN özcan
// ESP8266 modülünün RX ve TX pinleri
#define RX 2
#define TX 3

SoftwareSerial esp8266(RX, TX); 

// Gaz sensörü için kullanılacak analog pin
int gazSensoruPin = A0;

// WiFi ağı bilgileri
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// Sunucu bilgileri
const char* server = "your_server_address";
const int port = 80;

void setup() {
  Serial.begin(9600); // Seri iletişimi başlat
  esp8266.begin(9600); // ESP8266 iletişim hızı
  delay(1000); // İlk başlatma için biraz bekleyelim

  connectWiFi(); // WiFi'ye bağlan
}

void loop() {
  // Gaz sensöründen okunan değeri al
  int gazDegeri = analogRead(gazSensoruPin);

  // Eğer gaz algılandıysa
  if (gazDegeri > 500) {
    // JSON verisi oluştur
    String jsonStr = "{\"gazAlgildi\":true,\"gazDegeri\":" + String(gazDegeri) + "}";

    // JSON verisini sunucuya gönder
    sendData(jsonStr);

    delay(5000); // Veri gönderdikten sonra beş saniye bekleyin
  }
}

void connectWiFi() {
  esp8266.println("AT+RST"); // ESP8266 modülünü yeniden başlat
  delay(1000);
  esp8266.println("AT+CWMODE=1"); // WiFi modülünü istemci moduna ayarla
  delay(1000);
  esp8266.println("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\""); // WiFi ağına bağlan
  delay(3000);
}

void sendData(String data) {
  esp8266.println("AT+CIPSTART=\"TCP\",\"" + String(server) + "\"," + port); // TCP bağlantısı başlat
  delay(2000);
  esp8266.println("AT+CIPSEND=" + String(data.length() + 4)); // Veri uzunluğunu gönder
  delay(1000);
  esp8266.println("POST /your_endpoint HTTP/1.1"); // HTTP POST isteği
  esp8266.println("Host: " + String(server));
  esp8266.println("Content-Type: application/json");
  esp8266.println("Content-Length: " + String(data.length())); // Veri uzunluğunu belirt
  esp8266.println();
  esp8266.println(data); // JSON verisini gönder
  delay(500);
  esp8266.println("AT+CIPCLOSE"); // Bağlantıyı kapat
}
