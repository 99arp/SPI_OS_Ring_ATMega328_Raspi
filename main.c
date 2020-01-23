
#define F_CPU 16000000UL
#include<stdio.h>
#include<stddef.h>
#include <avr/io.h>
#include <avr/delay.h>

#include "Ringspeicher.h"
#include "minios.h"
#include "SPIHander.h"
#include "pwm.h"
#include "adc.h"

volatile Telegramm; 

/* To do *

- Make Sure Interrupts fire. 
- Make Sure SPI Works
- Make Sures Pins can be set and reset. 
- Make Sure PWM works. the point of confusion is that both port pins  use different OCCRA and OCCRB. Should it be that way? 

*/


ISR(SPI_STC_vect)
    {
    	Telegramm = SPDR;  // ISR for SPI 

    }


ISR(TIMER0_COMPB_vect)
    {
    	Adcflag = true; /*https://www.avrfreaks.net/forum/solved-adc-autotrigger-timer1a-ctc-interrupt-problem-atmega328p */

    }

int main()
{	
	DDRC |= (1<<DDC0);
    while (1) 
    {
	PORTC |= (1<<PORTC0);
	_delay_ms(1);
	PORTC &= ~ (1<<PORTC0);
	_delay_ms(1);
    }


    SPI_SlaveInit(); 

   while(1)
   {

   	// Get the whole Telegramm 
   	// check if it is okay
   	// select the function byte // athawa Ringspeicher laii nai badauxu vanda kheri pani paiiyo. 
   	// select the data byte 
   	// give function the parameter and call it 
   	// if function returns something save it in a ringspiecher  if not void it 
   	// if ADC_Flag = true
   	// get the value from ADC. Read the Pins
   	// 
   	Ringspeicher_Put_Override(Telegramm[Functionbyte]); 


   	fptr funktionausdemtelegramm = Telegramm_Function_Assigner(Ringspeicher_Get_Value()); // Nimmt der Letzte Wert vom Ringspeicher
   	functionausdemtelegramm(char Telegramm[]); 
   	OS_Befehlausfuehren(&funktionausdemtelegramm, 1, BLOCKED); 

	// isp c file ma rakhxu chaiyo vaniTo recieve data from SPI https://raspberry-projects.com/pi/programming-in-c/spi/using-the-spi-interface









   }
    

	//OS_Befehlgenerieren(&Funktion1, 2,  BLOCKED);   //OS_Rueckmeldung OS_Befehlgenerieren(fncPtr Befehl, uint8_t periodendauer, OS_State dstate )
	//OS_Befehlgenerieren(&Funktion2, 3, BLOCKED); 


	/*Die Funktionen oben generieren die Befehle und speicheren diese Befehle in 
	  static OS_struct befehl_array[OS_MAX_BEFEHLE_NUM] . Die folgende Funktion führt dann alle 
	  Befehle die in dieser Array gespeichert sind. */

	//OS_Befehlausfuehren();                     // Führt die Befehle die generiert worden sind aus





}

/*
The basic idea is as follows:
	
	First the Data Comes in SPI.
	It triggers an Interrupt. 
	The Data is the Saved in Ringspeicher. 
	SPI Interrupt can happen anytime maybe.
	SPI Handler which returns pointers to the function that has to be executed is called. 

	{
		Befehlliste is updated with that function . 

	}
	Betreibsystem(Befehlausführen) is called. ()
	It also has time parameter. Which means it will call the function periodically
	int that time. 

	

	Abah K k garna baki xa ta:

		Voli First ma SPI interrupt hunxa ki naii test garnu parxa
		Tesko lagi Raspberry Lai SPi master banaunu parxa
		tespaxi tesbata aako data laii halnu parxa
		

	




	*/