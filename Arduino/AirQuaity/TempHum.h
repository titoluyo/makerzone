#ifndef TempHum_h
#define TempHum_h

#include "Sensor.h"

#define CANTIDAD_VALORES 3

class TempHum : public Sensor
{
  public:
    TempHum(int pin);
    TempHum(int pin, int pin2);
    virtual void setup();
    virtual void sense();
    virtual void sense2();
    virtual char* getValue(int index);

  protected:
    float _val[CANTIDAD_VALORES];
    String _title[CANTIDAD_VALORES];
    DHT* _dht;
};

#endif

