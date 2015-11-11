/*************************************************************
Motor Shield Stepper Demo
by Randy Sarafan

For more information see:
http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/

int delaylegnth = 5000; //30;

void setup() {
  
  //establish motor direction toggle pins
  pinMode(12, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards???
  pinMode(13, OUTPUT); //CH B -- HIGH = forwards and LOW = backwards???
  
  //establish motor brake pins
  pinMode(9, OUTPUT); //brake (disable) CH A
  pinMode(8, OUTPUT); //brake (disable) CH B
  
  Serial.begin(9600);
}

void loop(){
Serial.println("*************");
  //  8 | 12 | 9 | 13
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B

  digitalWrite(12, HIGH);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  Serial.println("1");
  delay(delaylegnth);
  
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B

  digitalWrite(13, LOW);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  Serial.println("2");
  delay(delaylegnth);
  
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B

  digitalWrite(12, LOW);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  Serial.println("3");
  delay(delaylegnth);
    
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B

  digitalWrite(13, HIGH);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  Serial.println("4");
  delay(delaylegnth);

}
