#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <DHT11.h>
#include<DHT.h>
#include <WiFiClient.h>
#define pinDHT 2
#define DHTTYPE DHT11
DHT dht (pinDHT,DHTTYPE);
ESP8266WiFiMulti WiFiMulti;
String serverName = "http://192.168.25.54:8000/temp/";
String Humidity = "/Humidity/";

char link;
void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SK_WiFi4FED", "1402033324");
}
void loop() {
  int h=dht.readHumidity();
  int t=dht.readTemperature();
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

   
   
      HTTPClient http;

      Serial.print("[HTTP] begin...\n");
      
      delay(100);
      String serverPath = serverName + t + Humidity + h;
      if (http.begin(client, serverPath.c_str())) {  // HTTP


        Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
        int httpCode = http.GET();

      // httpCode will be negative on error
        if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.println(serverPath.c_str());
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.println(serverPath.c_str());
      Serial.printf("[HTTP} Unable to connect\n");
    }
    
    

    
    
  }

  delay(100);
}
