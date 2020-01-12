#include <avr/io.h>
#include "gpio.h"

enum Mode Pin_Function(char c){

	switch(c)
	{
		case(0x08): return Input;//   0x08  Definiert in Kommunikationsprotokoll
		case(0x80): return Output; // 0x80 Definiert in Kommunikationsprotokoll
		default: return 0; 
	}
}
enum Pin_Set_Reset Pin_Set_Reset_Funktion(char c){

	switch(c)
	{
		case(0x08): return Set;// Pins Setzen 
		case(0x80): return Reset; // Pins Zuruecksetzen
		default: return 0; 
	}
}
	
enum Pin_Number Pin(char Telegramm[]){  // Take whole thing as argument. and do two different switch case. 
	
	switch(Telegramm[2])
	{
		/*zweiten Datenbyte*/
		case(1): return PC0_; //Wert der 2. Daten-Byte von Kommunikation protokoll
		case(2): return PC1_;
		case(3): return PC2_;
		case(4): return PC3_;
		case(5): return PC4_;
		case(6): return PC5_;
		case(7): return PD3_;
		default: return 0; 
	}

	switch(Telegramm[1])
	{
		/*1. Daten-Byte*/
		case(1): return PD5_; // Rainers Version hat hier 0. Kann nicht stimmen. 
		case(2): return PD6_;
		case(3): return PD7_;
		case(4): return PB0_; 
		case(5): return PB1_; 
		default: return 0; 
		


	}
}

	void Pin_Init(char Telegramm[])
	{

		enum  Mode Output_Input = Pin_Function( Telegramm[1]);
		enum Pin_Number Selected_Pin = Pin( Telegramm[2]); 


		switch(Output_Input)
		{
			case(Input):
			{
				switch(Selected_Pin)
				{
					case (PB0_): DDRB &= ~(1 << PB0); break; 
					case (PB1_): DDRB &= ~(1 << PB1); break; 
					case (PC0_): DDRC &= ~(1 << PC0); break;
					case (PC1_): DDRC &= ~(1 << PC1); break;
					case (PC2_): DDRC &= ~(1 << PC2); break;
					case (PC3_): DDRC &= ~(1 << PC3); break;
					case (PC4_): DDRC &= ~(1 << PC4); break;
					case (PC5_): DDRC &= ~(1 << PC5); break;
					case (PD3_): DDRD &= ~(1 << PD3); break; 
					case (PD5_): DDRD &= ~(1 << PD5); break;
					case (PD6_): DDRD &= ~(1 << PD6); break;
					case (PD7_): DDRD &= ~(1 << PD7); break;
					default: return 0; 
					
				}

			}break; 
			
			case(Output):
			{
				switch(Selected_Pin)
				{
					case (PB0_): DDRB |= (1 << PB0); break; 
					case (PB1_): DDRB |= (1 << PB1); break; 
					case (PC0_): DDRC |= (1 << PC0); break;
					case (PC1_): DDRC |= (1 << PC1); break;
					case (PC2_): DDRC |= (1 << PC2); break;
					case (PC3_): DDRC |= (1 << PC3); break;
					case (PC4_): DDRC |= (1 << PC4); break;
					case (PC5_): DDRC |= (1 << PC5); break;
					case (PD3_): DDRD |= (1 << PD3); break; 
					case (PD5_): DDRD |= (1 << PD5); break;
					case (PD6_): DDRD |= (1 << PD6); break;
					case (PD7_): DDRD |= (1 << PD7); break;
					default: return 0; 

				}


			}break; 
		}


	}
	void Pin_Set_Read_Write(char Telegramm[])
	{
	/* if i change it to read write https://www.arnabkumardas.com/online-courses/avr-gpio-programming-tutorial-atmega328p-avr-8-bit/*/
		enum  Mode Set_Reset = Pin_Function( Telegramm[1]);
		enum Pin_Number Selected_Pin = Pin( Telegramm[2]); 


		switch(Set_Reset) 
		{
			case(Reset):
			{
				switch(Selected_Pin)
				{
					case (PB0_): PORTB &= ~(1 << PB0); break; 
					case (PB1_): PORTB &= ~(1 << PB1); break; 
					case (PC0_): PORTC &= ~(1 << PC0); break;
					case (PC1_): PORTC &= ~(1 << PC1); break;
					case (PC2_): PORTC &= ~(1 << PC2); break;
					case (PC3_): PORTC &= ~(1 << PC3); break;
					case (PC4_): PORTC &= ~(1 << PC4); break;
					case (PC5_): PORTC &= ~(1 << PC5); break;
					case (PD3_): PORTD &= ~(1 << PD3); break; 
					case (PD5_): PORTD &= ~(1 << PD5); break; 
					case (PD6_): PORTD &= ~(1 << PD6); break; 
					case (PD7_): PORTD &= ~(1 << PD7); break; 
					default: return 0; 
					
				}

			}break; 
			
			case(Set):
			{
				switch(Selected_Pin)
				{
					case (PB0_): PORTB |= (1 << PB0); break; 
					case (PB1_): PORTB |= (1 << PB1); break; 
					case (PC0_): PORTC |= (1 << PC0); break;
					case (PC1_): PORTC |= (1 << PC1); break;
					case (PC2_): PORTC |= (1 << PC2); break;
					case (PC3_): PORTC |= (1 << PC3); break;
					case (PC4_): PORTC |= (1 << PC4); break;
					case (PC5_): PORTC |= (1 << PC5); break;
					case (PD3_): PORTD |= (1 << PD3); break; 
					case (PD5_): PORTD |= (1 << PD5); break; 
					case (PD6_): PORTD |= (1 << PD6); break; 
					case (PD7_): PORTD |= (1 << PD7); break; 
					default: return 0; 

				}


			}break; 
		}

	}


	int Read_Single_Pin( char Telegramm[] )
	{
		enum Pin_Number Single_Selected_Pin = Pin( Telegramm[2]);
		switch(Single_Selected_Pin)
				{
					case (PB0_): return PB0; 
					case (PB1_): return PB1; 
					case (PC0_): return PC0;
					case (PC1_): return PC1;
					case (PC2_): return PC2;
					case (PC3_): return PC3;
					case (PC4_): return PC4;
					case (PC5_): return PC5;
					case (PD3_): return PD3; 
					case (PD5_): return PD5; 
					case (PD6_): return PD6; 
					case (PD7_): return PD7; 
					default: return 0; 
					
				}

	}
	



