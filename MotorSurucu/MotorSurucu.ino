#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);

int motorHiz;
char gelenVeri[10];
bool aracCalisti = false;

void motorHizAyarla();
void motorHareket(String yon); // ileri, geri, sag, sol


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  motorHiz = 210;
  Serial2.begin(9600);
  if (Serial1.available() > 0) {
      aracCalisti = true;
  }
  if (Serial2.available() > 0) {
    Serial2.readBytes(gelenVeri, 2);
    Serial.println(gelenVeri);
    motorHareket("dur");
    delay(10);
    Serial2.end();
    if (gelenVeri[0] == 'S' && !aracCalisti) {
      aracCalisti = true;
    }
    if (gelenVeri[0] == 'A' || gelenVeri[0] == 'B' || gelenVeri[0] == 'D' && aracCalisti) {
      sagaGit();
    }
    else if (gelenVeri[0] == 'C' && aracCalisti) {
      solaGit();
    }
    else if (gelenVeri[0] == 'x' && aracCalisti) {
      duzGit();
    }
    else if (aracCalisti) {
      motorHareket("geri");
      delay(200);
      motorHareket("dur");
      delay(1300);
      gelenVeri[0] = 'x';
      sagaGit();
    }
    else {
      motorHareket("dur");
    }
    Serial2.end();
  }
  else if (aracCalisti) {
    duzGit();
  }
  else {
    motorHareket("dur");
  }
}

void sagaGit() {
  motorHiz = 250;
  motorHizAyarla();
  motorHareket("geri");
  delay(200);
  motorHareket("sag");
  delay(400);
}

void solaGit() {
  motorHiz = 250;
  motorHizAyarla();
  motorHareket("geri");
  delay(200);
  motorHareket("sol");
  delay(400);
}

void duzGit() {
  motorHiz = 210;
  motorHizAyarla();
  motorHareket("ileri");
}

void motorHizAyarla() {
  motor1.setSpeed(motorHiz);
  motor2.setSpeed(motorHiz);
  motor3.setSpeed(motorHiz);
  motor4.setSpeed(motorHiz);
}

void motorHareket(String yon) { // Teker dizilimine gore backward deyince ileri forward deyince geri gidiyoruz
  if (yon == "ileri") {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  }
  else if (yon == "geri") {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
  else if (yon == "sag") {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
  }
  else if (yon == "sol") {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
  }
  else if (yon == "dur") { // dur
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
  else { // tanimli olmayan komut
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
}
