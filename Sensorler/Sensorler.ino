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

int maxMesafe = 30;
int minMesafe = 0;
bool aracAktifHalde = true;

int mesafeOlc(int enAz, int enFazla);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  pinMode(echoOrta, INPUT);
  pinMode(trigOrta, OUTPUT);
  pinMode(echoSag, INPUT);
  pinMode(trigSag, OUTPUT);
  pinMode(echoSol, INPUT);
  pinMode(trigSol, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
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
  
}

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
