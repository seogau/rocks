#include<Servo.h>

//초음파센서 핀넘버 지정
int echoPin1 = 12;
int trigPin1 = 13;
int echoPin2 = 7;
int trigPin2 = 4;
int echoPin3 = 8;
int trigPin3 = 10;

//초음파센서 거리
int dis_point1 = 10000;
int dis_point2 = 4000;

//스피커 상수
int speaker = 2;
unsigned long previousMillis = 0;

//서보모터
Servo myservo0;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

//mov함수 변수값
int value = 0; //mov2에서의 모터 각도
int delval = 50; //mov1 딜레이값
int randnum = 1; //mov1모터 랜덤값 선언
int random_scope;
int random_delay;
int pos = 0; //mov1 모터 랜덤값 선언


void setup() {
  Serial.begin(9600);
  //핀넘버 지정
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(speaker, OUTPUT);
  //////////////////////////////
  myservo0.attach(3);
  myservo1.attach(5);
  myservo2.attach(6);
  myservo3.attach(9);
  myservo4.attach(11);
}

void loop() {


  //초음파1
  digitalWrite(trigPin1, LOW);
  digitalWrite(echoPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  unsigned long duration1 = pulseIn(echoPin1, HIGH);


  //초음파2
  digitalWrite(trigPin2, LOW);
  digitalWrite(echoPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  unsigned long duration2 = pulseIn(echoPin2, HIGH);


  //초음파3
  digitalWrite(trigPin3, LOW);
  digitalWrite(echoPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  unsigned long duration3 = pulseIn(echoPin3, HIGH);

//  Serial.print("초음파센서1 : ");
//  Serial.println(duration1);
//  Serial.print("초음파센서2 : ");
//  Serial.println(duration2);
//  Serial.print("초음파센서3 : ");
//  Serial.println(duration3);
//  Serial.println("--------------------");

  if ((duration1 <= dis_point2) || (duration2 <= dis_point2) || (duration3 <= dis_point2)) {        //거부반응 단계

    mov2();
    noTone(speaker);

    Serial.println("distance level : 3");

  }
  else if ((duration1 <= dis_point1) || (duration2 <= dis_point1) || (duration3 <= dis_point1)) {    //동작정지 단계

    Serial.println("distance level : 2");

    noTone(speaker);

  }
  else {                                                                                             //기본 단계
    Serial.println("distance level : 1");
    randnum = random(1, 6);
    random_scope = 181;
    random_delay = 200;
    mov1();
  }
}

void mov1() {

  if (randnum == 1)
  {
    pos = random(0, random_scope);
    myservo0.write(pos);
    delay(delval);
    randnum = random(1, 6);
  }
  else if (randnum == 2)
  {
    pos = random(0, random_scope);
    myservo1.write(pos);
    delay(delval);
    randnum = random(1, 6);
  }
  else if (randnum == 3)
  {
    pos = random(0, random_scope);
    myservo2.write(pos);
    delay(delval);
    randnum = random(1, 6);
  }
  else if (randnum == 4)
  {
    pos = random(0, random_scope);
    myservo3.write(pos);
    delay(delval);
    randnum = random(1, 6);
  }
  else if (randnum == 5)
  {
    pos = random(0, random_scope);
    myservo4.write(pos);
    delay(delval);
    randnum = random(1, 6);
  }
}

void mov2() {


  for (value = 0; value <= 360; value++) {
    value = value + 4;
    myservo0.write(value);
    myservo1.write(value);
    myservo2.write(value);
    myservo3.write(value);
    myservo4.write(value);
  }
  tone(speaker, 200);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1) {
    previousMillis = currentMillis;

    for (value = 360; value >= 0; value--) {
      value = value - 4;
      myservo0.write(value);
      myservo1.write(value);
      myservo2.write(value);
      myservo3.write(value);
      myservo4.write(value);
    }

    currentMillis = millis();
    if (currentMillis - previousMillis >= 1) {
      previousMillis = currentMillis;
      tone(speaker, 262);
    }

    delay(200);


  }
}
