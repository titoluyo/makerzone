#include <Servo.h>
#define NUMSERVOS 3       // Cantidad de servos
#define PINGRABA 4        // Pin de SWITCH que determina el modo
#define PINMODO 2         // Pin de PULSADOR que determina cuando graba la posicion
#define MAXPASOS 300      // Maxima cantidad de pasos
int paso = 0;             // contador de pasos;
int ultimoPaso = 0;       // Contiene el ultimo paso guardado
byte position[MAXPASOS][NUMSERVOS];  // Array de 100 pasos, de los N servos
Servo servos[NUMSERVOS];  // Array de los servos
byte potpin[NUMSERVOS] = {A0, A1, A2}; //, A3, A4};  // Array de pines de potenciometros
byte pinservo[NUMSERVOS] = {5, 6, 9}; //, 10, 3};    // Array de pines de servos
bool modoGraba = true;    // Modo: true:Graba, false:Ejecuta
byte limites[NUMSERVOS][2] = { {0,180}, {82,178}, {5,180} }; //valores limites de cada servo de mi brazo {inferior, superior}

// graba la posicion de los potenciometros en el paso
void savePos() {
  if (paso >= MAXPASOS)   // Si excede la cantidad de pasos comienza a sobreescribir del inicio
    paso = 0;
  Serial.print("Grabando paso (");
  Serial.print(paso);
  Serial.print(")");
  for (byte i = 0; i < NUMSERVOS; i++) {
    int lectura = analogRead(potpin[i]);
    int valor = map(lectura, 0, 1023, limites[i][0], limites[i][1]);
    Serial.print(" | ");
    //Serial.print(lectura);
    //Serial.print(",");
    Serial.print(valor);
    position[paso][i] = valor;
  }
  Serial.println("");
  paso++;
  ultimoPaso = paso;
}

// ejecuta la posicion en el paso
void execPos() {
  if (paso == ultimoPaso){
    Serial.println("Ultimo paso");
    paso++; // Para que el mensaje solo salga una vez
  }
  if (paso >= ultimoPaso) return; // Si llego al ultimo paso no avanza
  Serial.print("Ejecutando paso:");
  Serial.print(paso);
  for (byte i = 0; i < NUMSERVOS; i++) {
    servos[i].write(position[paso][i]);
    delay(15);
    Serial.print(" | ");
    Serial.print(position[paso][i]);
  }
  Serial.println("");
  paso++;
  delay(1000);
}

// validaciones del modo de grabacion o ejecucion
void validarModo() {
  bool modo = digitalRead(PINMODO);
  // si cambio de modo resetear paso a 0
  bool cambio = false;
  if (modoGraba != modo) {
    cambio = true;
    Serial.print("Cambio de modo, Modo graba:");
    Serial.println(modo);
  } else {
    cambio = false;
  }
  modoGraba = modo;
  if (cambio) { 
    paso = 0;
  }

}

// Arduino setup
void setup() {
  Serial.begin(9600);
  for (byte i = 0; i < NUMSERVOS; i++) {
    servos[i].attach(pinservo[i]);
  }
  pinMode(PINGRABA, INPUT);
  pinMode(PINMODO, INPUT);
  //Valores iniciales de mi brazo/servos
  servos[0].write(0);
  servos[1].write(178);
  servos[2].write(90);
}

// Arduino loop
void loop() {
  validarModo();
  if (modoGraba) {  // modo Graba
    int graba = digitalRead(PINGRABA);
    if (graba == HIGH) {
      savePos();
      delay(1000);
    }
  } else { // modo Ejecucion
    execPos();
  }
}

