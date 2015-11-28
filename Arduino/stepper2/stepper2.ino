/* 
 Stepper Motor Control with Arduino Motor Control Shield V3.0.

 This requires the following modification to the shield:
- Remove IC2
- Bridge IC2 pins 4 and 12, connecting DIRA/Arduino 12 with IC3 2A
- Bridge IC2 pins 6 and 9, connecting DIRB/Arduino 13 with IC3 3A

 This program drives a bipolar stepper motor. The motor is controlled
 by Arduino pins 8, 9, 12, 13. Additionally Pins 10 and 11 are required.

 The motor should do five revolutions into one and five into another direction.

 */

#include <Stepper.h>

int out1 = 8;
int out2 = 9;
int enA  = 10;  // Enable pin 1 on Motor Control Shield   
int enB  = 11;  // Enable pin 2 on Motor Control Shield   
int dirA = 12;  // Direction pin dirA on Motor Control Shield
int dirB = 13;  // Direction pin dirB on Motor Control Shield


const int stepsPerRevolution = 20;  // change this to fit the number of steps per revolution
                                     // for your motor

// Initialize the stepper library on pins 8, 9, 12, 13:
Stepper myStepper(stepsPerRevolution, out1, dirA, out2, dirB);            

void setup() {
  // Set speed to 60 rpm:
  myStepper.setSpeed(60);

pinMode(out1, OUTPUT);
pinMode(out2, OUTPUT);
pinMode(dirA, OUTPUT);
pinMode(dirB, OUTPUT);

  // Enable IC3 outputs.
  pinMode(enA, OUTPUT);
  digitalWrite (enA, HIGH);
  pinMode(enB, OUTPUT);
  digitalWrite (enB, HIGH);
}

void loop() {
  // Step five revolutions into one direction:
  myStepper.step(stepsPerRevolution*15);
  delay(2000);

  // Step five revolutions in the other direction:
  myStepper.step(-stepsPerRevolution*15);
  delay(2000); 
}
