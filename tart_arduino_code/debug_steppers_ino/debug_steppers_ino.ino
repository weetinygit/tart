#define MOTOR_1_PWM 7
#define MOTOR_1_DIR 8


#include <AccelStepper.h>
AccelStepper stepper1(AccelStepper::DRIVER, MOTOR_1_PWM, MOTOR_1_DIR);
int pos = -1000;

void setup()
{
  

  stepper1.setSpeed(6);
  stepper1.setAcceleration(100);
  stepper1.moveTo(pos);
}

void loop(){
    stepper1.run();
    /*if (stepper1.distanceToGo()==0) {
      pos = -pos;
      stepper1.moveTo(pos);
    }*/
  
}
