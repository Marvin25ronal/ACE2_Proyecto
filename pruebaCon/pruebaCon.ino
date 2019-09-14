#include <ESP8266WiFi.h>        //https://arduino.esp8266.com/stable/package_esp8266com_index.json
#include <SoftwareSerial.h>
#include <NTPClient.h>              //https://github.com/taranais/NTPClient
#include <WiFiUdp.h>
#include "ESP8266HTTPClient.h"
#include <WifiLocation.h>           //https://github.com/gmag11/WifiLocation




SoftwareSerial NodeMCU(D2,D3);



const char* ssid="TURBONETT";
const char* password="GAP55841383";

//*********************************************************LOCATION
#define GOOGLE_KEY "AIzaSyB4m5_Jw5YIVO-lIk5CA7niezR90XZYPEA"
WifiLocation location(GOOGLE_KEY);
String latitud, longitud;
// latitud 14.6481152 longitud -90.5723877 casa de pablo
//*********************************************************TIME
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
// Variables to save date and time
String fecha, tiempo;

 String datos = "";

double minutos =15;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NodeMCU.begin(4800);
  
  //pinMode(2,OUTPUT);
  /*Serial.print("Wifi connecting to ");
  Serial.println( ssid );*/
  
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");
  while( WiFi.status() != WL_CONNECTED ){
      delay(1000);
       //Serial.println("Connectando");
      //Serial.print(".");
  }
 // Serial.println();
 // Serial.println("Wifi Connected Success!");
 // Serial.print("NodeMCU IP Address : ");
 // Serial.println(WiFi.localIP() );

  //LOCATION
  location_t loc = location.getGeoFromWiFi();
  //Serial.println("Location request data");
  //Serial.println(location.getSurroundingWiFiJson());
  latitud = String(loc.lat, 7);
  longitud = String(loc.lon, 7);
  /*Serial.println("Latitude: " + latitud);
  Serial.println("Longitude: " + longitud);
  Serial.println("Accuracy: " + String(loc.accuracy));*/
  
  //TIME
  timeClient.begin();
  timeClient.setTimeOffset(-21600);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(2,HIGH);
  //prueba();
  //delay(5000);
 //datos = "{\n \"peso\":2,  \"temperatura\":10, \"calidadaire\":300, \"hayagua\":true, \"fecha\":\"04/09/2019\", \"hora\":";
  //TIME
 // Serial.print("en loop");
  
  //delay(1000);
  getTime();
latitud = "14.6481152";
longitud = "-90.5723877";
  
  String informacion_gps="";
  informacion_gps=latitud;
  informacion_gps+=",";
  informacion_gps+=longitud;
  informacion_gps+=",";
  informacion_gps+=fecha;
  informacion_gps+=",";
  informacion_gps+=tiempo;
  informacion_gps+=",";

  
  
  
  
NodeMCU.println(informacion_gps); // pasa sensor gps a arduino   

 String datos_prueba= "5,27,340,10,12/12/12,10:10:10"; // los datos separados por comas 

//Serial.println(datos_prueba);
 
 /*metodo_post(datos_prueba); // enviar datos aleatorios de prueba*/
 //delay(60000*minutos); // tiempo de siguiente envio
 //lo de abajo es la conexion con arduino
 //
 String arduino_info="";
  if(NodeMCU.available()>0){
    arduino_info = NodeMCU.readStringUntil('\n');  // resive del arduino la info  
    Serial.print(arduino_info);
    Serial.print("\n");
      metodo_post(arduino_info);  // metodo para enviar post con los datos de arduino
    delay(60000* minutos);
  }
  delay(200);
   
}

void getTime(){
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  String formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  
  fecha = formattedDate.substring(0, splitT);
  //Serial.print("Fecha: ");
  //Serial.println(fecha);

  tiempo = formattedDate.substring(splitT+1, formattedDate.length()-1);
  //Serial.print("Tiempo: ");
  //Serial.println(tiempo);
  //delay(500);
}

 
void metodo_post(String datos_sensores){
  
   String str = "";
  // String datos_sensores ="1,2,3,4,5,6";
  String  lista_sensores [6];
  for (int i = 0; i < 6 ; i++)
      {
         
         lista_sensores[i] = getValue(datos_sensores,',',i);
        
      }

  // CREANDO DATOS EN FORMATO JSON {"peso":0,"temperatura":2,"calidadaire":0,"hayagua":3,"fecha":"04/09/2019","hora":"01:01:01","posicion":"prueba"}

  
  datos="{ \"peso\":";
  datos+="\"";
  datos+=lista_sensores[3];//peso-----
  datos+="\" ,";
  datos+=" \"temperatura\":";
  datos+="\"";
  datos+=lista_sensores[0];//temperatura -----
  datos+="\" ,";
  datos+=" \"calidadaire\":";
  datos+="\"";
  datos+=lista_sensores[2]; // calidad del aire
  datos+="\" ,";
  datos+=" \"hayagua\":";
  datos+="\"";
  datos+=lista_sensores[1];// va hacer el int del agua
  datos+="\" ,";


  datos+=" \"fecha\":";
  datos+="\"";
  datos+=fecha;
  datos+="\" ,";
  datos+=" \"hora\":";
  datos+="\"";
  datos+=tiempo;
  datos+="\" , ";
  datos+=" \"posicion\":";
  datos+="\"";
  datos+=latitud;
  datos+=",";
  datos+=longitud;
  datos+="\" }";



  
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
       HTTPClient http;    //Declare object of class HTTPClient
   //  String datos = "{\n \"peso\":0,  \"temperatura\":2, \"calidadaire\":0, \"hayagua\":false, \"fecha\":\"04/09/2019\", \"hora\": \"01:01:01\",  \"posicion\": \"prueba\" }";
       http.begin("http://arqui2proyecto1.appspot.com/api/Estados");      //Specify request destination
       http.addHeader("Content-Type", "application/json");  //Specify content-type header
     
       int httpCode = http.POST(datos);   //Send the request

      //  Serial.println(datos);
      // Serial.print("*");
      // Serial.print(httpCode);
      // Serial.println("*");
       String payload = http.getString();                  //Get the response payload
     
      // Serial.println(httpCode);   //Print HTTP return code
       //Serial.println(payload);    //Print request response payload
     
       http.end();  //Close connection
 
    }  else{
 
      //Serial.println("Error in WiFi connection");   
 
  }
 
    //delay(20000);  //Send a request every 30 seconds
  
  }

  String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
