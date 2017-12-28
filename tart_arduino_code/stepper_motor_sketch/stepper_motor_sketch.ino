
#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 8, 9);

int spd = 1000;    // The current speed in steps/second
int sign = 1;      // Either 1, 0 or -1

void setup()
{ 
  Serial.begin(9600);
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(1000);   
}

void loop()
{ 
  char c;
  if(Serial.available()) {
    c = Serial.read();
    if (c == 'f') {  // forward
      sign = 1;
    }
    if (c == 'r') {  // reverse
      sign = -1;
    }
    if (c == 's') {  // stop
      sign = 0;
    }
    if (c == '1') {  // super slow
      spd = 10;
    }
    if (c == '2') {  // medium
      spd = 100;
    }
    if (c == '3') {  // fast
      spd = 1000;
    }
    stepper.setSpeed(sign * spd);
  }
  stepper.runSpeed();
}
