#include <Servo.h>

// Stepper motors pins
#define MOTOR_1 9
#define MOTOR_2 10
#define MOTOR_3 11

#define MOTOR_1_LOWER 80
#define MOTOR_1_UPPER 100
#define MOTOR_2_LOWER 50
#define MOTOR_2_UPPER 130
#define MOTOR_3_LOWER 50
#define MOTOR_3_UPPER 130

#define MOTOR_1_POLARITY 1
#define MOTOR_2_POLARITY 1
#define MOTOR_3_POLARITY -1
#define TSERVO_POLARITY 1
#define LSERVO_POLARITY -1
#define RSERVO_POLARITY 1

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
int pos;


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
ros::NodeHandle  nh;

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
  motor1.write(90);
  motor2.write(90);
  motor3.write(90);
  LServo.write(90);
  RServo.write(90);
  TServo.write(90);

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
   pos = 90+(int)motor[0]*MOTOR_1_POLARITY;
   if(pos>=MOTOR_1_LOWER && pos<=MOTOR_1_UPPER) motor1.write(pos);
   pos = 90+(int)motor[1]*MOTOR_2_POLARITY;
   if(pos>=MOTOR_2_LOWER && pos<=MOTOR_2_UPPER) motor2.write(pos);
   pos = 90+((int)motor[2]*MOTOR_3_POLARITY+(int)motor[1]*MOTOR_2_POLARITY);
   if(pos>=MOTOR_3_LOWER && pos<=MOTOR_3_UPPER) motor3.write(pos);
   TServo.write(90+(int)motor[5]*TSERVO_POLARITY);
   LServo.write(90+(int)motor[5]*LSERVO_POLARITY);
   RServo.write(90+(int)motor[5]*RSERVO_POLARITY);
   delay(20);
   
}
