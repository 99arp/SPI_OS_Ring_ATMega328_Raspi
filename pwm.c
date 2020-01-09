
#include <avr/io.h>
#include "pwm.h"

/*
16 bit PWM Beispiel
https://sites.google.com/site/qeewiki/books/avr-guide/pwm-on-the-atmega328 


*/

enum Prescaler_Value Prescale_Calculator(char c)
 {

 	switch (c)
 	{
 		case(0x01):  return Prescaler1;  //Kommunikationsprotokoll. Hex Werte der Binaeren Char
 		case(0x02):  return Prescaler8; 
 		case(0x0A):  return Prescaler64; 
 		case(0x10): return Prescaler256; 
 		case(0x20): return Prescaler1024; 

 		default:     return ERROR;   

 	}
 }

 enum DutyCycle_value DutyCycle(char c)
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

enum Selected_Kanal Kanal_Select (char c)
{
	switch(c)
	{
		case(1): return Kanal1; 
		case(2): return Kanal2; 
		default: return ERROR; 
	}

}

 void Pwm_Init_And_Set_Frequency(char  Telegramm[] ){  /*minimum working  example on adc.h" */

 	char  Prescaler_From_Telegramm = Telegramm[2]; 
 	enum Prescaler_Value Prescaler = Prescale_Calculator(Prescaler_From_Telegramm)

 	char  Kanal_From_Telegramm =  Telegramm [1]; 
 	enum Selected_Kanal Kanal = Kanal_Select(Kanal_From_Telegramm); 

 	switch(Kanal)
 	{
 		case(Kanal1):
 		{
 			DDRD |= (1 << PD5 )  //PD5 als Ausgang
 			OCR0B = 0;            // Register, in dem Vergleichwert gespeichert wird. in Setpwm einstellbar
 			TCNT0 = 0;            // Counter Value, initialiest null. 
 			TCCR0A |= (1 << COM0B1); // Non-inverting mode. Pulse happens at the beginning of the period. 
 			TCCR0A |= (1 << WGM01 )| (1 << WGM00 ); // set fast PWM Mode WGM02 is 0 by Default. 
 		}break; 

 		case(Kanal2):
 		{
 			DDRD |= (1 << PD6 )  //PD6 als Ausgang
 			OCR0B = 0;
 			TCNT0 = 0;
 			TCCR0B |= (1 << COM0A1); // Non-inverting mode. Pulse happens at the beginning of the period. 
 			TCCR0A |= (1 << WGM01 )| (1 << WGM00 ); // set fast PWM Mode WGM02 is 0 by Default. 
 		}break; 
 		default: 
 			return 0; 

 			switch(Prescaler):
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

 void Set_Pwm(char Telegramm[]) {
	char dutyCycle = Telegramm[2];
	char Kanal_From_Telegramm = Telegramm[1]; 
	


	if(Kanal_From_Telegramm == 1) {			// Kanal 1 Possible becasue 0x01 = int 1 
		OCR0B = (255/100)*dutyCycle;
		}

	if(Kanal_From_Telegramm == 2) {			// Kanal 2
		OCR0A = (255/100)*dutyCycle;
		}
	}

void Pwm_Off(char Telegramm[]) {
	if(Kanal_From_Telegramm == 1) {			// Kanal 1
		DDRD &= ~(1 << PD5);
		TCCR0A &= ~(1 << COM0B1);
		}
	if(Kanal_From_Telegramm == 2) {			// Kanal 2
		DDRD &= ~(1 << PD5);
		TCCR0A &= ~(1 << COM0A1);
		}
	}