#include <Servo.h>

// Stepper motors pins
#define MOTOR_1 9
#define MOTOR_2 10
#define MOTOR_3 11

#define MOTOR_1_LOWER 65
#define MOTOR_1_UPPER 85
#define MOTOR_2_LOWER 80
#define MOTOR_2_UPPER 140
#define MOTOR_3_LOWER 63
#define MOTOR_3_UPPER 108

#define MOTOR_1_ZERO 90
#define MOTOR_2_ZERO 110
#define MOTOR_3_ZERO 88
#define TSERVO_ZERO 90
#define LSERVO_ZERO 90
#define RSERVO_ZERO 90

#define MOTOR_1_POLARITY 1
#define MOTOR_2_POLARITY 1
#define MOTOR_3_POLARITY -1
#define TSERVO_POLARITY -1
#define LSERVO_POLARITY -1
#define RSERVO_POLARITY -1

// Servo motors pins
#define LSERVO 6// left servo motor
#define RSERVO 7 // right servo motor
#define TSERVO 8 // top servo motor

// For rosserial
#define BAUD 57600

// Indicator lights & toggle buttons
#define CMD_RECEIVE_ACK 13
#define TOGGLE_BUTTON 22

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <AccelStepper.h>


//Servo instances
Servo motor1, motor2, motor3, LServo, RServo, TServo;
double motor[6] = {0,0,0,0,0,0};
int targetpos = 0;
int currentpos[6]={MOTOR_1_ZERO,MOTOR_2_ZERO,MOTOR_3_ZERO,0,TSERVO_ZERO,LSERVO_ZERO};


//Ros communication functions
void motor1_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[0] = cmd_msg.data;
  delay(10);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void motor2_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[1] = cmd_msg.data;
  delay(10);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void motor3_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[2] = cmd_msg.data;
  delay(10);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void servo1_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[4] = cmd_msg.data;
  delay(10);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
  
}
void servo2_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[5] = cmd_msg.data;
  delay(10);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}


//Global variables
ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher action_node("/action_node", &str_msg);
ros::Subscriber<std_msgs::Float32> sub("/arduino/motor_1", &motor1_cmd);
ros::Subscriber<std_msgs::Float32> sub2("/arduino/motor_2", &motor2_cmd);
ros::Subscriber<std_msgs::Float32> sub3("/arduino/motor_3", &motor3_cmd);
ros::Subscriber<std_msgs::Float32> sub4("/arduino/motor_5", &servo1_cmd);
ros::Subscriber<std_msgs::Float32> sub5("/arduino/motor_6", &servo2_cmd);

int status = -1; //starting
char msg[2] = "1";

void setup()
{
  // Setup servo motors
  motor1.attach(MOTOR_1);
  motor2.attach(MOTOR_2);
  motor3.attach(MOTOR_3);
  LServo.attach(LSERVO);
  RServo.attach(RSERVO);
  TServo.attach(TSERVO);
  motor1.write(MOTOR_1_ZERO);
  motor2.write(MOTOR_2_ZERO);
  motor3.write(MOTOR_3_ZERO);
  LServo.write(LSERVO_ZERO);
  RServo.write(RSERVO_ZERO);
  TServo.write(TSERVO_ZERO);

  pinMode(TOGGLE_BUTTON, INPUT);
  pinMode(CMD_RECEIVE_ACK, OUTPUT);
  
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  delay(3000);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
  
  //Initialize ros commands
  nh.initNode();
  nh.advertise(action_node);
  nh.subscribe(sub);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.subscribe(sub5);
  nh.getHardware()->setBaud(BAUD);
}

void loop()
{
  //Sending toggle command
  if(digitalRead(TOGGLE_BUTTON) != status){
    if(digitalRead(TOGGLE_BUTTON) == 1) msg[0] = '2';
    else if (digitalRead(TOGGLE_BUTTON) == 0) msg[0] = '1';
    str_msg.data = msg;
    action_node.publish( &str_msg );

    status = digitalRead(TOGGLE_BUTTON);
  }
   nh.spinOnce();
   //Move motors to position
   targetpos = MOTOR_1_ZERO+(int)motor[0]*MOTOR_1_POLARITY;
   if(targetpos>=MOTOR_1_LOWER && targetpos<=MOTOR_1_UPPER) {
     if(targetpos<currentpos[0]) currentpos[0]--;
     else if (targetpos>currentpos[0]) currentpos[0]++;
     motor1.write(currentpos[0]);
   }
   targetpos = MOTOR_2_ZERO+(int)motor[1]*MOTOR_2_POLARITY;
   if(targetpos>=MOTOR_2_LOWER && targetpos<=MOTOR_2_UPPER) {
     if(targetpos<currentpos[1]) currentpos[1]--;
     else if (targetpos>currentpos[1]) currentpos[1]++;
     motor2.write(currentpos[1]);
   }
   targetpos = MOTOR_3_ZERO+((int)motor[2]*MOTOR_3_POLARITY-(int)motor[1]*MOTOR_2_POLARITY);
   if(targetpos>=MOTOR_3_LOWER && targetpos<=MOTOR_3_UPPER) {
     if(targetpos<currentpos[2]) currentpos[2]--;
     else if (targetpos>currentpos[2]) currentpos[2]++;
     motor3.write(currentpos[2]);
   }
   
   targetpos=TSERVO_ZERO+(int)motor[4]*TSERVO_POLARITY;
   if(targetpos<currentpos[4]) currentpos[4]--;
   else if (targetpos>currentpos[4]) currentpos[4]++;
   TServo.write(targetpos);
   
   targetpos=(int)motor[5]*LSERVO_POLARITY;
   if(targetpos<currentpos[5]) currentpos[5]--;
   else if (targetpos>currentpos[5]) currentpos[5]++;
   LServo.write(90+targetpos);
   RServo.write(90-targetpos);
   delay(10);
   
}
