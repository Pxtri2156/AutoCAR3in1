//www.linhkientot.vn
//code xe robot 3 banh dieu khien qua bluetooth
//Ket noi Bluetooth HC-06,HC-05 (neu HC-05 (có 5 chân) thì chỉ dùng 4 pin: +5V,GND,TX,RX)
// Bluetooth HC-06/HC-05   <----> Arduino SENSor Shield V5.0 (4pin TX,RX,-,+)
//      RX                 -NOI-            TX
//      TX                 -NOI-            RX
//      GND                -NOI-            -
//      +5V                -NOI-            +

//#include <LiquidCrystal_I2C.h> //Includes I2C-LCD1602 lib
#include <Wire.h> //Includes I2C Lib 
#include <NewPing.h>
#include <Servo.h>
#include "UCNEC.h"
Servo myservo;

int32_t IR_signal = 0; 
UCNEC myIR(A0); 
#define F 16718055
#define B 16732845
#define L 16713975
#define R 16734885
#define S 16719075
#define U 16729530 //1
#define T 16729785 //2

#define ECHO_PIN 9
#define TRIG_PIN 10           
#define MAX_DISTANCE 200 
#define MAX_SPEED 235 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

// 3 -> 16730040
// 4 -> 16729275
// 5 -> 16728255
// 6 -> 16729020
// 7 -> 16713720
// 8 -> 16717290
// 9 -> 16714230
// * -> 16717545
// 0 -> 16718310
// # -> 16715250


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
boolean goesForward=false;
int distance = 100;
int speedSet = 0;

//const int onfar = 13;
int       dugme=1;

// Motor control pins: L298N H bridge
const int enAPin = 6; // Left motor PWM speed control
const int in1Pin = 7; // Left motor Direction 1
const int in2Pin = 5; // Left motor Direction 2
const int in3Pin = 4; // Right motor Direction 1
const int in4Pin = 2; // Right motor Direction 2
const int enBPin = 3; // Right motor PWM speed control

int command;               //bien luu trang thai Bluetooth
int speedCar    = 250;     // toc do 50 - 255.
int speed_Coeff = 4;       // he so suy giam <=> giam may lan toc do
void setup() {
      pinMode(enAPin, OUTPUT);
      pinMode(in1Pin, OUTPUT);
      pinMode(in2Pin, OUTPUT);
      pinMode(in3Pin, OUTPUT);
      pinMode(in4Pin, OUTPUT);
      pinMode(enBPin, OUTPUT);
      myIR.begin();
      Serial.begin(9600); 
      myservo.attach(8); 
      pinMode(TRIG_PIN, OUTPUT);
      pinMode(ECHO_PIN, INPUT);
      myservo.write(95); 
      testServo();
      delay(200);
      readPing();
}

void loop() {
  if(myIR.available())
      {
            IR_signal =  myIR.read();
            Serial.println(IR_signal);
      }
//      if (IR_signal == F){goAhead();} 
//      else if (IR_signal == B) {goBack();} 
//      else if (IR_signal == L) {goLeft();} 
//      else if (IR_signal == R) {goRight();} 
//      else if (IR_signal == S) {stopRobot();IR_signal=0;}
//      else if (IR_signal == U) {avoiding();IR_signal=0;} 
//      else if (IR_signal == T) {stopAvoiding();IR_signal=0;} 
  switch (IR_signal) {
          case F:goAhead();break;
          case B:goBack();break;
          case L:goLeft();break;
          case R:goRight();break;
          case U:avoiding();break;
          case T:stopAvoiding();break;
          case S: stopRobot(); break;
  }
}

void goAhead(){ 

      digitalWrite(in1Pin,HIGH);      
      digitalWrite(in2Pin,LOW);         // LEFT tien
      digitalWrite(in3Pin,HIGH);      
      digitalWrite(in4Pin,LOW);         // RIGHT tien
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar);

  }

void goBack(){ 
      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,HIGH);         // LEFT lui
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,HIGH);         // RIGHT lui
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar);
  }

void goLeft(){ 
      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,HIGH);         // LEFT tien
      digitalWrite(in3Pin,HIGH);      
      digitalWrite(in4Pin,LOW);          // RIGHT lui
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar);

  }

void goRight(){
      digitalWrite(in1Pin,HIGH);      
      digitalWrite(in2Pin,LOW);         // LEFT lui
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,HIGH);         // RIGHT tien
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar);
      
  }

void goAheadRight(){      //vua tien - vua quay phai
      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,HIGH);         // LEFT tien
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,HIGH);         // RIGHT tien
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar/speed_Coeff);  //banh phai quay cham hon
            
  }

void goAheadLeft(){
      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,HIGH);         // LEFT tien
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,HIGH);         // RIGHT tien
      analogWrite(enAPin, speedCar/speed_Coeff);   //banh trai quay cham hon
      analogWrite(enBPin, speedCar);
 
  }

void goBackRight(){     //vua lui - vua quay phai
      digitalWrite(in1Pin,HIGH);      
      digitalWrite(in2Pin,LOW);         // LEFT lui
      digitalWrite(in3Pin,HIGH);      
      digitalWrite(in4Pin,LOW);         // RIGHT lui
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar/speed_Coeff);  //banh phai quay cham hon

  }

void goBackLeft(){ 
      digitalWrite(in1Pin,HIGH);      
      digitalWrite(in2Pin,LOW);         // LEFT lui
      digitalWrite(in3Pin,HIGH);      
      digitalWrite(in4Pin,LOW);         // RIGHT lui
      analogWrite(enAPin, speedCar/speed_Coeff);//banh trai quay cham hon
      analogWrite(enBPin, speedCar);  

  }

void stopRobot(){  
      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,LOW);      
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,LOW);         
      analogWrite(enAPin, 0);
      analogWrite(enBPin, 0);  
      
  }

 void stopAvoiding()
{
  dugme=0;
  digitalWrite(in1Pin,LOW);      
  digitalWrite(in2Pin,LOW);      
  digitalWrite(in3Pin,LOW);      
  digitalWrite(in4Pin,LOW);         
  analogWrite(enAPin, 0);
  analogWrite(enBPin, 0); 
}

void avoiding()
{
    long duration, distance;
    int distanceR = 0;
    int distanceL =  0;
     while(dugme==1)
     { 
         distance = readPing();
         delay(40);
         if(distance<=30)
         {
              stopRobot();
              delay(100);
              goBack();
              delay(200);
              stopRobot();
              delay(200);
              distanceR = lookRight();
              delay(200);
              distanceL = lookLeft();
              delay(200);
              if(distanceR>=distanceL)
              {
                goRight();
                delay(300);
                stopRobot();
                delay(100);
              }else
              {
                goLeft();
                delay(300);
                stopRobot();
                delay(100);
              }
         }else
         {
          goAhead();
         }
         
     }
}
int lookRight()
{
    Serial.println("look Right");
    myservo.write(40); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(95); 
    return distance;
}

int lookLeft()
{
    Serial.println("look Left");
    myservo.write(150); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(95); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void testServo(){
  myservo.write(150); 
  myservo.write(40); 
  myservo.write(90);
}
