/// # Description:
// # The sketch for driving the gsm mode via the Arduino board
 
// # Steps:
// #        1. connect D2M and D2
// #        2. connect D3M and D3
// #        3. connect pwrkey and GND
 
 
byte gsmDriverPin[3] = {
  2,3};//The default digital driver pins for the GSM and GPS mode

void setup()
{    
  //Init the driver pins for GSM function
  for(int i = 0 ; i < 3; i++){
    pinMode(gsmDriverPin[i],OUTPUT);
  }
  digitalWrite(2,LOW);//Enable the GSM mode
  digitalWrite(3,HIGH);//Disable the GPS mode
  delay(2000);
  Serial.begin(9600); //set the baud rate
  delay(5000);//call ready
  delay(5000);
  delay(5000);
}
 
void loop()
{  
  Serial.println("AT"); //Send AT command  
  delay(2000);
  Serial.println("AT");   
  delay(2000);
  //Send message
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"990610289\"");//Change the receiver phone number
  delay(1000);
  Serial.print("HELLO");//the message you want to send
  delay(1000);
  Serial.write(26);
  while(1);
}
