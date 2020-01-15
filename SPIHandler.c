#include "SPIhandler.h"
#include "pwm.h"
#include "adc.h"
#include "gpio.h"

#include <avr/io.h>
/* https://www.avrfreaks.net/forum/interrupt-driven-slave-spi */

/* This is a function pointer
	We use it to call the function corresponding to the third byte of Telegramm
	The Information are taken from Ringspeicher, which will be struct of chars probably
	. Then 3rd Byte is analysed and acoording to the third byte, a zeiger to the function 
	is returned. This Zeiger is also argument for minoos.c

*/

/*

This is what i want https://www.tablix.org/~avian/blog/archives/2012/06/spi_interrupts_versus_polling/


*/



static uint8_t* volatile burstData; 
static volatile int  burstLen = -1; 

ISR(SPI_STC_vect){

	burstLen --; 
	if(burstLen < 0 )
	{
		/*finished, turn off the interrupt request */
		SPCR &= ~_BV(SPIE) /* BV explained: https://www.microchip.com/webdoc/avrlibcreferencemanual/FAQ_1faq_use_bv.html*/


	}
	else {
		SPDR = *burstData; 
		 burstData++; 
	}

}

void sepa525_dataBurst(uint8_t* values, int len)
{	
	/*wait if software buffer is not empty */
	while (burstLen >= 0); 
	burstLen = len; 
	burstData =  values;

	/*enable Interrupt */

	SPCR |= _BV(SPIE); 

	/*start the transfer of the first byte */
	SPI_STC_vect(); 





}



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
		case(0x02) : return Pwm_Init_And_Set_Frequency; 
		case(0x03) : return Pwm_On; 
		case(0x04) : return Pwm_Off; 
		case(0x05) : return Adc_Init; 
		case(0x06) : return Get_Adc; 
		default    : return NULL; 

	}

}
/* To use it 

fptr z = Telegramm_Function_Assigner(c);
z();

*/
 
/*

A function that returns pointer to the function that needs to be done

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
	SPCR = (1<<SPE);// SPI enable						
}

/*

This will help:
https://electronics.stackexchange.com/questions/107146/avr-spi-slave-with-interrupt.Yo ta mug le gar<eko jastai xa ta: Muni tira chaii feri thik answer xa re
Or rather this
https://www.avrfreaks.net/forum/spi-interrupt-atmega328


and here is the answer: https://sites.google.com/site/qeewiki/books/avr-guide/spi
SPI AVR Setup : https://www.element14.com/community/docs/DOC-65037/l/avr151-setup-and-use-of-the-spi


*/

/*--------------+------------------------------------------------------------------+
| Name         |    SPI_SlaveReceive                                               |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  SPI Daten empfangen                                              |
|              |                                                                   |
|              |  Parameter: void                                                 |
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

  while(!(SPSR & (1<<SPIF))) {		// Hier ist die Polling von  was der Rede war Prüfung, ob die SPI-Interupt-Flag gesetzt ist	
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