#include <Enes100.h>
#include <Servo.h>

Servo myServo1;
Servo myServo2;

// Motor pins
int m1p1 = 31, m1p2 = 33;
int m2p1 = 35, m2p2 = 37;
int m3p1 = 32, m3p2 = 30;
int m4p1 = 34, m4p2 = 36;

// Motor enable (PWM) pins
int ENA1 = 6;  int ENB1 = 7;
int ENA2 = 8; int ENB2 = 9;

// Ultrasonic pins
int trig1 = 50, echo1 = 52;
int trig2 = 40, echo2 = 38;

int servoPin1 = 3;
int servoPin2 = 2;
int pos = 0; 

void setup() {
  
  pinMode(m1p1, OUTPUT); pinMode(m1p2, OUTPUT);
  pinMode(m2p1, OUTPUT); pinMode(m2p2, OUTPUT);
  pinMode(m3p1, OUTPUT); pinMode(m3p2, OUTPUT);
  pinMode(m4p1, OUTPUT); pinMode(m4p2, OUTPUT);

  pinMode(ENA1, OUTPUT); pinMode(ENB1, OUTPUT);
  pinMode(ENA2, OUTPUT); pinMode(ENB2, OUTPUT);

  pinMode(trig1, OUTPUT); pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT); pinMode(echo2, INPUT);

  myServo1.attach(servoPin1);
  myServo2.attach(servoPin2);

  Serial.begin(9600);
  delay(1000);
  Enes100.begin("Dirt", SEED, 676, 1120, 10, 11);
  delay(1000);
  Enes100.println("Connected...");
  //navigateMission();
}

void loop() {
  if (Enes100.isVisible()) {
    if(Enes100.getX() < 3.5) {
      straighten(0);
      delay(1000);
      float distance1 = measureDistance(trig1, echo1);
      float distance2 = measureDistance(trig2, echo2);
      while(((distance1 > 25 || distance1 == 0) && (distance2 > 25 || distance2 == 0)) || Enes100.getX() < 0.55) {
        forward(100);
        distance1 = measureDistance(trig1, echo1);
        distance2 = measureDistance(trig2, echo2);
      }
      stopOTV();
      straightenBetter(0);
      if (distance1 < 10 || distance2 < 10){
        backward(100);
        delay(1000);
        straightenBetter(0);
      }
      stopOTV();
      if (Enes100.getY() < 1.6) {
        left(150);
        delay(1900);
      }
      else{
        straightenBetter(0);
        right(100);
        delay(500);
        while (Enes100.getY() > 0.3 && Enes100.getY() != -1){
          right(200);
          delay(500);
          straighten(0);
        }
        straighten(0);
        stopOTV();
      }
    }
    else {
      stopOTV();
      delay(1000000);
    }
    delay(100);
  }
}

void setSpeed(int s) {
  analogWrite(ENA1, s+3);
  analogWrite(ENB1, s+3);
  analogWrite(ENA2, s);
  analogWrite(ENB2, s);
}

void forward(int speedVal) {
  setSpeed(speedVal);
  digitalWrite(m1p1, HIGH); digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH); digitalWrite(m3p2, LOW);
  digitalWrite(m4p1, LOW);  digitalWrite(m4p2, HIGH);
}

void backward(int speedVal) {
  setSpeed(speedVal);
  digitalWrite(m1p1, LOW);  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH); digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);  digitalWrite(m3p2, HIGH);
  digitalWrite(m4p1, HIGH); digitalWrite(m4p2, LOW);
}

void stopOTV() {
  setSpeed(0);
  digitalWrite(m1p1, LOW); digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW); digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW); digitalWrite(m3p2, LOW);
  digitalWrite(m4p1, LOW); digitalWrite(m4p2, LOW);
}

void spinright(int speedVal) {
  setSpeed(speedVal);
  digitalWrite(m1p1, HIGH); digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, LOW);  digitalWrite(m3p2, HIGH);
  digitalWrite(m4p1, HIGH); digitalWrite(m4p2, LOW);
}
   
void spinleft(int speedVal) {
  setSpeed(speedVal);
  digitalWrite(m1p1, LOW);  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH); digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, HIGH); digitalWrite(m3p2, LOW);
  digitalWrite(m4p1, LOW);  digitalWrite(m4p2, HIGH);
}

void right(int speedVal) {
  setSpeed(speedVal);
  digitalWrite(m1p1, LOW); digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, LOW); digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH); digitalWrite(m3p2, LOW);
  digitalWrite(m4p1, HIGH); digitalWrite(m4p2, LOW);
}
   
void left(int speedVal) {
  setSpeed(speedVal);
  digitalWrite(m1p1, HIGH); digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, HIGH); digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW); digitalWrite(m3p2, HIGH);
  digitalWrite(m4p1, LOW); digitalWrite(m4p2, HIGH);
}

float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);
  float distance = (duration * 0.0343) / 2;

  delay(40);
  return distance;
}

void straightenBetter(float value) {
  if (Enes100.getTheta() < value){
    while (Enes100.getTheta() < value - 0.1){
      if(Enes100.isVisible()){
        spinleft(52);
      }
    }
    stopOTV();
  }
  else if (Enes100.getTheta() > value){
    while (Enes100.getTheta() > value + 0.1){
      if(Enes100.isVisible()){
        spinright(52);
      }
    }
    stopOTV();
  }
  
}
void straighten(float value) {
  if (Enes100.getTheta() < value){
    while (Enes100.getTheta() < value - 0.18){
      if(Enes100.isVisible()){
        spinleft(60);
      }
    }
    stopOTV();
  }
  else if (Enes100.getTheta() > value){
    while (Enes100.getTheta() > value + 0.18){
      if(Enes100.isVisible()){
        spinright(60);
      }
    }
    stopOTV();
  }
}

void navigateMission() {
  float distance1 = measureDistance(trig1, echo1);
  float distance2 = measureDistance(trig2, echo2);
  
  if (Enes100.getY() > 1){
    straightenBetter(-3.14/2);
  }
  else{
    straightenBetter(3.14/2);
  }
  
  while((distance1 > 9 || distance1 == 0) && (distance2 > 9 || distance2 == 0)){
    forward(90);
    distance1 = measureDistance(trig1, echo1);
    distance2 = measureDistance(trig2, echo2);
    float x_pos = Enes100.getX();
    if (x_pos < 0.29 || x_pos > 0.31){
      if (Enes100.getTheta() < 0){
        straighten(-3.14/2);
        while (x_pos < 0.29){
          left(60);
          x_pos = Enes100.getX();
        }
        while (x_pos > 0.31) {
          right(60);
          x_pos = Enes100.getX();
        }
      }
      else{
       straighten(3.14/2);
        while (x_pos < 0.29){
          right(60);
          x_pos = Enes100.getX();
        }
        while (x_pos > 0.31) {
          left(60);
          x_pos = Enes100.getX();
        }
      }
    }
  }
  float x_pos = Enes100.getX();
  if (Enes100.getTheta() < 0){
      straightenBetter(-3.14/2);
      forward(60);
      delay(500);
        while (x_pos < 0.29){
          left(60);
          x_pos = Enes100.getX();
        }
        while (x_pos > 0.31) {
          right(60);
          x_pos = Enes100.getX();
        }
      }
      else{
       straightenBetter(3.14/2);
       forward(60);
        delay(500);
        while (x_pos < 0.29){
          right(60);
          x_pos = Enes100.getX();
        }
        while (x_pos > 0.31) {
          left(60);
          x_pos = Enes100.getX();
        }
      }
  stopOTV();
  delay(50);
  forward(60);
  delay(2000);
  while((distance1 > distance2 + 5)){
    right(60);
    distance1 = measureDistance(trig1, echo1);
    distance2 = measureDistance(trig2, echo2);
  }
  stopOTV();
  while((distance2 > distance1 + 5)){
    left(60);
    distance1 = measureDistance(trig1, echo1);
    distance2 = measureDistance(trig2, echo2);
  }
  stopOTV();

  int plot = predictPlot();
  delay(500);
  forward(60);
  delay(1500);
  stopOTV();
  delay(500);
  if (plot == 0){
    centerLeft(7);
  }
  else if (plot == 1) {
    centerLeft(0);
  }
  else if (plot == 3) {
    centerRight(0);
  }
  else{
    centerRight(7);
  }
  plant();
  forward(60);
  delay(1000);
  if (plot != 0) {
    centerRight(0);
  }
  else { 
    centerLeft(0);
  }
  collect();
  backward(60);
  myServo2.write(150);
}

void centerLeft(float dist) {
  float distance1 = measureDistance(trig1, echo1);
  float distance2 = measureDistance(trig2, echo2);
  while (!(distance1 > distance2 + 20)){
    left(80);
    distance1 = measureDistance(trig1, echo1);
    distance2 = measureDistance(trig2, echo2);
  }
  delay(300);
  stopOTV();
  distance2 = measureDistance(trig2, echo2);
  while (distance2 < dist || distance2 > dist + 15){
    backward(80);
    distance2 = measureDistance(trig2, echo2);
  }
  if(dist == 0){
    forward(60);
    delay(500);
  }
  stopOTV();
}

void centerRight(float dist) {
  float distance1 = measureDistance(trig1, echo1);
  float distance2 = measureDistance(trig2, echo2);
  while (!(distance2 > distance1 + 20)){
    right(80);
    distance1 = measureDistance(trig1, echo1);
    distance2 = measureDistance(trig2, echo2);
  }
  delay(300);
  stopOTV();
  distance1 = measureDistance(trig1, echo1);
  while (distance1 < dist || distance1 > dist + 15){
    backward(80);
    distance1 = measureDistance(trig1, echo1);
  }
  if(dist == 0){
    forward(60);
    delay(500);
  }
  stopOTV();
}

//0 - bottomleft, 1 - topleft, 2 bottomright, 3-topright
int predictPlot(){
  delay(100);
  centerRight(6);
  delay(50);
  Enes100.println("Requesting prediction...");
  unsigned long t0 = millis();
  int result = Enes100.MLGetPrediction(3);
  unsigned long delta_t = millis() - t0;
  Enes100.println("Results are in! ML predicts: " + String(result));
  Enes100.println("The prediction took: " + String(delta_t) + " ms");
  delay(5000);
  return result;
}

void collect(){
  for (pos = 0; pos <= 180; pos += 1) {
    myServo1.write(pos); 
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myServo1.write(pos); 
    delay(15); 
  }
}

void plant(){
  for(int i = 0; i < 3; i++){
    for (pos = 0; pos <= 180; pos += 1) {
      myServo2.write(pos); 
      delay(15);
    }
    for (pos = 180; pos >= 0; pos -= 1) { 
      myServo2.write(pos); 
      delay(15); 
    }
  }
  
}


