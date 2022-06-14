//#include <ros.h>
//#include <std_msgs/String.h>
//#include <geometry_msgs/Twist.h>
#include <HCSR04.h>
UltraSonicDistanceSensor R3(13, 10);
UltraSonicDistanceSensor R2(12, 9);
UltraSonicDistanceSensor R1(11, 8);
#define dir1 2
#define pwm1 3
#define dir2 4
#define pwm2 5
int theta = 60; //angle between range of 2 side sensors
int del=100;
float accel = 15;
float ang_k = 30*PI/180;
int k = 10;
unsigned int r1;
unsigned int r2;
unsigned int r3;

int spwm1 = 60 ;
int spwm2 = 60;
int sdir1 = 0;
int sdir2 = 0;

//ros::NodeHandle  nh;
//geometry_msgs::Twist msg;
//
//void message(const geometry_msgs::Twist& vel)
//{ 
//  obj_avd(vel.linear.x,vel.linear.y,vel.linear.z,vel.angular.x);  
//}

//ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel",message);


//void obj_avd(int spwm1,int spwm2,int sdir1,int sdir2){
//  
//  //initialization of the initial value
//  digitalWrite(2, sdir1);
//  analogWrite(3, spwm1);
//  digitalWrite(4, sdir2);
//  analogWrite(5, spwm2);
//
//  if(r1>10) r1=10;
//  if(r2>10) r2=10;
//  if(r3>10) r3=10;
//  
//  long absolute = sq(r3 - r1) + sq(r2) + 2*r2*(r3 - r1)*cos(theta) + r1*r3*sq(2*cos(theta));
//  int r = sqrt(absolute); 
//  
//  float ang1=acos(r1/r);
//  float ang2=acos(r2/r);
//  float ang3=acos(r3/r);
//
//  if(r2<k){
//    if(r-r2<k){
//    if(ang1<ang3){
//      if(ang2>ang_k){
//      sleft();
//      Serial.println("sharp left");}
//      else{
//      left();
//      Serial.println("left");}
//    }
//    else{
//      if(ang2 > ang_k){
//      sright();
//      Serial.println("sharp right");}
//      else{
//      right();
//      Serial.println("right");} 
//    }
//    }
//    else{
//      if(ang1<ang3){
//        revleft();
//        Serial.println("reverse left");}
//      else{
//        revright();
//        Serial.println("reverse right");
//      }  
//    }
//  }    
//  else{
//     if(r-r2<k){
//        reverse();
//        Serial.println("reverse");}
//     else{
//        forward();
//        Serial.println("forward");}
//  }
//  }

void left() {
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  analogWrite(3, spwm1);
  analogWrite(5, spwm2);
}

void right() {
  digitalWrite(4, LOW);
  digitalWrite(2, HIGH);
  analogWrite(3, spwm1);
  analogWrite(5, spwm2);
}

void revleft() {
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  analogWrite(3, spwm1);
  analogWrite(5, 0);
}

void revright() {
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  analogWrite(3, 0);
  analogWrite(5, spwm2);
}

void sright() {
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  analogWrite(3, spwm1);
  analogWrite(5, 0);
}

void sleft() {
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  analogWrite(3, 0);
  analogWrite(5, spwm2);
}

void forward() {
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  analogWrite(3, spwm1);
  analogWrite(5, spwm2);
}

void reverse() {
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  analogWrite(3, spwm1);
  analogWrite(5, spwm2);
  delay(2*del);
  forward();
}

void setup(){
  Serial.begin(57600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

//  nh.initNode();
//  nh.subscribe(sub);
}

void loop()
{
  r1 = R1.measureDistanceCm();
  r2 = R2.measureDistanceCm();
  r3 = R3.measureDistanceCm();

  if(r1>20) r1=20;
  if(r2>20) r2=20;
  if(r3>20) r3=20;
  
  Serial.println(r1);
  Serial.println(" r1");
  Serial.println(r2);
  Serial.println(" r2");
  Serial.println(r3);
  Serial.println(" r3");

  
  
  digitalWrite(2, sdir1);
  analogWrite(3, spwm1);
  digitalWrite(4, sdir2);
  analogWrite(5, spwm2);
  
  long absolute = sq(r3 - r1) + sq(r2) + r2*(r3 - r1) + r1*r3;
  int r = sqrt(absolute); 
  
  float ang1=abs(acos(r1/r));
  float ang2=abs(acos(r2/r));
  float ang3=abs(acos(r3/r));

  if(r2<k){
    if(r-2*r2<k){
    if(ang1<ang3){
      if(ang2>ang_k){
      sleft();
      Serial.println("sharp left");}
      else{
      left();
      Serial.println("left");}
    }
    else{
      if(ang2>ang_k){
      sright();
      Serial.println("sharp right");}
      else{
      right();
      Serial.println("right");} 
    }
    }
    else{
      reverse();
      Serial.println("reverse");  
    }
  }    
  else{
     if(r-2*r2<k){
        if(ang1<ang3){
        revleft();
        Serial.println("reverse left");}
      else{
        revright();
        Serial.println("reverse right");
      }}
     else{
        forward();
        Serial.println("forward");}
  }
  delay(del);
}
