#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>  //Kilit noktası olan kütüphane

//Rıdvan Gonca
//İçerik kaynağı: https://randomnerdtutorials.com/

#define WIFI_SSID ""      //İnternet İsmi
#define WIFI_PASSWORD ""  //İnternet Şifresi

//Yardımcı birimler
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

//Api Anahtarı ve DB Link Adresi (GİZLİ TUTUN!)
#define API_KEY ""
#define DATABASE_URL ""

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
const long sendDataIntervalMillis = 10000;

//Kullanıcı kayıt kontrol
bool signupOK = false;

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println(WIFI_SSID + " ağına bağlanılmaya çalışılıyor.") while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi bağlantısı başarılı.");

  //Kütüphanenin config dosyalarına aynı birimleri kaydediyoruz.
  //Burası ana bağlantıların yapıldığı kısım.
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Serial.print("Yeni kullancı kaydı oluşturuluyor.");
  //Aşağıdaki if döngüsü bize true/false döndürüyor. Sunucuya ise kullanıcı verisi gönderiyor.
  if (Firebase.signUp(&config, &auth, "", "")) {
      Serial.println("ok");
      signupOK = true;
    } else {
      Serial.printf("%s\n", config.signer.signupError.message.c_str());
      signupOK = false;
    }

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > sendDataIntervalMillis || sendDataPrevMillis == 0)) {
    //Firebase komutları burada yer alıcak. Son kontrol tarihi 19.02.2024 (Kullancı Kayıt Testi / Birim Kayıt ve Okuma Testi)
  }
}