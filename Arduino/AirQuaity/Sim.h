#ifndef Sim_h
#define Sim_h

#include <Arduino.h>
#include <Adafruit_FONA.h>
#include <SoftwareSerial.h>

#define VERSION 2
#define NODO 1

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4
#define FONA_PWR 5

class Sim {
	public:
		// ctor
		Sim(uint8_t tx, uint8_t rx, uint8_t rst, uint8_t pwr);
		void setup();
    void PowerToggle();
    String construyeTrama(String valores[]);
    uint8_t getTime(char *buff, uint16_t maxlen);
    uint8_t getGPS(uint8_t arg, char *buffer, uint8_t maxbuff);
    uint8_t getGPSvalores(uint8_t arg, char *buffer, uint8_t maxbuff);
    void sendData(char *server, uint16_t port, char *trama, uint8_t len);
	  boolean getBattPercent(uint16_t *p);
 
	private:
		/*
		SoftwareSerial fonaSS;
		SoftwareSerial *fonSerial;
    Adafruit_FONA *fona;
    */
    SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
    SoftwareSerial *fonaSerial = &fonaSS;
    Adafruit_FONA *fona = new Adafruit_FONA(FONA_RST);
    float gradosMinutos(String valor);
		uint8_t _pwr;
};


#endif
