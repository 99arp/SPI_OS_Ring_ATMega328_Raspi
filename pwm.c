
#include <avr/io.h>
#include "pwm.h"
#include "enmus.h"

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

 void Set_Frequency(char  Telegramm[] ){  /*minimum working  example on adc.h" */

 	char  Prescaler_From_Telegramm = Telegramm[2]; 
 	enum Prescaler_Value Prescaler = Prescale_Calculator(Prescaler_From_Telegramm)

 	char  Kanal_From_Telegramm =  Telegramm [1]; 
 	enum Selected_Kanal Kanal = Kanal_Select(Kanal_From_Telegramm); 

 	switch(Kanal)
 	{
 		case(Kanal1):
 		{
 			DDRD |= (1 << PD5 )  //PD5 als Ausgang
 			OCR0B = 0;
 			TCNT0 = 0;
 			switch(Prescaler):
 			{
 				case(Prescaler1):
 								{


 								}break; 
 				case(Prescaler8):
 								{


 								}break; 

 				case(Prescaler64):
 								{

 								}break;
 				case(Prescaler256):
 								{

 								}break; 								
 				case(Prescaler1024):
 								{

 								}break;
 				default:
 						return 0; 

 			}break; 
 			case(Kanal2):
 		{
 			DDRD |= (1 << PD6 )  //PD6 als Ausgang
 			OCR0B = 0;
 			TCNT0 = 0;
 			switch(Prescaler):
 			{
 				case(Prescaler1):
 								{


 								}break; 
 				case(Prescaler8):
 								{


 								}break; 

 				case(Prescaler64):
 								{

 								}break;
 				case(Prescaler256):
 								{

 								}break; 								
 				case(Prescaler1024):
 								{

 								}break;
 				default:
 						return 0; 

 			}break; 
 			
 		

 		}
 		default:
 			return 0; 
 	}





 }