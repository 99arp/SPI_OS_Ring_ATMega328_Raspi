// Die Includes der Hardwareplatform
#include <avr/io.h>
#include <avr/interrupt.h>
# include<string.h>
#include "SPI.h"

#ifndef SYSCLK
#warning "F_CPU war noch nicht definiert, wird nun nachgeholt mit 2000000"
#define SYSCLK 20000000UL  // CPU Taktfrequenz
#endif

#define SPI_RX_BUF_SIZE  16
#define Set_nSS()    PORTB |=1<< PORTB2		// Slave nicht selektiert
#define Clear_nSS()  PORTB |=~(1<< PORTB2)	// Slave selektiert


static volatile uint8_t SPI_Rxbuf[SPI_RX_BUF_SIZE];	// Empfangsringspeicher
static volatile uint8_t SPI_RxWidx;						// Leseindex des Empfangsringspeichers 
static volatile uint8_t SPI_RxWidx;						// Schreibindex des Empfangsringspeichers 
static volatile uint8_t SPI_RxCount;					// Anzahl der ungelesenen Bytes im Empfangsringspeicher 
static volatile uint8_t SPI_RX_OVF;						// 1: Datenverlust Byte(s) überschrieben
static volatile uint8_t *SendStringPtr = NULL;			// Zeiger auf zu sendenden String;
static volatile uint8_t SPI_TX_Done = 0;

char IniSPI(unsigned int Baudrate)
{
	// Die SPI ist Master, MSB first, Datenbit mit pos. Flanke anlegen und mit neg. Flake übernehmen.
	// Meldung Byteübertrgung beendet per Interrupt.
	//   SCK    : PB5
	//   MISO	: PB4
	//   MOSI	: PB3
	//   nSS	: PB2
	//   
	// Parameter 1 : Baudrate 
	// Rückgabewert: 0 : Initialisierung ok  , -1: Baudratenfehler 

	char			RetValue = 0;

	// SPI arbeitet als Master, Data Direktion Register für SPI Pins setzen
	DDRB |= (1 << PB3) | (1 << PB5); // MOSI und CLK sind Ausgänge

	//SPI Control Register :: SPCR
	// 
	// Bit 7   0  SPIE   SPI Interrupt Enable(1: enabled)			:: Interrupt nach Datenübertragung zunächst ausgeschaltet	     
	// Bit 6   1  SPE    SPI Enable (1: enabled						:: enabled -  SPI aktiv!
	// Bit 5   0  DORD   Data Order (0: MSB first, 1: LSB first)	:: MSB first	
	// Bit 4   1  MSTR   Master/Slave Select (1: Master)            :: Master 
	// Bit 3   0  CPOL   Clock Polarity								:: L ist inaktiver Level 
	// Bit 2   1  CPHA   Clock Phase ( 1: sample at trailing edge)  :: Abtastung bei fallender Flanke, d.h. bei trailing edge
	// Bit 1   0  SPR1   Clock Rate Select Bits
	// Bit 0   0  SPR0   SYSCLK / 4..128							::  nach Baudratenvorgabe berechnen

	SPCR = 0x57;

	VorTeiler = (unsigned int)(SYSCLK / Baudrate);
	if (!(Vorteiler < 2) && !(Vorteiler > 128))
	{
      switch (VorTeiler)
	  {
	     case 2:    SPCR |= 0x00;	// SPR1 = 0,SPR0=0
					SPSR |= 0x01;   // Double Speed Bit im SPI Status Register SPI2= 1
				break;
		 case 4:    SPCR |= 0x00;	// SPR1 = 0,SPR0=0
					SPSR ^= 0x01;   // Double Speed Bit im SPI Status Register SPI2= 0
				break;
		  case 8:   SPCR |= 0x01;   // SPR1 = 0,SPR0=1
					SPSR |= 0x01;   // Double Speed Bit im SPI Status Register SPI2= 1
				break;
		  case 16:  SPCR |= 0x01;   // SPR1 = 0,SPR0=1
					SPSR ^= 0x01;	// Double Speed Bit im SPI Status Register SPI2= 0
				break;
		  case 32:  SPCR |= 0x02;   // SPR1 = 1,SPR0=0 
					SPSR |= 0x01;   // Double Speed Bit im SPI Status Register SPI2= 1
				break;
		  case 64:  SPCR |= 0x02;   // SPR1 = 1,SPR0=0 
					SPSR ^= 0x01;   // Double Speed Bit im SPI Status Register SPI2= 0
				break;
		  case 128: SPCR |= 0x03;   // SPR1 = 1,SPR0=1 
					SPSR ^= 0x01;   // Double Speed Bit im SPI Status Register SPI2= 0
				break
			default: // Baudrate nicht realisierbar
					RetValue = -1;
	   }

	   SPI_RxWidx  = 0;
	   SPI_RxWidx  = 0;
	   SPI_RxCount = 0;
	   SPI_RX_OVF  = 0;

   }
   else RetValue = -1;

   return RetValue;
}



uint8_t SPI_RxAvailable(void)
// Prüft, ob noch ungelesene Bytes im Ringspeichervorhanden sind.
// Rückgabewert:  :0 keine Bytes vorhanden , 1 : Bytes vorhanden
{
	if SPI_RxCount == 0)
		 return 0;
	else return 1;
}


uint8_t SPI_Getc(void)
//  Holt ein Zeichen aus dem Empfangs-Ringspeicher
{
	uint8_t r;

	r = SPI_Rxbuf[SPI_RxRidx];
	SPI_RxRidx++;
	SPI_RxRidx &= (SPI_RX_BUF_SIZE - 1); // Rücksetzen des Leseindexes, wenn obere Ringspeichergrenze erreicht
	SPI_RxCount--;
	return(r);
}




void StartSPI_Transmission(uint8_t *SendPtr)
// Datenübertragung starten : Zeiger aud Sendestring übernehmen, Tx-Ready-Semaphor rückseten, Interruppt einschalten,
//   wenn möglich erstes Byte senden
{
	SPI_TX_Done = 0;
	SendStringPtr = SendPtr;
	if (SendStringPtr != NULL && (*SendStringPtr != '\0'))
	{
		SPDR = *(SendStringPtr++);
		// SPI Data Register empty Interuppt einschalten
		SPCR |= 1 << SPIE;
	}
	

}



uint8_t GetTxStatus(void)
// Abfrage, ob Sting vollständig gesendet wurde.
// Rückgabewert : 1: gesendet 0: pending
{
	if (SPI_TX_Done == 1)
		 return  1;
	else return  0;
}




ISR(SPI_STC_vect)
{
	// Empfangenes Byte in den Ringspeicher kopieren
	SPI_Rxbuf[SPI_RxWidx++] = SPDR;
	SPI_RxWidx &= (SPI_RX_BUF_SIZE - 1); // Rücksetzen des Leseindexes, wenn obere Ringspeichergrenze erreicht
	SPI_RxCount++
	// Byteübertragung abgeschlossen
	if (SendStringPtr != NULL && (*SendStringPtr != '\0'))
		   SPDR = *(SendStringPtr++);
	else {
		   SPI_TX_Done = 1;
		   // SPI TX Data Register empty Interuppt ausschalten
		   SPCR & = ~(1 << SPIE);
	     }
}


