#include <IRremote.h>

IRrecv irrecv(11);
decode_results results;

#define startStop 16726215 // 0xE31CFF00
#define forward 16734375 // 0xE51AFF00
#define backward 16716525 // 0xB748FF00
#define right 16769055 // 0xF807FF00
#define left 16769565 // 0xB847FF

char temp;

/*
#define echoOrta 2
#define trigOrta 3
#define echoSag 4
#define trigSag 5
#define echoSol 6
#define trigSol 7
#define hareketSensoruEcho 9
#define hareketSensoruTrig 12
#define ustEcho 11
#define ustTrig 10
#define led 8
#define buzzer 13
*/

/*
int maxMesafe = 30;
int minMesafe = 0;
bool aracAktifHalde = true;

int mesafeOlc(int enAz, int enFazla);
*/

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  
/*
  Serial2.begin(9600);
  
  pinMode(echoOrta, INPUT);
  pinMode(trigOrta, OUTPUT);
  pinMode(echoSag, INPUT);
  pinMode(trigSag, OUTPUT);
  pinMode(echoSol, INPUT);
  pinMode(trigSol, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
*/
}

void loop() {

  if (irrecv.decode(&results)) {
    //Serial.println(results.value);
    if (results.value == startStop) { // basla - dur
      Serial.write(65); // A
      //Serial.println("A gonderildi");
      temp = 'A';
    }
    else if (results.value == forward) { // ileri
      Serial.write(66); // B
      //Serial.println("B gonderildi");
      temp = 'B';
    }
    else if (results.value == backward) { // geri
      Serial.write(67); // C
      //Serial.println("C gonderildi");
      temp = 'C';
    }
    else if (results.value == right) { // sag
      Serial.write(68); // D
      //Serial.println("D gonderildi");
      temp = 'D';
    }
    else if (results.value == left) { // sol
      Serial.write(69); // E
      //Serial.println("E gonderildi");
      temp = 'E';
    }
    else { // tanimsiz
      //Serial.println("Tanimsiz");
      if (temp == 'A') Serial.write(65);
      else if (temp == 'B') Serial.write(66);
      else if (temp == 'C') Serial.write(67);
      else if (temp == 'D') Serial.write(68);
      else Serial.write(69);
    }
    results.value = 55555555;
    irrecv.resume();
  }
  
  /*
  if (aracAktifHalde) {
    digitalWrite(led, HIGH);
    noTone(buzzer);
  }
  else {
    digitalWrite(led, LOW);
    tone(buzzer, 349);
  }
  
  int mesafe1 = mesafeOlc(minMesafe, maxMesafe, echoOrta, trigOrta); // on sensor
  int mesafeUst = mesafeOlc(minMesafe, maxMesafe, ustEcho, ustTrig); // on ust sensor
  int mesafe2 = mesafeOlc(minMesafe, maxMesafe, echoSag, trigSag); // sag sensor
  int mesafe3 = mesafeOlc(minMesafe, maxMesafe, echoSol, trigSol); // sol sensor
  int mesafe4 = mesafeOlc(minMesafe, maxMesafe, hareketSensoruEcho, hareketSensoruTrig); // start

  Serial.println(mesafe4);

  if (mesafe4 != -1) { // start
    //Serial1.write("a", 1);
    Serial.println("BASLADI");
    aracAktifHalde = true;
  }
  
  if (aracAktifHalde) {
    Serial2.write(83);
  }
  if (mesafeUst != -1) { // engel sadece onumuzde
    //Serial1.write("d", 1);
    Serial1.write(68); // D
    Serial.println("D gonderildi");
  }
  if (mesafe1 != -1) { // engel sadece onumuzde
    //Serial1.write("a", 1);
    Serial1.write(65); // A
    Serial.println("A gonderildi");
  }
  if(mesafe2 != -1) { // engel sadece sagda
    //Serial1.write("b", 1);
    Serial1.write(66); // B
    Serial.println("B gonderildi");
  }
  if (mesafe3 != -1) { // engel sadece solda
    //Serial1.write("c", 1);
    Serial1.write(67); // C
    Serial.println("C gonderildi");
  }
  */
}

/*
int mesafeOlc(int enAz, int enFazla, int echoPin, int trigPin) {
  long geriGelmeSuresi, uzaklik;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  geriGelmeSuresi = pulseIn(echoPin, HIGH);
  uzaklik = geriGelmeSuresi / 58.2;
  if (uzaklik > enFazla || uzaklik <= enAz)
    return -1;
  else
    return uzaklik;
}
*/
