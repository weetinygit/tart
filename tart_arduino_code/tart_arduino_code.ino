

#define POSE_SWITCH 12
#define CMD_RECEIVE_ACK 13
#define BAUD 57600

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>

double motor[5] = {90,90,90,90,90};


void motor1_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[0] = radiansToDegrees(cmd_msg.data);
  delay(10);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
void motor2_cmd(const std_msgs::Float32& cmd_msg)
{
  digitalWrite(CMD_RECEIVE_ACK, HIGH);
  motor[1] = radiansToDegrees(cmd_msg.data);
  delay(10);
  digitalWrite(CMD_RECEIVE_ACK, LOW);
}
double radiansToDegrees(float position_radians)
{

  position_radians = position_radians + 1.6;

  return position_radians * 57.2958;

}

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher action_node("/action_node", &str_msg);
ros::Subscriber<std_msgs::Float32> sub("/arduino/motor_1", &motor1_cmd);
ros::Subscriber<std_msgs::Float32> sub2("/arduino/motor_2", &motor2_cmd);
/*ros::Subscriber<std_msgs::Float32> sub2("/arduino/motor_3", &motor3_cmd);
ros::Subscriber<std_msgs::Float32> sub2("/arduino/motor_5", &motor4_cmd);
ros::Subscriber<std_msgs::Float32> sub2("/arduino/motor_6", &motor5_cmd);
*/
int status = -1; //starting
char msg[2] = "1";


void setup()
{
  nh.initNode();
  nh.advertise(action_node);
  nh.subscribe(sub);
  nh.subscribe(sub2);
  pinMode(POSE_SWITCH, INPUT);
  pinMode(CMD_RECEIVE_ACK, OUTPUT);
  nh.getHardware()->setBaud(BAUD);
}

void loop()
{
  if(digitalRead(POSE_SWITCH) != status){
    if(digitalRead(POSE_SWITCH) == 1) msg[0] = '2';
    else if (digitalRead(POSE_SWITCH) == 0) msg[0] = '1';
    str_msg.data = msg;
    action_node.publish( &str_msg );

    status = digitalRead(POSE_SWITCH);
  }
   nh.spinOnce();
   delay(1);

}

