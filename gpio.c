

/* ***********************  C-Modul: gpio.c  ********************************************
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
* In diesem Modul sind alle Funktionen realisiert, ddie zum Setzten bzw. Rücksetzen und Schreiben bzw. 
* Lesen des GPIO Pins notwending ist.  
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
* enum Pin_Number Pin(char Telegramm[]) --> Gibt der Pin Number basiernd auf das Kommunikationsprotokoll zürück. Dient der Lesbarkeit
* enum Mode Pin_Function(char c) --> Gibt der Pin Funktion  basiernd auf das Kommunikationsprotokoll zürück. Dient der Lesbarkeit
*
* enum Pin_Set_Reset  Pin_Set_Reset_Funktion(char c) --> Gibt der Pin Modus basiernd auf das Kommunikationsprotokoll zürück. Dient der Lesbarkeit
*
* void Pin_Init(char Telegramm[]) --> Initialierung der Pins
* void Pin_Manipulation(char Telegramm[])  --> Setzen oder Rücksetzen von Pins
* int Read_Single_Pin(char  Telegramm[] )  --> Einzelene Pins lesen
* void Pin_Set_Read_Write(char Telegramm[]) --> Pin  Lesen oder Schreiben
*
* Die ausfürhliche Beschreibung der Funtkionen sind unten vor deren Difinition zu finden. 
*
*
*
*
*
* Alle anderen Funktionen des Moduls sind durch den vorangestellten static Qualifier als lokale
* Funktionen ausgezeichnet.
*
* static  enum Mode Pin_Function(char c) --> Gibt der Pin Funktion  basiernd auf das Kommunikationsprotokoll zürück. Dient der Lesbarkeit
* static enum Pin_Set_Reset  Pin_Set_Reset_Funktion(char c) --> Gibt der Pin Modus basiernd auf das Kommunikationsprotokoll zürück. Dient der Lesbarkeit
********************************************************************************************************/

//************* Header-Dateien ****************


#include <stdio.h>
#include <stdlib.h>

//************ weitere Include-Dateien *********

#include <avr/io.h>
#include "gpio.h"
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



/*--------------+------------------------------------------------------------------+
| Name         |  Pin_Function                                                     |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Hilferfunktion um die Pinfunktion aus Telegramm zu bestimmen     |
|              |  Parameter: char c                                                |
|              |  Rückgabewert: enum Mode                                          |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/


static enum Mode Pin_Function(char c){

	switch(c)
	{
		case(0x08): return Input;//   0x08  Definiert in Kommunikationsprotokoll
		case(0x80): return Output; // 0x80 Definiert in Kommunikationsprotokoll
		default: return 0; 
	}
}


/*--------------+------------------------------------------------------------------+
| Name         |  Pin_Set_Reset_Funktion                                           |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Hilferfunktion um die Betriebmodus 						       |
|              |  des Pins aus Telegramm zu bestimmen.                             |
|              |  Parameter: char c                                                |
|              |  Rückgabewert: enum Pin_Set_Reset                                 |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/

static enum Pin_Set_Reset Pin_Set_Reset_Funktion(char c){

	switch(c)
	{
		case(0x08): return Set;// Pins Setzen 
		case(0x80): return Reset; // Pins Zuruecksetzen
		default: return 0; 
	}
}

/*--------------+------------------------------------------------------------------+
| Name         |  Pin                                                              |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Hilferfunktion um die ausgewählte  						       |
|              |  Pin  aus Telegramm zu bestimmen.                                 |
|              |  Parameter: char c                                                |
|              |  Rückgabewert: enum Pin_Number                                    |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/

	
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

/*--------------+------------------------------------------------------------------+
| Name         |  Pin_Init                                                         |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Die ausgewählte Pins  aus dem Telegramm initialisieren	       |
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

/*--------------+------------------------------------------------------------------+
| Name         |  Pin_Set_Read_Write                                               |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Die ausgewählte Pins  setzen oder löschen               	       |
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

/*--------------+------------------------------------------------------------------+
| Name         |  Read-Single_Pin                                                  |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Die ausgewählte Pins  lesen                             	       |
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
	



