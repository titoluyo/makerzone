
 
// Used pins
const int dataPin = 4;
const int latchPin = 7;
#define clockPin 9
 
// Pump
#define PumpPin 5
int Drop;
 
// Jumper pins
#define Button 10     // Onboard button
#define InPosLED 11   // Yellow LED
#define ReadyLED 12   // Green LED
#define PumpRUN 13    // Force the pump to run
 
 const int XMax = 600;
 const int YMax = -900;
 const int Xorigo = 20;
 const int Yorigo = -24;
 const int CellDistX = 77;
 const int CellDistY = -77;

 volatile boolean Xint = false;
 volatile boolean Yint = false;

// Single-step high torque
 int Fram[4] = {B00000011, B00000110, B00001100, B00001001};
 int Bak[4] =  {B00000011, B00001001, B00001100, B00000110};
 
 
void setup() {
   Serial.begin(9600);
   pinMode(dataPin, OUTPUT);
   pinMode(clockPin, OUTPUT);
   pinMode(latchPin, OUTPUT);
   
   pinMode(PumpPin, OUTPUT);
   digitalWrite(PumpPin, LOW);
   
   pinMode(InPosLED, OUTPUT);
   digitalWrite(InPosLED, LOW);
   pinMode(ReadyLED, OUTPUT);
   digitalWrite(ReadyLED, LOW);
   pinMode(Button, INPUT);
   digitalWrite(Button, HIGH); 
   
   pinMode(PumpRUN, INPUT);
   digitalWrite(PumpRUN, HIGH); 
   
   ReadVolume();
   
   attachInterrupt(1, Xtrigger, RISING);
   attachInterrupt(0, Ytrigger, RISING);
   Home();
   WaitForGO();
 }
 
void DoSomething()
 {
   Pump();
 }
 
void ReadVolume()
{
  Drop = analogRead(A0);    
  Drop = map(Drop, 0, 1023, 300, 2000);
}
 
void Pump()
 {
   ReadVolume();   // change volume while running
   digitalWrite(PumpPin, HIGH);   
   delay(Drop); 
   digitalWrite(PumpPin, LOW);
   delay(50);
 }
 
 void WaitForGO()
 {
   while (digitalRead(Button))
   {
     if (digitalRead(PumpRUN))
     {
       ReadVolume();
       Pump();
       delay(1000);
     }
   }
   digitalWrite(ReadyLED, LOW);
 }
 
void loop() 
{ 
  
  for (int j=0; j < 6; j++)
    {
      DoSomething();
      for (int i=0; i < 7; i++)
      {
        Move(CellDistX,0);
        DoSomething();
       }  
       Move(0,CellDistY);
       DoSomething();
       for (int k=0; k < 7; k++)
      {
        Move((CellDistX * -1),0);
        DoSomething();
       }  
       Move(0,CellDistY);
    }
   
    while (true)
      {
        delay(1000);  // Stop after one run
      }

 }
 

