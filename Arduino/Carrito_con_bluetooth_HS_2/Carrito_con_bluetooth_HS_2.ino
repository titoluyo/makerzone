#include <Ultrasonic.h>

String command; // a string to hold the incoming command
boolean commandReceived = false; // whether the command has been received in full

int izqA = A0; 
int izqB = A1; 
int derA = A2; 
int derB = A3; 

int izqA2 = A4; 
int izqB2 = A5; 
int derA2 = A6; 
int derB2 = A7; 

bool primero = true;
String valStr = "";

#define START_CMD_CHAR '>'

#define DEBUG 1 // Set to 0 if you don't want serial output of sensor data

float val1, val2, val3;
float yaw, pitch, roll;
float lat, lon, alt;

float dest_lat =0.0;
float dest_lon = 0.0;


/* Pines del ultrasonido */

#define TRIG 6	//Disparador de ultrasónico
#define ECHO 5	//Recepción de eco

#define OBSTRACLE_DISTANCE 15.0
#define TURN_DELAY 200

Ultrasonic ultrasonic(TRIG, ECHO);
float distance = 0;

void setup()  { 
  Serial.begin(9600);
  Serial.println("Iniciando....");
  Serial1.begin(9600);
  Serial3.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  Serial3.flush();
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  
  pinMode(derA2, OUTPUT);
  pinMode(derB2, OUTPUT);
  pinMode(izqA2, OUTPUT);
  pinMode(izqB2, OUTPUT);
 } 
 
void loop()   
  
  {
    stopMove();
    serialEvent();
    handleCommand();

  if (dest_lon > 0) {
    checkGPS();            //Bucle de medición de sensores y GPS
      
    checkDistance();	//Bucle de medición de distancia
    
    moove();		//Bucle de activación de motores
  }  
  delay(10);
}

void serialEvent(){
  while (Serial1.available()) {
    String cadenax = Serial1.readString();
    Serial.println(cadenax);
  // all we do is construct the incoming command to be handled in the main loop

    // get the incoming byte from the serial stream
    char incomingByte = (char)Serial1.read();
    //Serial.print(incomingByte);
Serial.println(command);
    if (incomingByte == '!')
    {
      Serial.println("1");
       // marks the end of a command
       commandReceived = true;
       dest_lon = command.toFloat();
       Serial.println(lon,10);
       return;
    }
    else if (incomingByte == '@')
    {
      Serial.println("2");
      // marks the start of a new command
       command = "";
       commandReceived = false;
       return;
    }
    else if (incomingByte == ';')
    {
             Serial.println("3");
       dest_lat = command.toFloat();
       command = "";
       Serial.println(lat,10);
    }
    else
    {
      Serial.println("4");
      command += incomingByte;
      return;
    }

  }
}

void handleCommand() {

  if (!commandReceived) return; // no command to handle

  // variables to hold the command id and the command data
  int id;
  int data[9];

  // NOT SURE WHAT TO DO HERE!!

  // flag that we've handled the command 
  commandReceived = false;
}

void checkGPS()
{
 
 Serial3.flush();
  int sensorType = 0;
  unsigned long logCount = 0L;

  char getChar = ' ';  //read serial

  // wait for incoming data
  if (Serial3.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag 
  getChar = Serial3.read();

  // parse incoming pin# and value  
  sensorType = Serial3.parseInt(); // read sensor typr
  logCount = Serial3.parseInt();  // read total logged sensor readings
  val1 = Serial3.parseFloat();  // 1st sensor value
  val2 = Serial3.parseFloat();  // 2rd sensor value if exists
  val3 = Serial3.parseFloat();  // 3rd sensor value if exists
  
  switch(sensorType){
    case 3:
      yaw = val1;  // 1st sensor value
      pitch = val2;  // 2rd sensor value if exists
      roll = val3;  // 3rd sensor value if exists
      break;
    case 98:
      lat = val1;  // 1st sensor value
      lon = val2;  // 2rd sensor value if exists
      alt = val3;  // 3rd sensor value if exists

      // calculo de angulo
      float y = lat - dest_lat;
      float x = lon - dest_lon;
      float ang = RAD_TO_DEG * ( atan2(-y, -x) + PI );
      float ang_to = ang - yaw;
      Serial.print("Angulo:");
      Serial.print(ang);
      Serial.print(" | Diff: ");
      Serial.print(ang_to);
      break;
      
      if(ang_to < 180){
       goLeft(); 
      }
      if(ang_to > 180){
       goRight();
      } 
      if(ang_to == 180){
        stopMove();
        delay(1000);
      }
  }

      
}

void checkDistance()  //Medir distancia
{
  distance = ultrasonic.Ranging(CM);
  Serial.println(distance);
}

void moove()
{
  if( distance > OBSTRACLE_DISTANCE )
  {    
    goForward();
    delay(TURN_DELAY);
  }
  else
  {
    stopMove();
    delay(TURN_DELAY);
    goRight();
    delay(1000);
    goForward();
    delay(1000);
    stopMove();
    delay(TURN_DELAY);
    goLeft();
    delay(1000);
   }
}

  void goForward()
{
  analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 255);  
      analogWrite(izqA, 255);

      analogWrite(derB2, 0);     
      analogWrite(izqB2, 0); 
      analogWrite(derA2, 255);  
      analogWrite(izqA2, 255);
  
}
  
  void goLeft(){          // Boton giro izquierda 
      analogWrite(derB, 0);     
      analogWrite(izqB, 128); 
      analogWrite(derA, 128);  
      analogWrite(izqA, 0);      
      
      analogWrite(derB2, 0);     
      analogWrite(izqB2, 128); 
      analogWrite(derA2, 128);  
      analogWrite(izqA2, 0);
  }
  void stopMove(){         // Boton Parar
      analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 0);    
      analogWrite(izqA, 0); 
      
      analogWrite(derB2, 0);     
      analogWrite(izqB2, 0); 
      analogWrite(derA2, 0);    
      analogWrite(izqA2, 0); 
  }
  void goRight(){          // Girar derecha
      analogWrite(derB, 128);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 0);  
      analogWrite(izqA, 128);      
      
      analogWrite(derB2, 128);     
      analogWrite(izqB2, 0); 
      analogWrite(derA2, 0);  
      analogWrite(izqA2, 128);
  } 
  
 void goBack(){          // Boton Reversa
      analogWrite(derB, 255);     
      analogWrite(izqB, 255); 
      analogWrite(derA, 0);  
      analogWrite(izqA, 0);

      analogWrite(derB2, 255);     
      analogWrite(izqB2, 255); 
      analogWrite(derA2, 0);  
      analogWrite(izqA2, 0);      
  }

