

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Power on");
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()==0) {
  }
  int command = Serial.parseInt();
  switch (command){
    case 1: Serial.println("1 ON");
            digitalWrite(8, HIGH);
            break;
    case 2: Serial.println("2 ON");
            digitalWrite(9, HIGH);
            break;
    case 3: Serial.println("3 ON");
            digitalWrite(10, HIGH);
            break;
    case 4: Serial.println("4 ON");
            digitalWrite(11, HIGH);
            break;

    case 5: Serial.println("1 OFF");
            digitalWrite(8, LOW);
            break;
    case 6: Serial.println("2 OFF");
            digitalWrite(9, LOW);
            break;
    case 7: Serial.println("3 OFF");
            digitalWrite(10, LOW);
            break;
    case 8: Serial.println("4 OFF");
            digitalWrite(11, LOW);
            break;

  }
}
