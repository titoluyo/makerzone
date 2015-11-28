int led = 12;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
  if (Serial.available()){
    int data = Serial.read();
    char dato = (char)data;
    Serial.println(dato);
    if(dato == '1'){
      digitalWrite(led,HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(led,LOW);
      Serial.println("LOW");
    }
  }
}
