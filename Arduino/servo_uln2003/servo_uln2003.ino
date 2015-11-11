 //Programa : Controle de sentido de rotacao de motor de passo  
 //Autor : Arduino e Cia  
   
 #include <Stepper.h>  
 int pinobotao_ah = 3;   //Porta botao sentido anti-horario  
 int pinobotao_h = 2;   //Porta botano sentido horario  
 int passos = 50;     //Passos a cada acionamento do botao  
 int leitura = 0;     //Armazena o valor lido do botao horario  
 int leitura2 = 0;     //Armazena o valor lido do botao anti-horario  
   
 const int stepsPerRevolution = 4095;   
   
 //Inicializa a biblioteca utilizando as portas de 8 a 11 para  
 //ligacao ao motor  
 Stepper myStepper(stepsPerRevolution, 8,10,9,11);        
   
 void setup()   
 {
  Serial.begin(9600);  
  pinMode(pinobotao_h, INPUT);  
  pinMode(pinobotao_ah, INPUT);  
  myStepper.setSpeed(60); //Determina a velocidade do motor  
 }  
   
 void loop()  
 {  
  //Gira o motor no sentido horario  
  leitura = digitalRead(pinobotao_h);   
  {  
  if (leitura != 0)
    Serial.println("A");  
   myStepper.step(-passos);   
  }  
  //Gira o motor no sentido anti-horario  
  leitura2 = digitalRead(pinobotao_ah);  
  if (leitura2 != 0)  
  {  
   Serial.println("B");
   myStepper.step(passos);   
  }   
 }  
