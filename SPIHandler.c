#include "SPIhandler.h"
#include "pwm.h"
#include "adc.h"
#include "gpio.h"


/* https://www.avrfreaks.net/forum/interrupt-driven-slave-spi */

/* This is a function pointer
	We use it to call the function corresponding to the third byte of Telegramm
	The Information are taken from Ringspeicher, which will be struct of chars probably
	. Then 3rd Byte is analysed and acoording to the third byte, a zeiger to the function 
	is returned. This Zeiger is also argument for minoos.c

*/

ptr Telegramm_Function_Assigner(char c)
{

	switch (c){
		case(0x01) : return IO_Init; 
		case(0x02) : return Pin_Set_Reset; 
		case(0x03) : return Pwm_Init_And_Set_Frequency; 
		case(0x04) : return PWM_On; 
		case(0x05) : return PWM_Off; 
		case(0x06) : return ADC_Init; 
		case(0x07) : return Get_Adc; 
		default    : return ERROR; 

	}

}

 
/*

A function that returns pointer to the function that needs to be done

*/

 void SPI_SlaveInit(void) {
	
	DDRB |= (1<<PORTB4);// MISO als Output
	SPCR = (1<<SPE);// SPI enable						
}

/*

This will help:
https://electronics.stackexchange.com/questions/107146/avr-spi-slave-with-interrupt.Yo ta mug le gar<eko jastai xa ta: Muni tira chaii feri thik answer xa re
Or rather this
https://www.avrfreaks.net/forum/spi-interrupt-atmega328


*/


char SPI_SlaveReceive(void) {
  char data;							

  while(!(SPSR & (1<<SPIF))) {		// Hier ist die Polling von  was der Rede war Prüfung, ob die SPI-Interupt-Flag gesetzt ist	
  }
  data = SPDR; 
  		
  SPDR = 0;// Rücksetzten des Datenregisters	
 					
  return data;	 // Rückgabewert data (char)						
}

void SPI_SlaveSend(char sendBits) {	
	
  SPDR = sendBits;	 // Zuweisung des Übergabewertes in das Datenregister					
										
  while(!(SPSR & (1<<SPIF))) {	// Prüfung, ob die SPI-Interupt-Flag gesetzt ist					
  }
  
  SPDR = 0;			// Rücksetzten des Datenregisters				
} 