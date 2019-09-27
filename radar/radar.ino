/*

   ---------------------    --------------------
   | HC-SC04 | Arduino |    | 3 pins | Arduino |
   ---------------------    --------------------
   |   Vcc   |   5V    |    |   Vcc  |   5V    |
   |   Trig  |   1o    | OR |   SIG  |   13    |
   |   Echo  |   2p    |    |   Gnd  |   GND   |
   |   Gnd   |   GND   |    --------------------
   ---------------------
*/

#include <Ultrasonic.h>
#include "LedControl.h"

LedControl lc = LedControl(26, 22, 24, 1); //se cambian los pines despues :D

boolean lasts = false;

Ultrasonic ultrasonic1(2, 3);
Ultrasonic ultrasonic2(4, 5);
Ultrasonic ultrasonic3(6, 7);
#include <Servo.h>;
Servo motorBase;
Servo motorCanon;

volatile unsigned char modo = 1;


unsigned char matrix[8][8];
const char mensaje[13] = "holagrupo15";
int posMat = 0;
int movLetrero = 20;
int auxmovLetrero = 100;



const unsigned char
la[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lb[6][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 1, 1, 0, 1, 1, 0}}
, lesp[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lcc [6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}
, ld[6][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 0, 0, 0, 0, 1, 1}, {0, 1, 1, 1, 1, 1, 1, 0}}
, le[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lf[6][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}}
, lg[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lh[6][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}}
, li[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lj[6][8] = {{1, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}}
, lk[6][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 1, 0, 0}, {0, 1, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 1}}
, ll[6][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1}}
, lm[6][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}}
, ln[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lp[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lq[6][8] = {{0, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 1, 1, 0, 1}}
, lr[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 1, 0, 0}, {1, 1, 1, 1, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}
, ls[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lt[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lu[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, lv[6][8] = {{1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 1, 1, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}}
, lw[6][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1}}
, lx[6][8] = {{1, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 1}}
, ly[6][8] = {{1, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 1, 1, 1, 1}, {0, 1, 1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}}
, lz[6][8] = {{1, 0, 0, 0, 0, 1, 1, 1}, {1, 0, 0, 0, 1, 1, 1, 1}, {1, 0, 0, 1, 1, 0, 0, 1}, {1, 0, 1, 1, 0, 0, 0, 1}, {1, 1, 1, 0, 0, 0, 0, 1}, {1, 1, 0, 0, 0, 0, 0, 1}}

, n0[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}
, n1[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}
, n2[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 1, 1, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}
, n3[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, n4[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, n5[6][8] = {{1, 1, 1, 1, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 1, 0}}
, n6[6][8] = {{0, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 0, 1, 1, 0}}
, n7[6][8] = {{1, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 1, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0}}
, n8[6][8] = {{0, 1, 1, 0, 1, 1, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 1, 0, 1, 1, 1, 0}}
, n9[6][8] = {{0, 1, 1, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 1, 1, 0}}

, dot[6][8] =  {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}
, dash[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, { 0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};



void setArr(int x , char c) {
  if (x < -6 || 17 < x) {
    return;
  }
  switch (c) {
    case  ' ': prueba(x , lesp); break;
    case  'a': prueba(x , la); break;
    case  'b': prueba(x , lb); break;
    case  'c': prueba(x , lcc); break;
    case  'd': prueba(x , ld); break;
    case  'e': prueba(x , le); break;
    case  'f': prueba(x , lf); break;
    case  'g': prueba(x , lg); break;
    case  'h': prueba(x , lh); break;
    case  'i': prueba(x , li); break;
    case  'j': prueba(x , lj); break;
    case  'k': prueba(x , lk); break;
    case  'l': prueba(x , ll); break;
    case  'm': prueba(x , lm); break;
    case  'n': prueba(x , ln); break;
    case  'o': prueba(x , n0); break;
    case  'p': prueba(x , lp); break;
    case  'q': prueba(x , lq); break;
    case  'r': prueba(x , lr); break;
    case  's': prueba(x , ls); break;
    case  't': prueba(x , lt); break;
    case  'u': prueba(x , lu); break;
    case  'v': prueba(x , lv); break;
    case  'w': prueba(x , lw); break;
    case  'x': prueba(x , lx); break;
    case  'y': prueba(x , ly); break;
    case  'z': prueba(x , lz); break;

    case  '0': prueba(x , n0); break;
    case  '1': prueba(x , n1); break;
    case  '2': prueba(x , n2); break;
    case  '3': prueba(x , n3); break;
    case  '4': prueba(x , n4); break;
    case  '5': prueba(x , n5); break;
    case  '6': prueba(x , n6); break;
    case  '7': prueba(x , n7); break;
    case  '8': prueba(x , n8); break;
    case  '9': prueba(x , n9); break;
  }
}

//setea cada letra en su lugar
void setMat(int x) {
  for (int a = 0; a < 8; a++) {
    for (int b = 0; b < 8; b++) {
      matrix[a][b] = 0;
    }
  }
  for (int a = 0; a < 12; a++) {
    char letra = mensaje[a];
    setArr(x, letra);
    x += 6;
  }
}

void setMat2(int x , char arr[3] , int narr ) {
  for (int a = 0; a < 8; a++) {
    for (int b = 0; b < 8; b++) {
      matrix[a][b] = 0;
    }
  }
  for (int a = 0; a < narr; a++) {
    char letra = arr[a];
    setArr(x, letra);
    x += 6;
  }

  for (int b = 0; b < 8; b++) {
    for (int a = 0; a < 8; a++) {
      lc.setLed(0 , b, cambiar(a) , matrix[b][a]); // se colocan los pines de la matriz con driver
    }
  }
}

int solenoide = 11;
int distancia1;
int distancia2;
int distancia3;
int t0_1, tf_1;
int t0_2, tf_2;
int t0_3, tf_3;
boolean s1, s2, s3;
int iBase;
int iCanon;
boolean mBase;
boolean mCanon;
int BTN1 = 2;
int nmuertos = 0;

int cambiar(int x) {
  return (x - 7) * -1;    //para probar en la vida real
  //return x;             //para probar en proteus
}




void prueba(int x , const unsigned char arr[6][8]) {
  for (int a = 0; a < 6; a++) {
    if (a + x < 0) {
      continue;
    }
    if (a + x > 7) {
      return;
    }
    for (int b = 0; b < 8; b++) {
      matrix[x + a][b] = arr[a][b];
    }
  }
}

void setup() {
  Serial.begin(9600);
  distancia1 = 0;
  distancia2 = 0;
  distancia3 = 0;
  t0_1 = 0;
  t0_2 = 0;
  t0_3 = 0;
  tf_1 = 0;
  tf_2 = 0;
  tf_3 = 0;
  s1 = false;
  s2 = false;
  s3 = false;
  motorBase.attach(8);
  motorCanon.attach(9);
  iBase = 0;
  iCanon = 70;
  mBase = false;
  mCanon = false;
  motorBase.write(iBase);
  motorCanon.write(iCanon);
  pinMode(solenoide , OUTPUT);
  pinMode(13, OUTPUT);


  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);
  //attachInterrupt(digitalPinToInterrupt(BTN1), recarga, HIGH);
}

void loop() {
  if (modo == 1) {
    Saludo();
    delay(100);
  } else {
    if (!s1 && !s2 && !s3) {
      moverBase();
    }
    leerDistancia();
    buscarEnemigo();
    if (!lasts) {
      setLetramat('s');
    }
  }
}

void moverBase() {
  motorBase.write(iBase);
  if (mBase) {
    if (iBase <= 0) {
      mBase = false;
    }
    iBase--;
  } else {
    if (iBase >= 90) {
      mBase = true;
    }
    iBase++;
  }
}

void moverCanon(int n, int distancia) {
  Serial.print("SE DISPARA PORQUE ");
  Serial.println(distancia);
  int mas = 0;
  /*if (mBase) {
    int mover = iBase - 10;
    if (mover > 0) {
      for (iBase; iBase >= mover; iBase--) {
        motorBase.write(iBase);
        delay(8);
      }
    }
    } else {
    int mover = iBase + 2;
    if (mover < 120) {
      for (iBase; iBase <= mover; iBase++) {
        motorBase.write(iBase);
        delay(5);
      }
    }
    }*/
  if (distancia < 20) {
    Serial.println("peque");
    mas = 5;
    if (mBase) {
      Serial.println("+++++++++++++");
      int mover = iBase - 30;
      if (mover > 0) {
        for (iBase; iBase >= mover; iBase--) {
          motorBase.write(iBase);
          delay(8);
        }
      }
    } else {
      Serial.println("--------------");
      int mover = iBase + 10;
      if (mover < 120) {
        for (iBase; iBase <= mover; iBase++) {
          motorBase.write(iBase);
          delay(8);
        }
      }
    }
  } else if ( distancia < 40) {
    Serial.println("medio");
    mas = 10;
    if (mBase) {
      Serial.println("+++++++++++++");
      int mover = iBase - 20;
      if (mover > 0) {
        for (iBase; iBase >= mover; iBase--) {
          motorBase.write(iBase);
          delay(8);
        }
      }
    } else {
      Serial.println("--------------");
      int mover = iBase + 10;
      if (mover < 120) {
        for (iBase; iBase <= mover; iBase++) {
          motorBase.write(iBase);
          delay(8);
        }
      }
    }
  } else  {
    Serial.println("grande");
    mas = 15;
    if (mBase) {
      Serial.println("+++++++++++++");
      int mover = iBase - 20;
      if (mover > 0) {
        for (iBase; iBase >= mover; iBase--) {
          motorBase.write(iBase);
          delay(8);
        }
      }
    } else {
      Serial.println("--------------");
      int mover = iBase + 15;
      if (mover < 120) {
        for (iBase; iBase <= mover; iBase++) {
          motorBase.write(iBase);
          delay(8);
        }
      }
    }
  }
  if (n + mas > 25) {
    for (iCanon = 25; iCanon < n + mas; iCanon++) {
      //Serial.println(iCanon);
      motorCanon.write(iCanon);
      delay(20);
    }
    Serial.println("DISPARA");
    digitalWrite(13, HIGH);
    delay(500);
    Serial.print("Grados: ");
    Serial.println(iCanon);
    digitalWrite(13, LOW);
    Serial.println("DISPARÓ");
    for (iCanon = n + mas; iCanon > 25; iCanon--) {
      Serial.println(iCanon);
      motorCanon.write(iCanon);
      delay(20);
    }
  } else {
    for (iCanon = 25; iCanon > n + mas; iCanon--) {
      //Serial.println(iCanon);
      motorCanon.write(iCanon);
      delay(20);
    }
    Serial.println("DISPARA");
    digitalWrite(13, HIGH);
    delay(500);
    Serial.print("Grados: ");
    Serial.println(iCanon);
    digitalWrite(13, LOW);
    Serial.println("DISPARÓ");
    for (iCanon = n + mas; iCanon < 25; iCanon++) {
      Serial.println(iCanon);
      motorCanon.write(iCanon);
      delay(20);
    }
  }
  recarga();
}

void recarga() {
  lc.clearDisplay(0);
  setLetramat('x');
  lasts = false; 
  int ini = 30;
  int fin = 130;
  for (int i = ini; i < fin; i++) {
    motorCanon.write(i);
    delay(10);
  }
  Serial.print("RECARGUE");

  digitalWrite(solenoide , 1);
  delay(162);
  digitalWrite(solenoide , 0);
  delay(1000);
  digitalWrite(solenoide , 1);
  delay(80);
  digitalWrite(solenoide , 0);
  delay(2000);
  delay(1000);


  Serial.println("FIN DE RECARGA");
  delay(1000);
  for (int i = fin; i > ini; i--) {
    motorCanon.write(i);
    delay(10);
  }
  lc.clearDisplay(0);
}

void leerDistancia() {
  distancia1 = ultrasonic1.read();
  distancia2 = ultrasonic2.read();
  distancia3 = ultrasonic3.read();
  //imprimirDistancias();
}

void imprimirDistancias() {
  Serial.print("Sensor 1 - ");
  Serial.println(distancia1);
  Serial.print("Sensor 2 - ");
  Serial.println(distancia2);
  Serial.print("Sensor 3 - ");
  Serial.println(distancia3);
  Serial.println();
}

void buscarEnemigo() {

  if (analizar3()) {
    disparar(3, distancia3);
  } else if (analizar2()) {
    disparar(2, distancia2);
  } else if (analizar1()) {
    disparar(1, distancia1);
  }

  /*if (analizar(distancia1, t0_1, tf_1, s1)) {

    //disparar(1,distancia1);

    } else if (analizar(distancia2, t0_2, tf_2, s2)) {


    //disparar(2,distancia2);
    } else if (analizar(distancia3, t0_3, tf_3, s3)) {


    //disparar(3,distancia3);
    }*/
}

boolean analizar1() {
  if (distancia1 < 70) {

    if (s1) {
      tf_1 = millis();
      if (tf_1 - t0_1 > 2000) {
        t0_1 = 0;
        tf_1 = 0;
        s1 = false;
        return true;
      }
    } else {
      s1 = true;
      t0_1 = millis();
      tf_1 = 0;
    }
  } else {
    s1 = false;
    t0_1 = 0;
    tf_1 = 0;
  }
  return false;
}

boolean analizar2() {
  if (distancia2 < 70) {

    if (s2) {
      tf_2 = millis();
      if (tf_2 - t0_2 > 2000) {
        t0_2 = 0;
        tf_2 = 0;
        s2 = false;
        return true;
      }
    } else {
      s2 = true;
      t0_2 = millis();
      tf_2 = 0;
    }
  } else {
    s2 = false;
    t0_2 = 0;
    tf_2 = 0;
  }
  return false;
}

boolean analizar3() {
  if (distancia3 < 70) {

    if (s3) {
      tf_3 = millis();
      if (tf_3 - t0_3 > 2000) {
        t0_3 = 0;
        tf_3 = 0;
        s3 = false;
        return true;
      }
    } else {
      s3 = true;
      t0_3 = millis();
      tf_3 = 0;
    }
  } else {
    s3 = false;
    t0_3 = 0;
    tf_3 = 0;
  }
  return false;
}
/*boolean analizar(int &distancia, int &t0, int &tf, boolean &s){
  if(distancia<60 && distancia<110){
    if (s){
      tf = millis();
      if(tf-t0 > 2000){
        return true;
      }
    } else {
      s = true;
      t0 = millis();
      tf = 0;
    }
  } else {
    s = false;
    t0 = 0;
    tf = 0;
  }
  return false;
  }*/

void disparar(int n, int distancia) {
  Serial.print("SE DISPARA A LA POSICIÓN: ");
  Serial.println(n);
  setLetramat('o');
  lasts= false; 
  switch (n) {
    case 1:
      moverCanon(5, distancia);
      break;
    case 2:
      moverCanon(30, distancia);
      break;
    case 3:
      moverCanon(55, distancia);
      break;
  }
  nmuertos++;
  nKills(nmuertos);

}

void limpiarMatriz() {
  for (int b = 0; b < 8; b++) {
    for (int a = 0; a < 8; a++) {
      matrix[b][a] = 0; // se colocan los pines de la matriz con driver
    }
  }
}

void setLetramat(char c) {
  limpiarMatriz();
  setArr(1 , c);
  pintarMatriz();
}


void pintarMatriz() {
  for (int b = 0; b < 8; b++) {
    for (int a = 0; a < 8; a++) {
      lc.setLed(0 , b, cambiar(a) , matrix[b][a]); // se colocan los pines de la matriz con driver
    }
  }
}

void nKills(int n) {
  char m2[3];
  int des = 3;
  if (n < 10) {
    des = 1;
  } else if (n < 100) {
    des = 2;
  }


  sprintf(m2 , "%i" , n);

  for (posMat = 0; posMat != - (6 * des + 8); posMat -= 1) {
    setMat2(posMat + 7 , m2, n);
    pintarMatriz();
    delay(50);
  }
  limpiarMatriz();
}

//setea cada letra y morse en su lugar

void Saludo() {

  setMat(posMat + 7);
  posMat -= 1;
  //n letras de la frase * 6 hola grupo, se cambia si no agarra jaja
  if (posMat == - 78) { //para que sea circular el retrero
    posMat = 0;
    modo = 2;
    lc.clearDisplay(0);
  }
  pintarMatriz();


}
