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

#include "UCNEC.h"
int32_t temp = 0;
UCNEC myIR(A0);
#define F 16718055
#define B 16732845
#define L 16713975
#define R 16734885
#define S 16719075

// Motor control pins: L298N H bridge
const int enAPin = 6; // Left motor PWM speed control
const int in1Pin = 7; // Left motor Direction 1
const int in2Pin = 5; // Left motor Direction 2
const int in3Pin = 4; // Right motor Direction 1
const int in4Pin = 2; // Right motor Direction 2
const int enBPin = 3; // Right motor PWM speed control

int command;               //bien luu trang thai Bluetooth
int speedCar    = 160;     // toc do 50 - 255.
int speed_Coeff = 4;       // he so suy giam <=> giam may lan toc do


void setup() {
  
      pinMode(enAPin, OUTPUT);
      pinMode(in1Pin, OUTPUT);
      pinMode(in2Pin, OUTPUT);
      pinMode(in3Pin, OUTPUT);
      pinMode(in4Pin, OUTPUT);
      pinMode(enBPin, OUTPUT);

      Serial.begin(9600); //Init Serial port rate set to 9600
      
      myIR.begin();
}

void loop() {

  if(myIR.available())
      {
            temp =  myIR.read();
            Serial.println(temp);
      }
             
      if (temp == F){goAhead();} 
      else if (temp == B) {goBack();} 
      else if (temp == L) {goLeft();} 
      else if (temp == R) {goRight();} 
      else if (temp == S) {stopRobot();temp=0;}

              
  if (Serial.available() > 0) {
      command = Serial.read();
      stopRobot();      //Initialize with motors stopped.
      Serial.println(command);
      
      switch (command) {
          case 'F':goAhead();break;
          case 'B':goBack();break;
          case 'L':goLeft();break;
          case 'R':goRight();break;
          case 'I':goAheadRight();break;
          case 'G':goAheadLeft();break;
          case 'J':goBackRight();break;
          case 'H':goBackLeft();break;
          case '0':speedCar = 100;break;
          case '1':speedCar = 115;break;
          case '2':speedCar = 130;break;
          case '3':speedCar = 145;break;
          case '4':speedCar = 160;break;
          case '5':speedCar = 175;break;
          case '6':speedCar = 190;break;
          case '7':speedCar = 205;break;
          case '8':speedCar = 220;break;
          case '9':speedCar = 235;break;
          case 'q':speedCar = 255;break;
          
       }
  }

}

void goAhead(){ 

      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,HIGH);         // LEFT tien
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,HIGH);         // RIGHT tien
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar);

  }

void goBack(){ 
      digitalWrite(in1Pin,HIGH);      
      digitalWrite(in2Pin,LOW);         // LEFT lui
      digitalWrite(in3Pin,HIGH);      
      digitalWrite(in4Pin,LOW);         // RIGHT lui
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar);
  }

void goRight(){ 
      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,HIGH);         // LEFT tien
      digitalWrite(in3Pin,HIGH);      
      digitalWrite(in4Pin,LOW);          // RIGHT lui
      analogWrite(enAPin, speedCar);
      analogWrite(enBPin, speedCar);

  }

void goLeft(){
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
