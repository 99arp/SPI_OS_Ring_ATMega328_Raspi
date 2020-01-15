
#include <avr/io.h>
#include "pwm.h"

/*
16 bit PWM Beispiel
https://sites.google.com/site/qeewiki/books/avr-guide/pwm-on-the-atmega328 


/*--------------+------------------------------------------------------------------+
| Name         |  Prescale_Calculator                                              |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion um den Wert des Prescalers zu bestimmen   	       |
|              |                                                                   |
|              |  Parameter: char c                                                |
|              |  Rückgabewert: enum Prescaler_Value                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
enum Prescaler_Value Prescale_Calculator(char c)
 {

 	switch (c)
 	{
 		case(0x01):  return Prescaler1;  //Kommunikationsprotokoll. Hex Werte der Binaeren Char
 		case(0x02):  return Prescaler8; 
 		case(0x0A):  return Prescaler64; 
 		case(0x10): return Prescaler256; 
 		case(0x20): return Prescaler1024; 

 		default:     return 0;   

 	}
 }
/*--------------+------------------------------------------------------------------+
| Name         |  DutyCycle                                                        |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion um den Wert des Dutycycles zu bestimmen   	       |
|              |                                                                   |
|              |  Parameter: char c                                                |
|              |  Rückgabewert: enum DutyCycle_Value                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
 enum DutyCycle_Value DutyCycle(char c)
 {

 	switch (c)
 	{
 		case(10):  return DutyCycle10; // Kommunikationsprotokoll. Decimal. Already converted from binary 
 		case(20):  return DutyCycle20; // von Kommunikationsprotokoll
 		case(30):  return DutyCycle30; 
 		case(40):  return DutyCycle40; 
 		case(50):  return DutyCycle50; 
 		case(60):  return DutyCycle60; 
 		case(70):  return DutyCycle70; 
 		case(80):  return DutyCycle80; 
 		case(90):  return DutyCycle90; 
 		
 		default:     return ON;   

 	}

 }
/*--------------+------------------------------------------------------------------+
| Name         |  Kanal_Select                                                     |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion um den ausgewählten Kanal zu bestimmen   	       |
|              |                                                                   |
|              |  Parameter: char c                                                |
|              |  Rückgabewert: enum Selected_Kanal                                |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
enum Selected_Kanal Kanal_Select (char c)
{
	switch(c)
	{
		case(1): return Kanal1; 
		case(2): return Kanal2; 
		default: return 0; 
	}

}
/*--------------+------------------------------------------------------------------+
| Name         |  Pwm_Init_And_Set_Freqeuncy                                       |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  PWM initialisieren, un die  Frequenz setzen     	               |
|              |                                                                   |
|              |  Parameter: char Telegramm[]                                      |
|              |  Rückgabewert: void                                               |
|              |                                                                   |
|              |                                                                   |
|              | 	CS02	CS01	CS00	Beschreibung                           |
|              | 	0		0		0	Stop, der Zähler/Zeitgeber0 wird angehalten|
|              | 	0		0		1	clkI/O (kein Vorteiler)                    |
|              | 	0		1		0	clkI/O/8                                   |
|              | 	0		1		1	clkI/O/64                                  |
|              | 	1		0		0	clkI/O/256                                 |
|              | 	1		0		1	clkI/O/1024                                |
|              | 	1		1		0	Speisung von Pin T0, fallende Flanke       |
|              | 	1		1		1	Speisung von Pin T0, steigende Flanke      |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
 void Pwm_Init_And_Set_Frequency(char  Telegramm[] ){  /*minimum working  example on adc.h" */

 	char  Prescaler_From_Telegramm = Telegramm[2]; 
 	enum Prescaler_Value Prescaler = Prescale_Calculator(Prescaler_From_Telegramm);

 	char  Kanal_From_Telegramm =  Telegramm [1]; 
 	enum Selected_Kanal Kanal = Kanal_Select(Kanal_From_Telegramm); 

 	switch(Kanal)
 	{
 		case(Kanal1):
 		{
 			DDRD |= (1 << PD5 );  //PD5 als Ausgang
 			OCR0B = 0;            // Register, in dem Vergleichwert gespeichert wird. in Setpwm einstellbar
 			TCNT0 = 0;            // Counter Value, initialiest null. 
 			TCCR0A |= (1 << COM0B1); // Non-inverting mode. Pulse happens at the beginning of the period. 
 			TCCR0A |= (1 << WGM01 )| (1 << WGM00 ); // set fast PWM Mode WGM02 is 0 by Default. 
 		}break; 

 		case(Kanal2):
 		{
 			DDRD |= (1 << PD6 );  //PD6 als Ausgang
 			OCR0B = 0;
 			TCNT0 = 0;
 			TCCR0B |= (1 << COM0A1); // Non-inverting mode. Pulse happens at the beginning of the period. 
 			TCCR0A |= (1 << WGM01 )| (1 << WGM00 ); // set fast PWM Mode WGM02 is 0 by Default. 
 		}break; 
 		default: 
 			return 0; 

 			switch(Prescaler)
 			{
 				case(Prescaler1):
 								{
 									TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00); 



 								}break; 
 				case(Prescaler8):
 								{
 									TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);  // Table for prescaler value sehen

 								}break; 

 				case(Prescaler64):
 								{
 									TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
 								}break;
 				case(Prescaler256):
 								{
 									TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);
 								}break; 								
 				case(Prescaler1024):
 								{
 									TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
 								}break;
 				default:
 						return 0; 

 			}
 	}





 }
/*--------------+------------------------------------------------------------------+
| Name         |  PWM_On                                                           |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  PWM einschalten  	                                               |
|              |                                                                   |
|              |  Parameter: char Telegramm[]                                      |
|              |  Rückgabewert: void                                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
 void Pwm_On(char Telegramm[]) {
	char dutyCycle = Telegramm[2];
	char Kanal_From_Telegramm = Telegramm[1]; 
	


	if(Kanal_From_Telegramm == 1) {			// Kanal 1 Possible becasue 0x01 = int 1 
		OCR0B = (255/100)*dutyCycle;
		}

	if(Kanal_From_Telegramm == 2) {			// Kanal 2
		OCR0A = (255/100)*dutyCycle;
		}
	}
/*--------------+------------------------------------------------------------------+
| Name         |  PWM_Off                                                          |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  PWM Ausschalten 	                                               |
|              |                                                                   |
|              |  Parameter: char Telegramm[]                                      |
|              |  Rückgabewert: void                                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
void Pwm_Off(char Telegramm[]) {
	char Kanal_From_Telegramm = Telegramm[2]; 
	
	if(Kanal_From_Telegramm == 1) {			// Kanal 1
		DDRD &= ~(1 << PD5);
		TCCR0A &= ~(1 << COM0B1);
		}
	if(Kanal_From_Telegramm == 2) {			// Kanal 2
		DDRD &= ~(1 << PD5);
		TCCR0A &= ~(1 << COM0A1);
		}
	}