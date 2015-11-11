void setup() 
{ 
  Serial.begin(115200);
  Serial.println("Inicializando");
  Serial1.begin(115200); 
}
void loop()
{
 char c;
 if(Serial1.available()>0)
  {
    c=Serial1.read();
    Serial.print(c);
  }
  
}
