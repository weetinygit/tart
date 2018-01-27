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
#define STEPPER_1_MAX_ACCEL 10000

#define STEPPER_2_MAX_SPEED 2000
#define STEPPER_2_MAX_ACCEL 30000

#define STEPPER_3_MAX_SPEED 2000
#define STEPPER_3_MAX_ACCEL 30000

// Servo motors pins
#define LSERVO_PIN 9 // left servo motor
#define RSERVO_PIN 10 // right servo motor
#define TSERVO_PIN 11 // top servo motor

// Define steppers and the pins they will use
AccelStepper stepper1(AccelStepper::DRIVER, MOTOR_1_PWM, MOTOR_1_DIR);
AccelStepper stepper2(AccelStepper::DRIVER, MOTOR_2_PWM, MOTOR_2_DIR);
AccelStepper stepper3(AccelStepper::DRIVER, MOTOR_3_PWM, MOTOR_3_DIR);

Servo LServo, RServo, TServo;

long pos1 = 3600.0;
long pos2 = 5678.0;
long pos3 = 5678.0;
int pos4, pos5;

long currentPos1, currentPos2, currentPos3;

long maxpos3 = 3500000; //degrees
long maxpos2 = 4500000; //degrees

int angle, choice;
char dump;

const long DEG_TO_STEP=15;

long degtostep(long deg){
  return deg*DEG_TO_STEP;
}

void dumpSerial(){
  while(Serial.available()>0){
    dump = Serial.read();
  }
}


int readAngle(){
  while(Serial.available()==0){}
  int angle = Serial.parseInt();
  dumpSerial();
  Serial.println(angle);
  return angle;
}

void printChoices(){
  Serial.println("Please choose:");
  Serial.println("1 to move bottom stepper motor");
  Serial.println("2 to move RIGHT stepper motor");
  Serial.println("3 to move left stepper motor");
  Serial.println("4 to move L/R servos");
  Serial.println("5 to move top servo");
  Serial.println("...followed by angle position to move indicated motor to.");
}

void printPos(){
  
}

void setup()
{

  Serial.begin(9600);
  // Setup servo motors
  LServo.attach(LSERVO_PIN);
  RServo.attach(RSERVO_PIN);
  TServo.attach(TSERVO_PIN);

  // Setup stepper motors
  stepper1.setMaxSpeed(STEPPER_1_MAX_SPEED);
  stepper1.setAcceleration(STEPPER_1_MAX_ACCEL);
  
  stepper2.setMaxSpeed(STEPPER_2_MAX_SPEED);
  stepper2.setAcceleration(STEPPER_2_MAX_ACCEL);
  
  stepper3.setMaxSpeed(STEPPER_2_MAX_SPEED);
  stepper3.setAcceleration(STEPPER_3_MAX_ACCEL);
  


  pinMode(MOTOR_2_LIMIT, INPUT);
  pinMode(MOTOR_3_LIMIT, INPUT);
  pinMode(13, OUTPUT);

  digitalWrite(13, HIGH);
  /*
  //Moves to reference position for motors 2 and 3
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
  digitalWrite(13, LOW);

  

  printChoices();

  while(Serial.available()>0){
    dump = Serial.read();
  }
  
}

void loop()
{

  if(Serial.available()>0){
    
    choice = Serial.parseInt();
    
    dumpSerial();
    Serial.print(choice);
    Serial.println();

    // Move base stepper motor
    if(choice == 1){
      
      pos1 = readAngle();
      stepper1.move(pos1);
      while(stepper1.distanceToGo()!=0){
        stepper1.run();
      }
    }

    // Move right stepper motor
    else if(choice == 2){
      pos2 = readAngle();
      if(pos2>maxpos2){
        Serial.print("Enter a value less than ");
        Serial.println(maxpos2);
      }
      else{
        pos2 = degtostep(pos2);
        stepper2.move(pos2);
        while(stepper2.distanceToGo()!=0){

            stepper2.run();

        }
      }
    }

    // Move left stepper motor
    else if(choice == 3){
      pos3 = readAngle();
      if(pos3>maxpos3){
        Serial.print("Enter a value less than ");
        Serial.println(maxpos3);
      }
      else{
        pos3=degtostep(pos3)*-1;
        stepper3.move(pos3);
        while(stepper3.distanceToGo()!=0){

            stepper3.run();

        }
      }
    }

    // Move L/R Servo motors
    else if(choice == 4){
      pos4 = readAngle();
      LServo.write(pos4);
      RServo.write(180-pos4);
    }

    // Move top servo motor
    else if(choice == 5){
      pos5 = readAngle();
      TServo.write(pos5);
    }

    else{
      printChoices();
    }
  }
}
