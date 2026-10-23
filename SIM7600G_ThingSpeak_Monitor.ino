#include <SoftwareSerial.h>
#include "DHT.h"

// إعدادات الحساس
#define DHTPIN 2     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

// إعدادات الموديول
SoftwareSerial sim7600(8, 9); 

// ضع مفتاحك الصحيح هنا (تأكد منه من الموقع)
String apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY"; 

void setup() {
  Serial.begin(115200);
  sim7600.begin(115200);
  dht.begin();
  
  Serial.println("--- System Starting ---");
  delay(5000); 

  // تهيئة الشبكة
  setupNetwork();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Sensor Error!");
  } else {
    Serial.print("Temp: "); Serial.print(t);
    Serial.print(" | Hum: "); Serial.println(h);
    
    // إرسال البيانات
    sendData(t, h);
  }

  // انتظر 30 ثانية (ضروري لـ ThingSpeak ولعدم حدوث 406)
  Serial.println("Waiting 30s...");
  delay(30000); 
}

void setupNetwork() {
  sim7600.println("AT+CGDCONT=1,\"IP\",\"m2ms.orange.jo\"");
  delay(2000);
  sim7600.println("AT+CGACT=1,1");
  delay(4000);
  sim7600.println("AT+NETOPEN");
  delay(3000);
}

void sendData(float temp, float hum) {
  sim7600.println("AT+HTTPINIT");
  delay(1000);

  // إعداد المحتوى لتجنب خطأ 406
  sim7600.println("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"");
  delay(1000);

  // بناء الرابط
  String url = "AT+HTTPPARA=\"URL\",\"http://api.thingspeak.com/update?api_key=";
  url += apiKey;
  url += "&field1="; url += String(temp);
  url += "&field2="; url += String(hum);
  url += "\"";

  sim7600.println(url);
  delay(1500);

  Serial.println("Sending to ThingSpeak...");
  sim7600.println("AT+HTTPACTION=0");
  
  // انتظر الرد واطبعه لمراقبته
  delay(5000); 
  while(sim7600.available()) {
    Serial.write(sim7600.read());
  }

  sim7600.println("AT+HTTPTERM");
  delay(1000);
}