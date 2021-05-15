#include<AFMotor.h>
AF_DCMotor motor_right(3);
AF_DCMotor motor_left(4);
int forward=0;
int backward=0;
int right=0;
int left=0;
void setup() 
{
 pinMode(A2,INPUT);
 pinMode(A3,INPUT);
 pinMode(A4,INPUT);
 pinMode(A5,INPUT);
 Serial.begin(9600);
 motor_right.setSpeed(255);
 motor_left.setSpeed(255);
 motor_right.run(RELEASE);
 motor_left.run(RELEASE);
}
void loop() 
{
  forward=digitalRead(A0);
  backward=digitalRead(A1);
  right=digitalRead(A2);
  left=digitalRead(A3);
   if(forward==HIGH)
    {
     motor_right.run(FORWARD);
     motor_left.run(FORWARD);
     Serial.println("Forward");
    }
   if(backward==HIGH)
    {       
     motor_right.run(BACKWARD);
     motor_left.run(BACKWARD);
     Serial.println("Reverse");
    }
    if(right==HIGH)
     {
      motor_right.run(FORWARD);
      motor_left.run(RELEASE);
      Serial.println("RIGHT");
     }
     if(left==HIGH)
      {
       motor_right.run(RELEASE);
       motor_left.run(FORWARD);
       Serial.println("LEFT");
      }
   if(left==LOW&&right==LOW&&forward==LOW&&backward==LOW)
   {
       motor_right.run(RELEASE);
       motor_left.run(RELEASE);
   }
   delay(100);
}