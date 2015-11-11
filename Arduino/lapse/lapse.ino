int start = 0;
int lapse = 2000;

void setup() {
  Serial.begin(9600);
  start = millis();
}

void loop() {
  int now = millis();
  if(now - start >= lapse) {
    Serial.println(now);
    start = now;
  }
}
