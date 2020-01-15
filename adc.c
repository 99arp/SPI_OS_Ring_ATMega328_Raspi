#include "adc.h"
#include<avr/io.h>


/*--------------+------------------------------------------------------------+
| Name         | Selected_Pin                                                |
+--------------+-------------------------------------------------------------+
| Beschreibung | Eine Helferfunktion, um die eingegangenen Datenbytes, einem |
|              | Pin zuzweisen                                               |
|              | Parameter: char c: 1. Daten-Byte des Telegramm              |
|              | Rückgabewert: enum ADC_Pin                                  |
+--------------+-------------------------------------------------------------+
|Autor         |          Jamakatel                                          |
+--------------+-------------------------------------------------------------+
| Notes        | Version 1.0 -- 31.10.2019                                   |
|              |                                                             |
|              |                                                             |
+--------------+------------------------------------------------------------*/
enum ADC_Pin Selected_Pin(char c) {
  switch (c) {
  case (0x01):
    return ADC_PC0_;
  case (0x02):
    return ADC_PC1_;
  case (0x03):
    return ADC_PC2_;
  case (0x04):
    return ADC_PC3_;
  case (0x05):
    return ADC_PC4_;
  case (0x06):
    return ADC_PC5_;
  default:
    return 0;
  }
}

/*



*/
/*--------------+-----------------------------------------------------------+
| Name         | Adc_Init                                                   |
+--------------+------------------------------------------------------------+
| Beschreibung |  Initiiert die ADC Känale einzelnen                        |
|              |  Parameter: char Telegramm[]:                              |
|              |  Rückgabewert: void                                        |
|              |                                                            |
|              |    Pinfunktionen
|              |                                                            |
|              |    MUX[3:0]  Unsymmetrischer Eingang                       |
|              |    0000  ADC0                                              |
|              |    0001  ADC1                                              |
|              |    0010  ADC2                                              |
|              |    0011  ADC3                                              |
|              |    0100  ADC4                                              |
|              |    0101  ADC5                                              |
|              |    0110  ADC6                                              |
|              |    0111  ADC7                                              |
|              |    1000  ADC8                                              |
|              |                                                            |
|              |                                                            |
|              |    REFS1 REFS0 Auswahl der Referenzspannung                |
|              |    0       0   AREF, interne UREF ist abgeschaltet         |
|              |    0       1   AUCC mit externem Kondensator am AREF-Pin   |
|              |    1       0   reserviert                                  |
|              |    1       1   Interne Referenzspannung 1,1 V mit externem |
|              |    Kondensator an AREF-Pin                                 |
+--------------+------------------------------------------------------------+
|Autor         |    Jamakatel                                               |
+--------------+------------------------------------------------------------+
| Notes        | Version 1.0 -- 31.10.2019
|              | 
|              | 
+--------------+-----------------------------------------------------------*/
void Adc_Init(char Telegramm[]) {
  enum ADC_Pin Selected_ADC_Pin =  Selected_Pin(Telegramm[1]);

  /*
              Initialisation und so weiter noch nicht gemacht.

  */

  ADCSRA = 0x97; // Make sure the converter is enabled and ADIF cleared

  switch (Selected_ADC_Pin) {

  case (ADC_PC0_): {

    DIDR0 |= 0x1; // Nur der Pin PC0 als ADC. Der Rest kann als GPIO benutzt werden            
    (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0); // Tabelle Oben sehen

  } break;

  case (ADC_PC1_): {

    DIDR0 |= 0x2;
    (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0);

  } break;

  case (ADC_PC2_): {

    DIDR0 |= 0x4;
    (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0);

  } break;

  case (ADC_PC3_): {

    DIDR0 |= 0x8;
    (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0);

  } break;

  case (ADC_PC4_): {

    DIDR0 |= 0x10;
    (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (0 << MUX0);

  } break;

  case (ADC_PC5_): {

    DIDR0 |= 0x20;
    (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (1 << MUX0);

  } break;
  
  default:
    return 0;
  }
}
/*--------------+-----------------------------------------------------------+
| Name         | Get_Adc                                                    |
+--------------+------------------------------------------------------------+
| Beschreibung |  holt die ADC-Werte aus dem iniierten Känale               |
|              |  Parameter: char Telegramm[]:                              |
|              |  Rückgabewert: uint8_t                                     |
|              |  Hierbei wird der adch value auf char gecastet             |
|              |                                                            |
|              |                                                            |
+--------------+------------------------------------------------------------+
|Autor         |          Jamakatel                                         |
+--------------+------------------------------------------------------------+
| Notes        | Version 1.0 -- 31.10.2019                                  |
|              |                                                            |
|              |                                                            |
+--------------+-----------------------------------------------------------*/
uint8_t Get_Adc(char Telegramm[]) {
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
