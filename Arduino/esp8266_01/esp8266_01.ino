void setup() {
  Serial2.begin(115200);
  Serial.begin(9600);

}

void loop() {
  while(Serial2.available()) Serial.write(Serial2.read());
  while(Serial.available()) Serial2.write(Serial.read());
}
