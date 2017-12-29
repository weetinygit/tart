#define MOTOR_1_PWM 3
#define MOTOR_1_DIR 4
#define MOTOR_2_PWM 5
#define MOTOR_2_DIR 6
#define MOTOR_3_PWM 7
#define MOTOR_3_DIR 8
#define TOGGLE_BUTTON 22
#define MOTOR_2_LIMIT 24
#define MOTOR_3_LIMIT 26
#define CMD_RECEIVE_ACK 13
#define BAUD 57600

#define MOTOR_1_RADPERSTEP 1.8*0.01745
#define MOTOR_2_RADPERSTEP 1.8*0.01745
#define MOTOR_3_RADPERSTEP 1.8*0.01745/(26+103/121)

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <AccelStepper.h>

// Define two steppers and the pins they will use
AccelStepper stepper1(AccelStepper::DRIVER, MOTOR_1_PWM, MOTOR_1_DIR);
AccelStepper stepper2(AccelStepper::DRIVER, MOTOR_2_PWM, MOTOR_2_DIR);
AccelStepper stepper3(AccelStepper::DRIVER, MOTOR_3_PWM, MOTOR_3_DIR);

int pos1 = 3600;
int pos2 = 5678;
int pos3 = 5678;
double motor[3] = {0,0,0};

double radToSteps(double rad, double radPerStep){
  //return rad/radPerStep;
  return rad*1000;
}

//Ros communication functions
void motor1_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[0] = cmd_msg.data;
  pos1 = (int)radToSteps(motor[0], MOTOR_1_RADPERSTEP);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void motor2_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[1] = cmd_msg.data;
   pos2 = (int)radToSteps(motor[1], MOTOR_2_RADPERSTEP);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void motor3_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[2] = cmd_msg.data;
  pos3 = (int)radToSteps(motor[2], MOTOR_2_RADPERSTEP);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}


//Global variables
ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher action_node("/action_node", &str_msg);
ros::Subscriber<std_msgs::Float32> sub("/arduino/motor_1", &motor1_cmd);
ros::Subscriber<std_msgs::Float32> sub2("/arduino/motor_2", &motor2_cmd);
ros::Subscriber<std_msgs::Float32> sub3("/arduino/motor_3", &motor3_cmd);
/*ros::Subscriber<std_msgs::Float32> sub2("/arduino/motor_5", &motor4_cmd);
ros::Subscriber<std_msgs::Float32> sub2("/arduino/motor_6", &motor5_cmd);
*/
int status = -1; //starting
char msg[2] = "1";

void setup()
{
  
  stepper1.setMaxSpeed(3000);
  stepper1.setAcceleration(1000);
  stepper2.setMaxSpeed(2000);
  stepper2.setAcceleration(800);
  stepper3.setMaxSpeed(2000);
  stepper3.setAcceleration(800);
  pinMode(TOGGLE_BUTTON, INPUT);
  pinMode(CMD_RECEIVE_ACK, OUTPUT);
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  stepper2.moveTo(pos2);
  stepper3.moveTo(pos3);
  
  
  //Moves to reference position for motors 2 and 3
  while(digitalRead(MOTOR_2_LIMIT)&&digitalRead(MOTOR_3_LIMIT)){
    stepper2.run();
    stepper3.run();
  }
  
  digitalWrite(CMD_RECEIVE_ACK, LOW);
  
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
  
  //Initialize ros commands
  nh.initNode();
  nh.advertise(action_node);
  nh.subscribe(sub);
  nh.subscribe(sub2);
  pinMode(TOGGLE_BUTTON, INPUT);
  pinMode(CMD_RECEIVE_ACK, OUTPUT);
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
   
}
