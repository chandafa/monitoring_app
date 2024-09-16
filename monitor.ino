/*
 Tutorial by IOTkece.com
*/


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define BLYNK_PRINT Serial 

#define DHTTYPE DHT11
#define DHTPIN 13

DHT dht(DHTPIN, DHTTYPE);

float humidity, temp;                
unsigned long previousMillis = 0;
const long interval = 15000;        

char auth[] = "Isikan kode auth yang dikirim blynk ke E-mail anda"; 
char ssid[] = "Nama Wifi Anda";
char pass[] = "Password Anda"; // Jika tidak menggunakan password kosongkan ""


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

bool isFirstConnect = true;

BLYNK_CONNECTED() {
  if (isFirstConnect)
  {
    Blynk.syncAll();
    isFirstConnect = false;
  }
}

void loop()
{
  Blynk.run();
  gettemperature();
}

void gettemperature() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

   
    humidity = dht.readHumidity();        
    temp = dht.readTemperature(); 
    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, humidity);

    
    if (isnan(humidity) || isnan(temp)) {
      Serial.println("Sensor Tidak Terbaca");
      return;
    }
  }
}
