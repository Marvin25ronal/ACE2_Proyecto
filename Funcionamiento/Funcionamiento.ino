/*
 * Ultrasonic Simple
 * Prints the distance read by an ultrasonic sensor in
 * centimeters. They are supported to four pins ultrasound
 * sensors (liek HC-SC04) and three pins (like PING)))
 * and Seeed Studio sensors).
 *
 * The circuit:
 * * Module HR-SC04 (four pins) or PING))) (and other with
 *   three pins), attached to digital pins as follows:
 * ---------------------    --------------------
 * | HC-SC04 | Arduino |    | 3 pins | Arduino |
 * ---------------------    --------------------
 * |   Vcc   |   5V    |    |   Vcc  |   5V    |
 * |   Trig  |   12    | OR |   SIG  |   13    |
 * |   Echo  |   13    |    |   Gnd  |   GND   |
 * |   Gnd   |   GND   |    --------------------
 * ---------------------
 * Note: You do not obligatorily need to use the pins defined above
 * 
 * By default, the distance returned by the read()
 * method is in centimeters. To get the distance in inches,
 * pass INC as a parameter.
 * Example: ultrasonic.read(INC)
 *
 * created 3 Apr 2014
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 23 Jan 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 03 Mar 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 11 Jun 2018
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 *
 * This example code is released into the MIT License.
 */
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <Servo.h>
SoftwareSerial DFPlayerSerial(10, 11); // RX, TX
//
/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
 * Ultrasonic ultrasonic(13);
 */
//Ultrasonic ultrasonic(12, 13);
Ultrasonic ultrasonic(3, 2);
int distancia;
int motorAbierto = 5;
int motorCerrado = 6;
boolean abierto = false;
long t0 = 0;
long tf = 0;
bool pasoprimera=false;
boolean hayObstaculo = false;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  pinMode(motorAbierto, OUTPUT);
  pinMode(motorCerrado, OUTPUT);
  pinMode(13, INPUT);
  digitalWrite(motorAbierto, LOW);
  digitalWrite(motorCerrado, HIGH);
  //
  DFPlayerSerial.begin(9600);
   mp3_set_serial(DFPlayerSerial);
   mp3_set_volume(50);//50
   //
   myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  //Serial.println(millis());
  tf = millis();
  if(digitalRead(13) == HIGH){
    t0 = millis();
    hayObstaculo = true;
  } else {
    hayObstaculo = false;
  }
  if(abierto && !hayObstaculo && (tf-t0) > 5000){
    cerrar();
  }
  // Pass INC as a parameter to get the distance in inches
  distancia = ultrasonic.read();
  
  //Serial.print("Distance in CM: ");
  //Serial.println(distancia);
  if(distancia<15){
    abrir();
  }
}

void abrir(){
  for(int i = 0; i<=50; i++){
    //abrir la tapa
  }
  if(!abierto){
    mp3_next();
  }
  //Serial.println("ABRIENDO");
  //Motor a °
  digitalWrite(motorCerrado, LOW); 
  digitalWrite(motorAbierto, HIGH);
  if(!abierto){
  subir();
  }
  abierto = true;
  t0 = millis();
}

void cerrar(){
  for(int i = 65; i>= 0; i--){
    //cerrar la tapa
  }
  //Serial.println("CERRANDO");
  //Motor a °
  bajar();
  mp3_pause();
  digitalWrite(motorAbierto, LOW);
  digitalWrite(motorCerrado, HIGH);  
  abierto = false;
  t0 = 0;
}

void subirprimera(){
  //15 arriba
  pasoprimera=true;
  myservo.write(150);
  for (pos = 150 ; pos >= 15; pos -= 1) { // goes from 180 degrees to 0 degrees
    Serial.println(pos);
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}
void subirsegunda(){
  //15 arriba
  pasoprimera=true;
  myservo.write(150);
  for (pos = 150 ; pos >= 15; pos -= 1) { // goes from 180 degrees to 0 degrees
    Serial.println(pos);
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}
void subir(){
  if(pasoprimera==true){
    subirprimera();
  }else{
    subirsegunda();
  }
}
void bajar(){
  for (pos = 15; pos <= 130; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.println(pos);
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
}
