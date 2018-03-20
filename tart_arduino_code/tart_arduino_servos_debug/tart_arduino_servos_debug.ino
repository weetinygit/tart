#include <Servo.h>

// Stepper motors pins
#define MOTOR_1 9
#define MOTOR_2 10
#define MOTOR_3 11

#define MOTOR_1_LOWER 65
#define MOTOR_1_UPPER 85
#define MOTOR_2_LOWER 70
#define MOTOR_2_UPPER 110
#define MOTOR_3_LOWER 66
#define MOTOR_3_UPPER 106

#define MOTOR_1_ZERO 90
#define MOTOR_2_ZERO 92
#define MOTOR_3_ZERO 86
#define TSERVO_OFFSET 0
#define LSERVO_ZERO 55
#define RSERVO_ZERO 0

#define MOTOR_1_POLARITY 1
#define MOTOR_2_POLARITY 1
#define MOTOR_3_POLARITY 1
#define TSERVO_POLARITY 1
#define LSERVO_POLARITY -1
#define RSERVO_POLARITY 1

// Servo motors pins
#define LSERVO_PIN 6// left servo motor
#define RSERVO_PIN 7 // right servo motor
#define TSERVO_PIN 8 // top servo motor

//Servo instances
Servo motor1, motor2, motor3, LServo, RServo, TServo;

int pos1, pos2, pos3, pos4, pos5;
int angle, choice;
char dump;

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
  motor1.attach(MOTOR_1);
  motor2.attach(MOTOR_2);
  motor3.attach(MOTOR_3);
  LServo.attach(LSERVO_PIN);
  RServo.attach(RSERVO_PIN);
  TServo.attach(TSERVO_PIN);  
  motor1.write(MOTOR_1_ZERO);
  motor2.write(MOTOR_2_ZERO);
  motor3.write(MOTOR_3_ZERO);
  LServo.write(LSERVO_ZERO);
  RServo.write(RSERVO_ZERO);
  TServo.write(90+TSERVO_OFFSET);

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
    Serial.println(choice);

    // Move base stepper motor
    if(choice == 1){
      pos1 = readAngle();
      if(pos1<MOTOR_1_LOWER||pos1>MOTOR_1_UPPER){
        Serial.print("Enter a value less than ");
        Serial.print(MOTOR_1_UPPER);
        Serial.print(" or more than ");
        Serial.println(MOTOR_1_LOWER);
      }
      else{
        motor1.write(pos1*MOTOR_1_POLARITY);
        }
      }

    // Move right stepper motor
    else if(choice == 2){
      pos2 = readAngle();
      if(pos2<MOTOR_2_LOWER||pos2>MOTOR_2_UPPER){
        Serial.print("Enter a value less than ");
        Serial.print(MOTOR_2_UPPER);
        Serial.print(" or more than ");
        Serial.println(MOTOR_2_LOWER);
      }
      else{
        motor2.write(pos2*MOTOR_2_POLARITY);
        Serial.print("Writing to servo 2 value of ");
        Serial.println(pos2);
        }
      }

    // Move left stepper motor
    else if(choice == 3){
      pos3 = readAngle();
      if(pos3<MOTOR_3_LOWER||pos3>MOTOR_3_UPPER){
        Serial.print("Enter a value less than ");
        Serial.print(MOTOR_3_UPPER);
        Serial.print(" or more than ");
        Serial.println(MOTOR_3_LOWER);
      }
      else{
        motor3.write(pos3*MOTOR_3_POLARITY);
        Serial.print("Writing to servo 3 value of ");
        Serial.println(pos3);
        }
      }

    // Move L/R Servo motors
    else if(choice == 4){
      pos4 = readAngle();
      LServo.write(90+pos4);
      RServo.write(180-pos4);
      Serial.print("Writing to servo LR value of ");
      Serial.println(pos4);
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
