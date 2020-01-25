/* ***********************  C-Modul: SPIHandler.c  ********************************************
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
* In diesem Modul sind alle Funktionen realisiert, die dafür nötig sind, die von SPI empfangengen Daten einem Funtkion zuzuweisen,
* einschließen die SPI Funktionalität und SPI Iterrupt. 
* 
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
* void SPI_SlaveInit(void); --> ATmega als Slave Initialiseren 
* void SPI_SlaveSend(char sendBits); --> Senden der Daten über SPI 
*
*
*
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
* 
********************************************************************************************************/

//************* Header-Dateien ****************


#include <stdio.h>
#include <stdlib.h>

//************ weitere Include-Dateien *********

#include "SPIHandler.h"
#include "pwm.h"
#include "adc.h"
#include "gpio.h"

#include <avr/io.h>
#include <avr/interrupt.h>
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
| Name         |    Telegramm_Function_Assinger                                    |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Ordnet dem Telegramm Nachricht einer entsprechenden  Funktion zu |
|              |                                                                   |
|              |  Parameter: char c                                                |
|              |  Rückgabewert:  fptr (Siehe header file für Beschreibung)         |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
fptr Telegramm_Function_Assigner(char c)
{

	switch (c){
		case(0x01) : return Pin_Init; 
		case(0x02) : return Pwm_Init_And_Set_Prescaler; 
		case(0x03) : return Pwm_On; 
		case(0x04) : return Pwm_Off; 
		case(0x05) : return Adc_Init; 
		case(0x06) : return Get_Adc; 
		case(0x07) : return Pin_Set_Read_Write;
		default    : return NULL; 

	}

}
/* To use it 

fptr z = Telegramm_Function_Assigner(c);
z();

*/
 
/*


*/
/*--------------+------------------------------------------------------------------+
| Name         |    SPI_SlaveInit                                                  |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  ATMega 328 als Slave in einer SPI-Kommunikation initialieren     |
|              |                                                                   |
|              |  Parameter: void                                                  |
|              |  Rückgabewert: void                                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
 void SPI_SlaveInit(void) {
	
	DDRB |= (1<<PORTB4);// MISO als Output
	SPCR &= ~(1<<MSTR);                // Set as slave 
  //  SPCR |= (1<<SPR0)|(1<<SPR1);       // divide clock by 128
    SPCR |= (1<<SPIE);                 // Enable SPI-Interrupt
	SPCR |= (1<<SPE);//  SPI enable						
	SPDR = 0; 
}






/*--------------+------------------------------------------------------------------+
| Name         |    SPI_SlaveReceive                                               |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  SPI Daten empfangen                                              |
|              |                                                                   |
|              |  Parameter: void                                                  |
|              |  Rückgabewert: char                                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
char SPI_SlaveReceive(void) {
  char data;							

  while(!(SPSR & (1<<SPIF))) {		//Obwohl hier ein While Loop gibt, ist es kein Polling. Die SPI arbeitet mit Flags. 
									// Das hier ist wichtig wenn man Daten länger als 8 bit schicken will. 
									// die SPI-Interupt-Flag wird benutzt und SPI wird eigentlich mit Interrupt gemacht.t	
  }
  data = SPDR; 
  		
  SPDR = 0;// Rücksetzten des Datenregisters	
 					
  return data;	 // Rückgabewert data (char)						
}

/*--------------+------------------------------------------------------------------+
| Name         |    SPI_SlaveSend                                                  |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  SPI Daten aussenden                                              |
|              |                                                                   |
|              |  Parameter: char sendBits                                         |
|              |  Rückgabewert: void                                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
void SPI_SlaveSend(char sendBits) {	
	
  SPDR = sendBits;	 // Zuweisung des Übergabewertes in das Datenregister					
										
  while(!(SPSR & (1<<SPIF))) {	// Prüfung, ob die SPI-Interupt-Flag gesetzt ist					
  }
  
  SPDR = 0;			// Rücksetzten des Datenregisters				
} 