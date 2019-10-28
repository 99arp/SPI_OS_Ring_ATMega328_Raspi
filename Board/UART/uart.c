// Die Includes der Hardwareplatform
#include <avr/io.h>
#include <avr/interrupt.h>
# include<string.h>
#include "uart.h"

#ifndef SYSCLK
#warning "F_CPU war noch nicht definiert, wird nun nachgeholt mit 2000000"
#define SYSCLK 20000000UL  // CPU Taktfrequenz
#endif


#define UART_RX_BUF_SIZE    16

static volatile uint8_t UartRxbuf[UART_RX_BUF_SIZE];	// Empfangsringspeicher
static volatile uint8_t UartRxWidx;						// Leseindex des Empfangsringspeichers 
static volatile uint8_t UartRxWidx;						// Schreibindex des Empfangsringspeichers 
static volatile uint8_t UartRxCount;					// Anzahl der ungelesenen Bytes im Empfangsringspeicher 
static volatile uint8_t UartRX_OVF;						// 1: Datenverlust Byte(s) überschrieben
static volatile uint8_t *SendStringPtr = NULL;			// Zeiger auf zu sendenden String;
static volatile uint8_t UartTX_Done = 0;

char IniUART(unsigned int Baudrate)
{
	// Die UART wird im normal Mode betrieben.
	// RX Interrupt und TX Daten Register Empty Interrupt werden genutzt.
	//
	// TxD	: PD1
	// RxD	: PD0
	//
	// Parameter 1 : Baudrate 
	// Rückgabewert: 0 : Initialisierung ok  , -1: Baudratenfehler 

	unsigned int	BaudReal;
	unsigned int	BaudErrorInThousandth;
	char			RetValue = 0;

	// USART Baudratenregister UBRR0 setzen
	UBRR0 = (unsigned int)((SYSCLK/Baudrate/16)-1);		// Berechnung der Baudrate mit Rundungsfehler

	BaudReal = SYSCLK / (16 * UBRR0 + 1);				// tatsächliche Baudrate
	BaudErrorInThousandth = BaudReal * 1000 / Baudrate; // Baudratenfehler in Promille


	if (!(BaudErrorInThousandth<990) && !(BaudErrorInThousandth>1010))
	{
		// Asynchron Mode Frame Format : 8 Data Bits, 2 Stop Bits , no Parity, Interrupts gesperrt

		//  UART Control Status Register 0 C  ::UCSR0C
		//       Asynchron         no parity         2 Stop Bits        8 Data Bits         set 0 isn async. mode
		//    UMSEL01  UMSEL00   UPM01  UPM00           USBS0         UCSZ01   UCSZ00           UCPOL0  
		//       0        0        0      0               1              1       1                0             
		UCSR0C = 0x0E;

		//  UART Control Status Register 1 C  ::UCSR0B
		//     Rx IE      TX IE    Data Reg Empty IE   act. Rx Pin     act. TX Pin     8 Data Bits    9th Bitreceived    9th. Bit to send
		//    RXCIE0     TXCIE0         UDRIE0             RXEN0           TXEN0        UCSZ02        RXB80                TX80
		//       0        0               0                 1               1              1            x                    x             
		UCSR0B = 0x1B;

		UartRxWidx  = 0;
		UartRxWidx  = 0;
		UartRxCount = 0;
		UartRX_OVF  = 0;

		// Den RX receive Interrupt freigeben.
		UCSR0B |= 1 << RXCIE0;

	}
	else RetValue = -1;

	return RetValue
}



ISR(USART_RX_vect)
{
	// Ein Zeichen wurde von der UART empfangen -> in den Ringspeicher schreiben 

	UartRxbuf[UartRxWidx] = UDR0;
	UartRxWidx++;
	UartRxWidx &= (UART_RX_BUF_SIZE - 1);  // Rücksetzen des Schreibindexes, wenn obere Ringspeichergrenze erreicht
	UartRxCount++;

	If(UartRxCount > (UART_RX_BUF_SIZE-1))
	{
		UartRX_OVF = 1;
	}
}

uint8_t UartRxAvailable(void)
// Prüft, ob noch ungelesene Bytes im Ringspeichervorhanden sind.
// Rückgabewert:  :0 keine Bytes vorhanden , 1 : Bytes vorhanden
{
	if UartRxCount == 0)
		 return 0;
	else return 1;
}


uint8_t UartGetc(void)
//  Holt ein Zeichen aus dem EmpfangsRingspeicher
{
	uint8_t r;

	r = UartRxbuf[UartRxRidx];
	UartRxRidx++;
	UartRxRidx &= (UART_RX_BUF_SIZE - 1);    // Rücksetzen des Leseindexes, wenn obere Ringspeichergrenze erreicht
	UartRxCount--;
	return(r);
}




void StartUART_Transmission(uint8_t *SendPtr)
// Datenübertragung starten : Zeiger aud Sendestring übernehmen, Tx-Ready-Semaphor rückseten, Interruppt einschalten
{
	UartTX_Done = 0;
	SendStringPtr = SendPtr;
	// UART Data Register empty Interuppt einschalten
	UCSR0B |= 1 << UDRIE0;

}



uint8_t GetTxStatus(void)
// Abfrage, ob Sting vollständig gesendet wurde.
// Rückgabewert : 1: gesendet 0: pending
{
	if (UartTX_Done == 1)
		 return  1;
	else return  0;
}



ISR(USART_UDRE_vect)
{
	// Das Senderegister der UART ist leer
	if (SendStringPtr != NULL && (*SendStringPtr != '\0'))
	      UDR = *(SendStringPtr++);
	else {
			UartTX_Done = 1;
		   // UART Data Register empty Interuppt ausschalten
		   UCSR0B & = ~(1 << UDRIE0);
	     }
}


