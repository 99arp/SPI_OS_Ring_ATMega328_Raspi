#include "adc.h"

enum ADC_Pin Selected_Pin(char c) {
  switch (c) {
  case (0x01):
    return PC0_;
  case (0x02):
    return PC1_;
  case (0x03):
    return PC2_;
  case (0x04):
    return PC3_;
  case (0x05):
    return PC4_;
  case (0x06):
    return PC5_;
  default:
    return 0;
  }
}

/*

MUX[3:0]	Unsymmetrischer Eingang
0000	ADC0
0001	ADC1
0010	ADC2
0011	ADC3
0100	ADC4
0101	ADC5
0110	ADC6
0111	ADC7
1000	ADC8


REFS1	REFS0	Auswahl der Referenzspannung
0		  0		AREF, interne UREF ist abgeschaltet
0	      1		AUCC mit externem Kondensator am AREF-Pin
1	      0		reserviert
1	      1		Interne Referenzspannung 1,1 V mit externem
Kondensator an AREF-Pin

*/

void Adc_Init(char Telegramm[]) {
  enum SelectedPin Selected_ADC_Pin = ADC_Pin SelectedPin(Telegramm[1]);

  /*
              Initialisation und so weiter noch nicht gemacht.

  */

  ADCSRA = 0x97; // Make sure the converter is enabled and ADIF cleared

  switch (Selected_ADC_Pin) {

  case (PC0_): {

    DIDR0 |= 0x1; // Nur der Pin PC0 als ADC. Der Rest kann als GPIO benutzt werden            
    (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0); // Tabelle Oben sehen

  } break;

  case (PC1_): {

    DIDR0 |= 0x2;
    (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0);

  } break;

  case (PC2_): {

    DIDR0 |= 0x4;
    (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0);

  } break;

  case (PC3_): {

    DIDR0 |= 0x8;
    (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0);

  } break;

  case (PC4_): {

    DIDR0 |= 0x10;
    (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (0 << MUX0);

  } break;

  case (PC5_): {

    DIDR0 |= 0x20;
    (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (1 << MUX0);

  } break;
  
  default:
    return 0;
  }
}

uint8_t Get_Adc(char receivedData[]) {
  uint8_t adch = 0;
  // Starten der ADC
  ADCSRA |= (1 << ADSC);
  // Abfrage, ob die ADC fertig ist
  if ((ADCSRA & (1 << ADSC)) == 0)
    ;
  // Speichern des Inhalts des Register ADCH
  adch = ADCH;
  // uint wird auf einen char gecastet
  // Rückgabe der Auflösung
  return ((char)adch);
}
