#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <DHT11.h>
#include <WiFiClient.h>
DHT11 dht11(2);
ESP8266WiFiMulti WiFiMulti;
String serverName = "http://192.168.25.54:8000/temp/";
String Humidity = "/Humidity/";
int humidity=0;//습도
int temp=0;//온도
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
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

   
   
      HTTPClient http;

      Serial.print("[HTTP] begin...\n");
      
      
      delay(100);
      String serverPath = serverName + temp + Humidity + humidity;

  }else{
   Serial.print("[HTTP] NO...\n");
  }
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
  int err;


  if((err=dht11.read(humidity, temp))==0)

  {

    Serial.print("temperature:");

    Serial.print(temp);

    Serial.print(" humidity:");

    Serial.print(humidity);

    Serial.println();

  }

  else

  {

    Serial.println();

    Serial.print("Error No :");

    Serial.print(err);

    Serial.println();    

  }


}
