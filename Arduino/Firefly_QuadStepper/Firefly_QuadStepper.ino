/*
 20 JUNE 2013
 By Andrew O. Payne
 AccelStepper Library by Adafruit available at: https://github.com/adafruit/AccelStepper (Arduino 1.0 Compatible)
 
 This Firmata has been tested with both the Easy Stepper Driver V4.4 (developed by Brian Schmalz: http://www.schmalzhaus.com/EasyDriver/)
 as well as the Quad Steppper Driver (http://www.sparkfun.com/products/10507).
 
 NOTE: The Firefly Stepper Arduino Firmata sets the following pins:

 For Individual Motors:
 Motor 1  - Dir To Arduino Pin 2; Stp To Arduino Pin 3
 Motor 2  - Dir To Arduino Pin 4; Stp To Arduino Pin 5
 Motor 3  - Dir To Arduino Pin 6; Stp To Arduino Pin 7
 Motor 4  - Dir To Arduino Pin 8; Stp To Arduino Pin 9 

 For All Motors: 
 Rst Is Connected To +5v (High)
 Slp Is Connected To +5v (High)
 En Is Connected To Gnd (Low) 
 Gnd Must Be Connected Back To The Arduino Gnd

 For more information on connecting the circuit, see the illustrated diagram in the Grasshopper Examples folder
 */
 
#include <AccelStepper.h>
#define BAUDRATE 115200          //Set the Baud Rate to an appropriate speed
#define BUFFSIZE  256            // buffer one command at a time, 12 bytes is longer than the max length
#define DIR_PIN_A 2              //Set Direction Pin for Stepper A to Digital Pin 2
#define STEP_PIN_A 3             //Set Step Pin for Stepper A to Digital Pin 3
#define DIR_PIN_B 4              //Set Direction Pin for Stepper B to Digital Pin 4
#define STEP_PIN_B 5             //Set Step Pin for Stepper B to Digital Pin 5
#define DIR_PIN_C 6              //Set Direction Pin for Stepper C to Digital Pin 6
#define STEP_PIN_C 7             //Set Step Pin for Stepper C to Digital Pin 7
#define DIR_PIN_D 8              //Set Direction Pin for Stepper D to Digital Pin 8
#define STEP_PIN_D 9             //Set Step Pin for Stepper D to Digital Pin 9

long incoming_motorPos[4] = {0,0,0,0};  //Declare some arrays for motor positions
long current_motorPos[4] = {0,0,0,0};
long previous_motorPos[4] = {0,0,0,0};
int motorSpeed = 2000;       //Set default speed value
int motorAcc = 1000;         //Set default acceleration value
int motorRun = 1;            //Set default run value
int motorReset = 0;          //Set default reset value

boolean moving_1 = true;
boolean moving_2 = true;
boolean moving_3 = true;
boolean moving_4 = true;

boolean wasmoving_1 = true;
boolean wasmoving_2 = true;
boolean wasmoving_3 = true;
boolean wasmoving_4 = true;

boolean update_motor_1 = true;
boolean update_motor_2 = true;
boolean update_motor_3 = true;
boolean update_motor_4 = true;

char *parseptr;
char buffidx;

int mask=0;               // declare a bitmask variable
char buffer[BUFFSIZE];    // this is the double buffer
uint16_t bufferidx = 0;   // a type of unsigned integer of length 16 bits  

AccelStepper stepper1(1, STEP_PIN_A, DIR_PIN_A);  // Define some steppers and their pins: Ex: Accelstepper stepper1(1, 3, 4) <- STEP PIN 3, DIR PIN 4.
AccelStepper stepper2(1, STEP_PIN_B, DIR_PIN_B);
AccelStepper stepper3(1, STEP_PIN_C, DIR_PIN_C);
AccelStepper stepper4(1, STEP_PIN_D, DIR_PIN_D);

/*==============================================================================
 * SETUP() This code runs once
 *============================================================================*/
 
void setup()
{  
  stepper1.setCurrentPosition(0);  //move steppers to default position
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);
  stepper4.setCurrentPosition(0);  
  setStepperSpeeds();

  Serial.begin(BAUDRATE);         // start serial communication
}

/*==============================================================================
 * LOOP() This code loops continuously
 *============================================================================*/
  
void loop()
{
  if (motorReset == 1) { 
    stepper1.setCurrentPosition(current_motorPos[0]);
    stepper2.setCurrentPosition(current_motorPos[1]);
    stepper3.setCurrentPosition(current_motorPos[2]);
    stepper4.setCurrentPosition(current_motorPos[3]);
  }
    
  if (motorRun == 1) {
    moving_1 = stepper1.run();    //tell the motors to move to their positions
    moving_2 = stepper2.run();
    moving_3 = stepper3.run();
    moving_4 = stepper4.run();
    
    boolean maskchanged=false;
         
    if(!moving_1 && wasmoving_1) {
        mask |= 0x01;               //set outgoing bitmask  
        update_motor_1 = false;     //reset need update flags
        maskchanged=true;
      }
      if(!moving_2 && wasmoving_2) {
        mask |= 0x02;               //set outgoing bitmask 
        update_motor_2 = false;     //reset need update flags
        maskchanged=true;
      }
      if(!moving_3 && wasmoving_3) {
        mask |= 0x04;               //set outgoing bitmask
        update_motor_3 = false;     //reset need update flags
        maskchanged=true;
      }
      if(!moving_4 && wasmoving_4) {
        mask |= 0x08;               //set outgoing bitmask
        update_motor_4 = false;     //reset need update flags
        maskchanged=true;
      }
      
      if(moving_1) mask &= ~0x01;        //set outgoing bitmask
      if(moving_2) mask &= ~0x02;
      if(moving_3) mask &= ~0x04;
      if(moving_4) mask &= ~0x08;

      if (mask!=0 && maskchanged) Serial.println(mask);    //send character for the next line from Firefly
 
      wasmoving_1=moving_1;
      wasmoving_2=moving_2;
      wasmoving_3=moving_3;
      wasmoving_4=moving_4;
  }
}


double parsedecimal(char *str)
{
  return atof(str);
}

void serialEvent() {
   char c;    // holds one character from the serial port
   if (Serial.available() > 0) {
    c = Serial.read();      // read one character
    buffer[bufferidx] = c;  // add to buffer

    if (c == '\n') {  
      buffer[bufferidx+1] = 0; // terminate it
      parseptr = buffer;       // offload the buffer into temp variable

      //********************************************************

      incoming_motorPos[0] = parsedecimal(parseptr);   // parse the first number
      parseptr = strchr(parseptr, ',')+1;              // move past the ","

      incoming_motorPos[1] = parsedecimal(parseptr);   // parse the next number
      parseptr = strchr(parseptr, ',')+1;              // move past the ","

      incoming_motorPos[2] = parsedecimal(parseptr);   // parse the next number
      parseptr = strchr(parseptr, ',')+1;              // move past the ","

      incoming_motorPos[3] = parsedecimal(parseptr);   // parse the next number
      parseptr = strchr(parseptr, ',')+1;              // move past the ","

      motorSpeed = parsedecimal(parseptr);             // parse the next number
      parseptr = strchr(parseptr, ',')+1;              // move past the ","

      motorAcc = parsedecimal(parseptr);               // parse the next number
      parseptr = strchr(parseptr, ',')+1;              // move past the ","

      motorRun = parsedecimal(parseptr);               // parse the next number
      parseptr = strchr(parseptr, ',')+1;              // move past the ","

      motorReset = parsedecimal(parseptr);             // parse the next number

      setStepperSpeeds();
      
      if(incoming_motorPos[0] != previous_motorPos[0]) {
        current_motorPos[0] = incoming_motorPos[0];      //update target position
        update_motor_1 = true;                           //set update flag
      }
      if(incoming_motorPos[1] != previous_motorPos[1]) {
        current_motorPos[1] = incoming_motorPos[1];      //update target position
        update_motor_2 = true;                           //set update flag
      }
      if(incoming_motorPos[2] != previous_motorPos[2]) {
        current_motorPos[2] = incoming_motorPos[2];      //update target position
        update_motor_3 = true;                           //set update flag
      }
      if(incoming_motorPos[3] != previous_motorPos[3]) {
        current_motorPos[3] = incoming_motorPos[3];      //update target position
        update_motor_4 = true;                           //set update flag
      }
      
      previous_motorPos[0] = incoming_motorPos[0];    //update previous target position
      previous_motorPos[1] = incoming_motorPos[1];    //update previous target position
      previous_motorPos[2] = incoming_motorPos[2];    //update previous target position
      previous_motorPos[3] = incoming_motorPos[3];    //update previous target position
      
      stepper1.moveTo(current_motorPos[0]);           //set new absolute target position
      stepper2.moveTo(current_motorPos[1]);           //set new absolute target position
      stepper3.moveTo(current_motorPos[2]);           //set new absolute target position
      stepper4.moveTo(current_motorPos[3]);           //set new absolute target position

      bufferidx = 0;       // reset the buffer for the next read
      return;              //return so that we don't trigger the index increment below
    }
    // didn't get newline, need to read more from the buffer
    bufferidx++;    // increment the index for the next character
    if (bufferidx == BUFFSIZE-1) {  //if we get to the end of the buffer reset for safety
      bufferidx = 0;
    }
  }
}

void setStepperSpeeds() {

  stepper1.setMaxSpeed(motorSpeed);
  stepper1.setAcceleration(motorAcc);

  stepper2.setMaxSpeed(motorSpeed);
  stepper2.setAcceleration(motorAcc);

  stepper3.setMaxSpeed(motorSpeed);
  stepper3.setAcceleration(motorAcc);

  stepper4.setMaxSpeed(motorSpeed);
  stepper4.setAcceleration(motorAcc);
}

