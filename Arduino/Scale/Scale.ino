#define ADC_CLOCK 2
#define ADC_DATA  3

#define NUM_SAMPLES_LOG2 8
#define NUM_SAMPLES (1 << NUM_SAMPLES_LOG2)

#define ADC_BIT_PERIOD_MICROS 1

int32_t getADCReading()
{
  int32_t v = 0;

  while (digitalRead(ADC_DATA) == HIGH);
  
  noInterrupts();
  
  for (int i=0; i<24; i++)
  {
    digitalWrite(ADC_CLOCK, 1);
    delayMicroseconds(ADC_BIT_PERIOD_MICROS);
    
    v <<= 1;
    v |= (digitalRead(ADC_DATA) == HIGH) ? 1 : 0;
    
    digitalWrite(ADC_CLOCK, 0);
    delayMicroseconds(ADC_BIT_PERIOD_MICROS);    
  }
  
  digitalWrite(ADC_CLOCK, 1);
  delayMicroseconds(ADC_BIT_PERIOD_MICROS);
  digitalWrite(ADC_CLOCK, 0);
  
  interrupts();
  
  v |= (v & 0x00800000) ? 0xff000000 : 0x00000000; // sign extend
  
  return v;
}

int32_t getPreciseADCReading()
{
  int32_t v = 0;
  for (int i=0; i<NUM_SAMPLES; i++)
  {
    v += getADCReading();
  }
  return (v >> NUM_SAMPLES_LOG2);
}

int32_t calibration = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("catpoop v0.1");

  pinMode(ADC_CLOCK, OUTPUT);
  pinMode(ADC_DATA, INPUT);
  
  calibration = getPreciseADCReading();
  Serial.print("initial calibration: ");
  Serial.println(calibration);
}

void loop() 
{
  int32_t v = getPreciseADCReading();
  Serial.print("v: ");
  Serial.println(v - calibration);
}
