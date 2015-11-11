/*
 PROJECT: SensoDuino 0.17 
 PROGRAMMER: Hazim Bitar (techbitar at gmail dot com)
 DATE: Sep 30, 2013
 FILE: sensoduino.ino
 LICENSE: Public domain
 */

#define START_CMD_CHAR '>'

#define DEBUG 1 // Set to 0 if you don't want serial output of sensor data

float val1, val2, val3;
float yaw, pitch, roll;
float lat, lon, alt;

float dest_lat = -12.072365;
float dest_lon = -77.080778;

void setup() {
  Serial.begin(9600);
  Serial.flush();
}

void loop()
{
  Serial.flush();
  int sensorType = 0;
  unsigned long logCount = 0L;

  char getChar = ' ';  //read serial

  // wait for incoming data
  if (Serial.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag 
  getChar = Serial.read();

  // parse incoming pin# and value  
  sensorType = Serial.parseInt(); // read sensor typr
  logCount = Serial.parseInt();  // read total logged sensor readings
  val1 = Serial.parseFloat();  // 1st sensor value
  val2 = Serial.parseFloat();  // 2rd sensor value if exists
  val3 = Serial.parseFloat();  // 3rd sensor value if exists
  
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
    }

  if (DEBUG) {
    Serial.print("Sensor type: ");
    Serial.println(sensorType);
//    Serial.print("Sensor log#: ");
//    Serial.println(logCount);
    switch(sensorType){
      case 3:
      Serial.print("Val[0]: ");
      Serial.println(yaw);
  //    Serial.print("Val[1]: ");
  //    Serial.println(pitch);
  //    Serial.print("Val[2]: ");
  //    Serial.println(roll);
        break;
      case 98:
        Serial.print("Lat: ");
        Serial.print(lat);
        Serial.print("| Lon: ");
        Serial.println(lon);
        //Serial.print("| Alt: ");
        //Serial.println(alt);
        break;
    }
    Serial.println("-----------------------");
    delay(20);
  }
}



