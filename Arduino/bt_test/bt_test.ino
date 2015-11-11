String command; // a string to hold the incoming command
boolean commandReceived = false; // whether the command has been received in full

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("Iniciando...");
}

void loop() {
  // main loop
  serialEvent();
  handleCommand();
}

bool primero = true;
float lat = 0.0;
float lon = 0.0;
String valStr = "";
void serialEvent(){
  while (Serial1.available()) {
  // all we do is construct the incoming command to be handled in the main loop

    // get the incoming byte from the serial stream
    char incomingByte = (char)Serial1.read();
    //Serial.print(incomingByte);

    if (incomingByte == '!')
    {
       // marks the end of a command
       commandReceived = true;
       lon = command.toFloat();
       Serial.println(lon,10);
       return;
    }
    else if (incomingByte == '@')
    {
       // marks the start of a new command
       command = "";
       commandReceived = false;
       return;
    }
    else if (incomingByte == ';')
    {
       lat = command.toFloat();
       command = "";
       Serial.println(lat,10);
    }
    else
    {
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
