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
Ultrasonic ultrasonic1(2, 3);
Ultrasonic ultrasonic2(4, 5);
Ultrasonic ultrasonic3(6, 7);
#include <Servo.h>;
Servo motorBase;
Servo motorCanon;

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
  pinMode(13, OUTPUT);
}

void loop() {
  if (!s1 && !s2 && !s3) {
    moverBase();
  }
  leerDistancia();
  buscarEnemigo();
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
      int mover = iBase+15;
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
  for (int i = 25; i < 90; i++) {
    motorCanon.write(i);
    delay(10);
  }
  Serial.print("RECARGUE");
  delay(4000);
  Serial.print("FIN DE RECARGA");
  delay(1000);
  for (int i = 90; i > 25; i--) {
    motorCanon.write(i);
    delay(10);
  }
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
}
