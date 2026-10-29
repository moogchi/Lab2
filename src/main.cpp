#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  DDRD |= (1 << PD0);
  TCCR0A = 0b00100011;
  TCCR0B = 0b00001011;
  OCR0A = 124;

  DDRD &= ~(1 << PD6);
  ADMUX = 0b01000001;
  ADCSRA = 0b11100110;
  ADCSRB = 0b00100000;
  DIDR2 |= (1 << ADC9D);
}

void loop() {
  float aval;
  long x;
  x = millis();
  aval = abs(3 * sin(2 * 3.141592654 * x / 1000));
  OCR0B = aval / 3 * 125;

  unsigned short *ADCData;
  unsigned short ADCVal;
  ADCData = (unsigned short *)0x78;
  ADCVal = (*ADCData & 0x3FF);
  float fADCVal;
  fADCVal = ((float)ADCVal) / 1023 * 3;

  Serial.print(abs(aval)); // Original rectified sinusoid
  Serial.print(" ");
  Serial.println(fADCVal); // Analog voltage measured from ADC
}
