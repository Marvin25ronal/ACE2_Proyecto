#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <NTPClient.h>              //https://github.com/taranais/NTPClient
#include <WiFiUdp.h>
#include "ESP8266HTTPClient.h"
#include "WifiLocation.h"           //https://github.com/gmag11/WifiLocation

SoftwareSerial NodeMCU(D2,D3);
<<<<<<< HEAD

const char* ssid="AndroidAP_S10";

#define GOOGLE_KEY "AIzaSyDRvymLOxDMUHGYC4VS-BlH1MnWLDfzWfI"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );
  NodeMCU.begin(9600);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(1000);
      Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  //LOCATION
  location_t loc = location.getGeoFromWiFi();
  //Serial.println("Location request data");
  Serial.println(location.getSurroundingWiFiJson());
  latitud = String(loc.lat, 7);
  longitud = String(loc.lon, 7);
  Serial.println("Latitude: " + latitud);
  Serial.println("Longitude: " + longitud);
  Serial.println("Accuracy: " + String(loc.accuracy));
  
  //TIME
  timeClient.begin();
  timeClient.setTimeOffset(-21600);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  //prueba();
  //delay(5000);
  
  //TIME
  getTime();
}

void getTime(){
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  String formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  
  fecha = formattedDate.substring(0, splitT);
  Serial.print("Fecha: ");
  Serial.println(fecha);

  tiempo = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.print("Tiempo: ");
  Serial.println(tiempo);
  delay(1000);
}

void prueba(){
  if(WiFi.status()==WL_CONNECTED){
    HTTPClient http;
    Serial.print("[HTTP] begin..\n");
   //http.begin("http://www.json-generator.com/api/json/get/cquDZXUdiW?indent=2"); //HTTP
   http.begin("https://arqui2-prueba2.herokuapp.com/pendiente", "9ba996f2c2eb712b55920dcebf39532761a7b8bd"); //HTTPS
    Serial.println("[HTTP] GET ...");
    int httpCode=http.GET();
    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        //Mandar datos al arduino

        if(payload.length()==0||payload.equals("null")){
          Serial.println("Esta vacia");
        }else{
          //se manda al arduino
          NodeMCU.println(payload);
          bool esperar=true;
          while(esperar==true){
            
            while(NodeMCU.available()>0){
              
              String mensaje=NodeMCU.readStringUntil('\n');
              Serial.println(mensaje);
              if(((char)mensaje[0])=='y'){
                esperar=false;
                
                delay(50);
                break;
              }
            }
            delay(100);
          }
        }
        Serial.print("ok");
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }else {
    Serial.print("Error al enviar");
  }
  delay(10);
}
