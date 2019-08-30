#include <HX711_ADC.h> // https://github.com/olkal/HX711_ADC
#include <Wire.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>      //https://github.com/mikalhart/TinyGPS
#include <DHT.h>
#include <DHT_U.h>

//Trig,echo

Ultrasonic ultrasonic(3, 2);
float calibrar = 900.0;
HX711_ADC LoadCell(4, 5);
const int analogInPin = A0;

int distancia = 0;
boolean hayLiquido = false;
float peso = 0;
boolean lleno = false;
int contador_de_uso = 0;
float temperatura = 0;

int dist_max = 20;
int tU0 = 0;
int tUf = 0;
int tL0 = 0;
int tLf = 0;
boolean estaEchando = false;
boolean seVaALlenar = false;

//GPS
TinyGPS gps_obj;
SoftwareSerial gps(22,23); // RX, TX
char dato=' ';

//TEMPERATURA
DHT dht(40, DHT11);

//GAS
// Pin del Arduino donde conectamos la pata A0 del módulo
#define GAS_PIN A1
// Cambio en las lecturas (en porcentaje) que consideraremos significativo
#define CAMBIO_SIGNIFICATIVO 3

int metano = -1;

void setup() {
  Serial.begin(9600); // start connection to HX711
  Serial.println("INICIO");
  /*LoadCell.begin();
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  Serial.println("Ya se estabilizó");
  LoadCell.setCalFactor(calibrar); // calibration factor for load cell => strongly dependent on your individual setup
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(13,OUTPUT);*/

  //SERIAL GPS
  gps.begin(9600);
//  serialgps.begin(9600); 
//    Serial.println("");
//  Serial.println("GPS GY-GPS6MV2 Leantec");
//  Serial.println(" ---Buscando senal--- ");
//  Serial.println("");

  //TEMPERATURA
  dht.begin();
}


void loop() {
  //calcularPeso();
  //consultarAgua();
  //consultarUltrasonico();
  //calcularTemp();
  //calcularGas();
  
  calculaGPS();
}

void calcularGas(){
  int nuevoValor = analogRead(GAS_PIN);
  //Se revisa si el cambio es suficiente para cambiar el valor
  if (abs(nuevoValor-metano) >= (10.23*CAMBIO_SIGNIFICATIVO)) { 
    metano = nuevoValor;
    Serial.println(String("Nuevo valor de gas detectado: ") + metano);
  }
  //delay(100);
}

void calcularTemp(){
  temperatura = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.println(temperatura);  
  //delay(1000);
}

void calculaGPS(){
  delay (2000);
  //if(gps.available())
  //{
    dato=gps.read();
    Serial.println(dato);
    delay (50);
  //}else{
    //Serial.println("GPS NO available");
  //}  
}

void calcularPeso() {
  LoadCell.update();
  float i = LoadCell.getData() * 10;
  Serial.print("Weight[g]:");
  Serial.println(i);
  peso = i;
  delay(100);
}

void consultarUltrasonico() {
  distancia = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distancia);
  if(distancia<dist_max){
    digitalWrite(13,HIGH);
  }else {
    digitalWrite(13,LOW);
  }
  if (lleno) {
    alertaLleno();
  } else {
    consultarContador();
    consultarLlenado();
  }
}

void consultarContador() {
  if (estaEchando) {
    if (distancia < dist_max) {
      tUf = millis();
      if ((tUf - tU0) > 3500) {
        estaEchando = false;
        digitalWrite(9, LOW);
        tU0 = 0;
        tUf = 0;
      }
    } else {
      estaEchando = false;
      digitalWrite(9, LOW);
      tU0 = 0;
      tUf = 0;
    }
  } else {
    if (distancia < dist_max) {
      tU0 = millis();
      estaEchando = true;
      digitalWrite(9, HIGH);
      contador_de_uso++;
    }
  }
}

void consultarLlenado() {
  if (seVaALlenar) {
    if (distancia < dist_max) {
      tLf = millis();
      if ((tLf - tL0) > 5000) {
        Serial.println("Entra aqui**********************************");
        lleno = true;
        digitalWrite(10, HIGH);
        tone(7, 1000);
        alertaLleno();
      }
    } else {
      digitalWrite(10, LOW);
      seVaALlenar = false;
      tL0 = 0;
      tLf = 0;
    }
  } else {
    if (distancia < dist_max) {
      seVaALlenar = true;
      tL0 = millis();
    }
  }
}

void alertaLleno() {
  if (distancia > dist_max) {
    lleno = false;
    digitalWrite(10, LOW);
    seVaALlenar = false;
    tL0 = 0;
    tLf = 0;
    noTone(7);
  }
}

void consultarAgua() {
  if(hayLiquido){
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
  int sensorValue = analogRead(analogInPin);
  Serial.print("Sensor de agua = " );
  Serial.print(sensorValue * 100 / 1024);
  int valorSensor = sensorValue * 100 / 1024;
  Serial.println("%");
  if (valorSensor > 3) {
    hayLiquido = true;
  } else {
    hayLiquido = false;
  }
}
