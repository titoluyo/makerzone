void Home()
{
 Move(20,-20);
 Move(-1000,1000);
 Xint = false;
 Yint = false;
 Move(Xorigo,Yorigo);
 digitalWrite(ReadyLED, HIGH);
}

void Move(int X, int Y)
{
  int X_dir,Y_dir;
  digitalWrite(InPosLED, LOW);
  while (X != 0 || Y != 0)
  {
    if (Xint) X = 0;  // handle interrupts
    if (Yint) Y = 0;
    
    if (X > 0) X_dir = 1;
    if (X < 0) X_dir = -1;
    if (X == 0) X_dir = 0;
   
    if (Y > 0) Y_dir = 1;
    if (Y < 0) Y_dir = -1;
    if (Y == 0) Y_dir = 0;
   
    TakeStep(X_dir, Y_dir);
    
    X = X - X_dir;
    Y = Y - Y_dir;
  }
  // Remove power from stepper's
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0);   
  digitalWrite(latchPin, HIGH);
  digitalWrite(InPosLED, HIGH);

}

void TakeStep(int X_dir, int Y_dir)
{
  int Xcode, Ycode;
  int Data;

  for (int i=0; i <= 3; i++)
  {
   Xcode = 0;
   Ycode = 0;
   if (X_dir ==  1) Xcode = Fram[i];
   if (X_dir == -1) Xcode = Bak[i];
   if (Y_dir ==  1) Ycode = Fram[i];
   if (Y_dir == -1) Ycode = Bak[i];
   Data = Ycode << 4;
   Data = Data + Xcode;
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, Data);   
   digitalWrite(latchPin, HIGH);  
   delay(5);
  }
}

void Xtrigger()
{
  detachInterrupt(1);
  Xint = true;
}

void Ytrigger()
{
  detachInterrupt(0);
  Yint = true;
}

 



