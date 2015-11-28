#ifndef Mq2_h
#define Mq2_h

#include "Sensor.h"

#define CANTIDAD_VALORES 1

class Mq2 : public Sensor
{
  public:
    Mq2(int pin);
    Mq2(int pin, int pin2);
    virtual void setup();
    virtual void sense();
    virtual void sense2();
    virtual char* getValue(int index);

  protected:
    float _val[CANTIDAD_VALORES];
    String _title[CANTIDAD_VALORES];
    int _pin_a0;
    int _valor_analogico;
};

#endif

