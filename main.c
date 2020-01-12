
#define F_CPU 16000000UL
#include<stdio.h>
#include<stddef.h>
#include <avr/io.h>
#include <avr/delay.h>

#include "Ringspeicher.h"
#include "minios.h"


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


	//OS_Befehlgenerieren(&Funktion1, 2,  BLOCKED);   //OS_Rueckmeldung OS_Befehlgenerieren(fncPtr Befehl, uint8_t periodendauer, OS_State dstate )
	//OS_Befehlgenerieren(&Funktion2, 3, BLOCKED); 


	/*Die Funktionen oben generieren die Befehle und speicheren diese Befehle in 
	  static OS_struct befehl_array[OS_MAX_BEFEHLE_NUM] . Die folgende Funktion f�hrt dann alle 
	  Befehle die in dieser Array gespeichert sind. */

	//OS_Befehlausfuehren();                     // F�hrt die Befehle die generiert worden sind aus





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
	Betreibsystem(Befehlausf�hren) is called. ()
	It also has time parameter. Which means it will call the function periodically
	int that time. 

	

	Abah K k garna baki xa ta:

		Voli First ma SPI interrupt hunxa ki naii test garnu parxa
		Tesko lagi Raspberry Lai SPi master banaunu parxa
		tespaxi tesbata aako data laii halnu parxa
		

	




	*/