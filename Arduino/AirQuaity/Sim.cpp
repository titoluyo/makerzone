#include "Sim.h"
#include <Arduino.h>
#include <Adafruit_FONA.h>
#include <SoftwareSerial.h>

Sim::Sim(uint8_t tx, uint8_t rx, uint8_t rst, uint8_t pwr) {
	_pwr = pwr;
//	fonaSS = new SoftwareSerial(2,3,false);
//	*fonaSerial = &fonaSS;
//	fona = new Adafruit_FONA(rst);
}

void Sim::setup() {
	pinMode(5, OUTPUT);
	
	Serial.println(F("Reiniciando FONA"));
	fonaSerial->begin(4800);
  bool initok = false;
  while (!initok) {
  	if(!fona->begin(*fonaSerial)){
  		Serial.println(F("No se encontró el FONA"));
  		//while(1);
      PowerToggle();
  	} else {
      initok = true;
  	}
  }

  fona->setGPRSNetworkSettings(F("movistar.pe"), F("movistar@datos"), F("movistar"));

	/*
	Serial.println("Registrando APN");
  fona->setGPRSNetworkSettings(F("movistar.pe"), F("movistar@datos"), F("movistar"));
  delay(5000);

  Serial.println("Deshabilitando Datos");
  if (!fona->enableGPRS(false))
    Serial.println(F("Failed to turn off Data"));
  delay(2000);

  Serial.println("Habilitando Datos");
  if (!fona->enableGPRS(true))
    Serial.println(F("Failed to turn on Data"));
  delay(5000);
*/
  Serial.println("Deshabilitando GPS");
  if (!fona->enableGPS(false))
    Serial.println(F("Failed to turn off GPS"));


  Serial.println("Habilitando GPS");
  if (!fona->enableGPS(true))
    Serial.println(F("Failed to turn on GPS"));
  delay(5000);
/*
  Serial.println("Habilitando tiempo GSM");
  if (!fona->enableNetworkTimeSync(true))
    Serial.println(F("Failed to enable tiempo GSM"));
  delay(5000);

  Serial.println("Habilitando tiempo NTP");
  if (!fona->enableNTPTimeSync(true, F("pool.ntp.org")))
    Serial.println(F("Failed to enable NTP"));
  delay(5000);


  //GPS Status
  int8_t stat = -1;
  while (stat < 2) {
    // check GPS fix
    stat = fona->GPSstatus();
    if (stat < 0)
      Serial.println(F("Failed to query"));
    if (stat == 0) Serial.println(F("GPS off"));
    if (stat == 1) Serial.println(F("No fix"));
    if (stat == 2) Serial.println(F("2D fix"));
    if (stat == 3) Serial.println(F("3D fix"));
    delay(1000);
  }
*/
  Serial.println("Setup terminado");
}

void Sim::PowerToggle(){
  pinMode(_pwr, OUTPUT);
	digitalWrite(_pwr, HIGH);
	delay(2200);
	digitalWrite(_pwr, LOW);
	delay(2200);
}

uint8_t Sim::getTime(char *buff, uint16_t maxlen){
  return fona->getTime(buff, maxlen);
}

uint8_t Sim::getGPS(uint8_t arg, char *buffer, uint8_t maxbuff) {
  return fona->getGPS(arg, buffer, maxbuff);
}

String valores[9];
uint8_t cont = 0;
String grados;
String minutos;
uint8_t Sim::getGPSvalores(uint8_t arg, char *buffer, uint8_t maxbuff) {
  getGPS(arg, buffer, maxbuff);
  int len = strlen(buffer);
  Serial.println(len);
  cont = 0;
  valores[0]="";
  for (uint8_t i = 0; i < len; i++) {
     if(buffer[i] == ','){
      cont++;
      valores[cont] = "";
     } else {
      valores[cont] += buffer[i];
     }
  }
  for (uint8_t i = 0; i < 9; i++) {
      Serial.print("Valor ");
      Serial.print(i);
      Serial.print(" ");
      Serial.println(valores[i]);
  }
  valores[4] = valores[4].substring(0, valores[4].indexOf('.'));
  Serial.print("Tiempo:");
  Serial.println(valores[4]);
}

uint8_t cantValoresSensores;
String Sim::construyeTrama(String valoresSensores[]){
  char sep = ',';
  String trama = String(VERSION);
  trama.concat(sep);
  trama.concat(NODO);
  trama.concat(sep);
/*
  char fecha[23];
  getTime(fecha,23);
  trama.concat(fecha);
  trama.concat(sep);
*/
  char gpsdata[120];
  getGPSvalores(0, gpsdata, 120);
  trama.concat(valores[4]);
  trama.concat(sep);
  trama.concat(valores[1]);
  trama.concat(sep);
  trama.concat(valores[2]);
  cantValoresSensores = sizeof(valoresSensores) + 1;
  for(uint8_t i = 0; i < cantValoresSensores; i++) {
    trama.concat(sep);
    trama.concat(valoresSensores[i]);  
  }
  Serial.println(trama);
  return trama;
}

void Sim::sendData(char *server, uint16_t port, char *tramac, uint8_t len) {
  if(!fona->TCPconnected()){
    if(!fona->TCPconnect(server, port)){
      Serial.println("Fallo al conectarse al servidor");
      return;
    }
  }
  Serial.println(tramac);
  Serial.println(len);
  if(fona->TCPsend(tramac, len)){
    Serial.println("Datos enviados satisfactoriamente");
  } else {
    Serial.println("Fallo al enviar");
  }
  //fona->TCPclose();
}

boolean Sim::getBattPercent(uint16_t *p){
  return fona->getBattPercent(p);
}

float Sim::gradosMinutos(String valor){
  int pos = valor.indexOf('.');
  grados = valor.substring(0, pos-2);
  minutos = valor.substring(pos-2, 5+pos+1);
  Serial.print(grados);
  Serial.print("+");
  Serial.println(minutos);
  char gc[grados.length()+1];
  grados.toCharArray(gc,grados.length()+1);
  char mc[5+pos+1];
  minutos.toCharArray(mc, 5+pos+1);
  float gf = grados.toFloat(); //atof(gc);
  float mf = minutos.toFloat(); //atof(mc);
  Serial.print(gf);
  Serial.print("#");
  Serial.println(mf);
  float result = atof(gc)+(atof(mc)/60.000000);
  return result;
}


