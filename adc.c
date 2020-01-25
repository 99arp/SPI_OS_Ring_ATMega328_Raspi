

/* ***********************  C-Modul: adc.c  ********************************************
*
* Dieses Programm wurde mit Atmelstudio 7  als  Konsolenanwendung  erstellt.
*
* Das Modul ist in Ansi-C (C89) geschrieben. Die Erweiterungen des C99 Standard finden bis auf:
*
*   
*
*  keine Anwendung.
*
*
* In diesem Modul sind alle Funktionen realisiert, die
* zur Initialiserung der ADC, so wie zur AD bzw. DC Wandlung so wie  Interrupt Service Routine für ADC benötigt sind
*
*
*
*
* Das C- Modul arbeitet mit den Files-Scope-Variablen:
*
*  - Typ    Name              : 
*       
*
* Globale Variablen gibt es nicht. Das Modul stellt als Schnittstelle öffentliche
* Funktionen bereit:
*
*
*
*   void Adc_Init(char Telegramm[])  -->  Initiaierung der ADC- Kanal
*   uint8_t Get_Adc(char Telegramm[]) --> Gibt den AD-Wandlung Wert zurück
*
* Die ausfürhliche Beschreibung der Funtkionen sind unten von deren Difinition zu finden. 
*
*
*
*
*
* Alle anderen Funktionen des Moduls sind durch den vorangestellten static Qualifier als lokale
* Funktionen ausgezeichnet.
*
*   static enum ADC_Pin Selected_Pin(char c ) --> Zur Verbessurung der Lesbarbkeit. Gibt der Pinname von empafangenen Telegramm zurück
********************************************************************************************************/

//************* Header-Dateien ****************


#include <stdio.h>
#include <stdlib.h>

//************ weitere Include-Dateien *********

#include "adc.h"
#include<avr/io.h>
//**************************************************




//********** nicht öffentliche Konstanten **********

//**************************************************




//********* nicht öffentliche Strukturen ***********

//**************************************************




//****** nicht öffentliche Typendefinitionen *******

//**************************************************




//************* File-Scope-Variablen ***************

//**************************************************

//****************** Funktionen ********************

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
static enum ADC_Pin Selected_Pin(char c) {
  switch (c) {
  case (0x01): // Die  Zuweisung der Name und Int-Wert basierend auf Kommunikationsprotokoll ist im Header-Datei zu finden. 
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
  ADMUX  |= (1 << REFS1) | (1 << REFS0);  // AVCC als Referenz --> 0b1100 0000 letzte beide Bits REFS1 und REFS2 gesetzt. 
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler ( 1 /128)
  ADCSRB |= (0 << ADTS2) | (1 << ADTS1) | (1 << ADTS0); // Timer 0  compare Interrupt
  ADCSRA |= (1 << ADEN); // Enable ADC
  ADCSRA |= (1 << ADATE); // Enable Auto Trigger 

  ADCSRA = 0x9F; // Make sure the converter is enabled and ADIF cleared --> 0b 1001 0111 seibte Bit-> ADC on 4bit-> 

  switch (Selected_ADC_Pin) {

  case (ADC_PC0_): {

    DIDR0 |= 0x1; // Nur der Pin PC0 als ADC. Der Rest kann als GPIO benutzt werden            
    ADMUX |= (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0); // Tabelle Oben sehen // I need to check if it works

  } break;

  case (ADC_PC1_): {

    DIDR0 |= 0x2;
    ADMUX |=(0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0); //Siehe Case ADC_PC0_

  } break;

  case (ADC_PC2_): {

    DIDR0 |= 0x4;
    ADMUX |=(0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0); //Siehe Case ADC_PC0_

  } break;

  case (ADC_PC3_): {

    DIDR0 |= 0x8;
    ADMUX |=(0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0);//Siehe Case ADC_PC0_

  } break;

  case (ADC_PC4_): {

    DIDR0 |= 0x10;
    ADMUX |=(0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (0 << MUX0);//Siehe Case ADC_PC0_

  } break;

  case (ADC_PC5_): {

    DIDR0 |= 0x20;
    ADMUX |=(0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (1 << MUX0);//Siehe Case ADC_PC0_

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
  uint8_t adch = 0; // Starten der ADC
  ADCSRA |= (1 << ADSC); // Abfrage, ob die ADC fertig ist
  if ((ADCSRA & (1 << ADSC)) == 0); // Speichern des Inhalts des Register ADCH
  adch = ADCH; // uint wird auf einen char gecastet
  return ((char)adch); // Rückgabe der Auflösung
}
/*--------------+-----------------------------------------------------------+
| Name         | Timer0_Init()                                              |
+--------------+------------------------------------------------------------+
| Beschreibung |  Initialisert Timer0 für zylkklische AD-Wandlung           |
|              |  Parameter: uint16_t compareMatchRegister                  |
|              |  Rückgabewert: uint16t                                     |
|              |                                                            |
|              |                                                            |
+--------------+------------------------------------------------------------+
|Autor         |          Jamakatel                                         |
+--------------+------------------------------------------------------------+
| Notes        | Version 1.0 -- 31.10.2019                                  |
|              |                                                            |
|              |                                                            |
+--------------+-----------------------------------------------------------*/

void Timer0_Init( uint16_t  compareMatchRegister){

  TCCR0A = 0; // Reset Timer Count
  TCCR0A |= (1 << WGM01);   // CTC Mode
  TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00); // 1024 MHz
  TCNT0  = 0;  // Initailize 

  OCR0A  = compareMatchRegister;  //Timer Compare Value
  OCR0B  = compareMatchRegister;  // Timer Compare Value
  TIMSK0 = ( 1 << OCIE0B); // Timer0_Compare A interrupt. 
  sei();  // enable global interrupts
}

/*

Beispiel Implementation des Timer0_Interrupts 
ISR(TIMER0_OVF_vect)
{
	uint8_t  x = getAdc();
	Ringspeicher_Put_Override(Ringspeicher, x); 
}

/*/