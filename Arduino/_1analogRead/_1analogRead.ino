#include <SD.h>

const int chipSelect = 4;

String padLeft(int numero)
{
  String cadena = String(numero);
  Serial.println(cadena);
  int longitud = 4 - cadena.length();
  for(int i=0;i<longitud;i++)
  {
    cadena = "0"+cadena;
  }
}

void setup() {
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  int a0 = analogRead(0);
  int a1 = analogRead(1);
  int a2 = analogRead(2);

  String dataString = "";
  dataString = padLeft(a0)+"|"+padLeft(a1)+"|"+padLeft(a2);
  
  
  
  File dataFile = SD.open("brazo04.txt", FILE_WRITE);
  if (dataFile) {
    //dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  delay(500);        // delay in between reads for stability
}


