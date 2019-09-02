#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial NodeMCU(D2,D3);
<<<<<<< HEAD

#include "ESP8266HTTPClient.h"
const char* ssid="AndroidAP_S10";
const char* password="Marvin25";
=======
const char* ssid="ARRIS-EA1A";
const char* password="2C8132173489";

//*********************************************************LOCATION
#define GOOGLE_KEY "AIzaSyDRvymLOxDMUHGYC4VS-BlH1MnWLDfzWfI"
WifiLocation location(GOOGLE_KEY);
String latitud, longitud;
>>>>>>> parent of 62cb28e... Update pruebaCon.ino


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
      delay(500);
      Serial.print(".");
  }
   Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  prueba();
  delay(5000);
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
