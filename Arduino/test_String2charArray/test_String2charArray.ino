void setup() {
  Serial.begin(115200);
  String trama = "2,1,20151114113954,1206.578273,7701.822705,79.30,22.20,999";
  trama += char(10);
  Serial.println(trama);
  Serial.println(sizeof(trama));
  Serial.println(trama.length());
  char tramac[trama.length()+1];
  trama.toCharArray(tramac,sizeof(tramac));
  Serial.println(sizeof(tramac));
  Serial.print(tramac);
  Serial.println("+");
}

void loop() {
  // put your main code here, to run repeatedly:

}
