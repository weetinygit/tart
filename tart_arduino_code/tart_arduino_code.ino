#include <AccelStepper.h>
#include <Servo.h>

// Stepper motors pins
#define MOTOR_1_PWM 3
#define MOTOR_1_DIR 4
#define MOTOR_2_PWM 5
#define MOTOR_2_DIR 6
#define MOTOR_3_PWM 7
#define MOTOR_3_DIR 8
#define MOTOR_2_LIMIT 24
#define MOTOR_3_LIMIT 26

#define STEPPER_1_MAX_SPEED 3000
#define STEPPER_1_MAX_ACCEL 1000

#define STEPPER_2_MAX_SPEED 2000
#define STEPPER_2_MAX_ACCEL 3000

#define STEPPER_3_MAX_SPEED 2000
#define STEPPER_3_MAX_ACCEL 800

// Servo motors pins
#define LSERVO_PIN 48// left servo motor
#define RSERVO_PIN 50 // right servo motor
#define TSERVO_PIN 52 // top servo motor

// For rosserial
#define BAUD 57600

// Indicator lights & toggle buttons
#define CMD_RECEIVE_ACK 13
#define TOGGLE_BUTTON 22

// Constants
#define MOTOR_1_RADPERSTEP 1.8*0.01745
#define MOTOR_2_RADPERSTEP 1.8*0.01745
#define MOTOR_3_RADPERSTEP 1.8*0.01745/(26+103/121)
#define RAD_TO_DEG 57.2958

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <AccelStepper.h>

// Define steppers and the pins they will use
AccelStepper stepper1(AccelStepper::DRIVER, MOTOR_1_PWM, MOTOR_1_DIR);
AccelStepper stepper2(AccelStepper::DRIVER, MOTOR_2_PWM, MOTOR_2_DIR);
AccelStepper stepper3(AccelStepper::DRIVER, MOTOR_3_PWM, MOTOR_3_DIR);

//Servo instances
Servo LServo, RServo, TServo;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
double motor[6] = {0,0,0,0,0,0};

double radToSteps(double rad, double radPerStep){
  //return rad/radPerStep;
  return rad*1000;
}

//Ros communication functions
void motor1_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[0] = cmd_msg.data;
  //pos1 = (int)radToSteps(motor[0], MOTOR_1_RADPERSTEP);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void motor2_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[1] = cmd_msg.data;
   //pos2 = (int)radToSteps(motor[1], MOTOR_2_RADPERSTEP);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void motor3_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[2] = cmd_msg.data;
  //pos3 = (int)radToSteps(motor[2], MOTOR_2_RADPERSTEP);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void servo1_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[4] = cmd_msg.data;
  TServo.write(90-(int)(motor[4]*RAD_TO_DEG));
  digitalWrite(CMD_RECEIVE_ACK, LOW);
  
}
void servo2_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[5] = cmd_msg.data;
  LServo.write(90-(int)(motor[5]*RAD_TO_DEG));
  RServo.write(90+(int)(motor[5]*RAD_TO_DEG));
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
  LServo.attach(LSERVO_PIN);
  RServo.attach(RSERVO_PIN);
  TServo.attach(TSERVO_PIN);
  LServo.write(90);
  RServo.write(90);
  TServo.write(90);

  // Setup steppers
  stepper1.setMaxSpeed(STEPPER_1_MAX_SPEED);
  stepper1.setAcceleration(STEPPER_1_MAX_ACCEL);
  stepper2.setMaxSpeed(STEPPER_2_MAX_SPEED);
  stepper2.setAcceleration(STEPPER_2_MAX_ACCEL);
  stepper3.setMaxSpeed(STEPPER_2_MAX_SPEED);
  stepper3.setAcceleration(STEPPER_3_MAX_ACCEL);
  
  pinMode(TOGGLE_BUTTON, INPUT);
  pinMode(CMD_RECEIVE_ACK, OUTPUT);
  pinMode(MOTOR_2_LIMIT, INPUT);
  pinMode(MOTOR_3_LIMIT, INPUT);
  
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  delay(3000);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
  //Moves to reference position for motors 2 and 3
   /*
  stepper2.moveTo(-5000);
  stepper3.moveTo(5000);
  while(digitalRead(MOTOR_2_LIMIT)&&digitalRead(MOTOR_3_LIMIT)){
    stepper2.run();
    stepper3.run();
  }

  if(!digitalRead(MOTOR_2_LIMIT)) {
  
    stepper2.stop();
    stepper2.setCurrentPosition(0);
    while(digitalRead(MOTOR_3_LIMIT)){
      stepper3.run();
    }
    stepper3.stop();
    stepper3.setCurrentPosition(0);
  }
  
  else {
    stepper3.stop();
    stepper3.setCurrentPosition(0);
    while(digitalRead(MOTOR_2_LIMIT)){
      stepper2.run();
    }
    stepper2.stop();
    stepper2.setCurrentPosition(0);
  }
  */
  
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
   stepper1.moveTo(pos1);
   stepper2.moveTo(pos2);
   stepper3.moveTo(pos3);
   stepper1.run();
   stepper2.run();
   stepper3.run();
   delay(2);
   
}
