/*
 * CFile2.c
 *
 * Created: 12.04.2016 08:55:12
 *  Author: Michael
 */ 

// Die Includes der Hardwareplattform
#include <avr/io.h>
			   
/*--------------+-----------------------------------------------------------+
| Name         | InitADC                                                   |
+--------------+-----------------------------------------------------------+
| Beschreibung | Setzt:   Singel Conversion Mode, Tw= 104us,               |
|              |          Standard Ch=0, Spg.-Referenz = Pin AVcc          |
+--------------+-----------------------------------------------------------+
|Autor         |  Michael Barten - HWR-Berlin                              |
+--------------+-----------------------------------------------------------+
| Notes        | Version 1.0 -- 11.04.2016                                 |
+--------------+-----------------------------------------------------------*/			   
void InitADC()
{
	// ADMUX	: ADC Multiplexer Selection Register
	// Bit 7	: REFS1	 = 0	: Reference Selection Bits:   00:: Pin AREF  , 01 :: Pin AVcc  , 10 :: --   11:: 1,1V intern
	// Bit 6	: REFS0	 = 1
	// Bit 5	: ADLAR  = 0	: ADC Left Adjust Result  :   geeignet, wenn nur 8 Bits gelesen werden sollen
	// Bit 4	: --
	// Bit 3	: MUX3   = 0    : Kanalnummer
	// Bit 2	: MUX2   = 0
	// Bit 1	: MUX1   = 0
	// Bit 0	: MUX0	 = 0

			
    ADMUX = 0x40;		// AVcc und Kanal 0

	// ADCSRA	: ADC Control Status Register A
	// Bit 7	: ADEN = 1		: ADC Enable  1:: enabled , 0:: disabled
	// Bit 6	: ADSC = 0      : ADC Singel Conversion  1:: Startet SIngel Conversion, Bit wird danach rückgesetzt - Verwendung Statusabfrage
	// Bit 5	: ADATE = 0     : AUto Trigger Enable 1:: Wandlung bei jeder positiven Flanke der Triggerquelle
	// Bit 4    : ADIF = 0		: ADC Interrupt Flag  zeigt Wandlungsende an, verwenden  bei ISR Applikation , wird in ISR gelöscht.
	// Bit 3	: ADIE = 0		: ADC Interrupt Enable  1:: Interrupt freigegeben.
	// Bit 2	: ADPS2 = 1		: ADC Prescaler Bits : Takt SYsclk/Prescaler muss für ADC muss 50kHz... 200kHz betragen.  Wandlungszeit 13 Takte
	// Bit 1	: ADPS1 = 1		:                      000::2 , 001::2 , 010:: 4 , 011:: 8 , 100:: 16 , 101:: 32 , 110: 64 , 111:: 128
	// Bit 0	: ADPS0 = 1		:  16MHz/128 = 125khz --> Wandlungszeit : 13/125kHz= 104 us

	ADCSRA = 0x87;		// ADC Enabled, Prescaler = 128

	// ADCSRB	: ADC Control Status Register B
	// Bit 7	:--
	// Bit 6	: ACME = 0	: Analog Comperator Multiplexer Enable
	// Bit 5	: --
	// Bit 4	: --
	// Bit 3	: --
	// Bit 2:	: ADTS2	=0	:ADC Auto Trigger Source Select Bits : 000:: free running , 001:: Analog Comperator , 010:: External IR0 , 011::T0 Compare Match
	// Bit 1:	: ADTS1	=0	:                                      100::T0 Overflow , 101:: T1 Compare Match , 110:: T1 Overflow , 111:T1 Capture Event
	// Bit 0:	: ADTS0	=0	:

	// ADCSB ist nach Reset = 0x00, keine Zuweisung notwendig	
}
//----------------------------------------------------------------------------



/*--------------+-----------------------------------------------------------+
| Name         | StartSingleADC                                            |
+--------------+-----------------------------------------------------------+
| Beschreibung | Setz den Kanal und starte Single Conversion               |
|              | Parameter : Chanel : Kanalnummer 0..7                     |
+--------------+-----------------------------------------------------------+
|Autor         |  Michael Barten - HWR-Berlin                              |
+--------------+-----------------------------------------------------------+
| Notes        | Version 1.0 -- 11.04.2016                                 |
+--------------+-----------------------------------------------------------*/
uint8_t StartSingleADC(uint8_t Chanel)
{
	if (Chanel<8)
	{
		ADCSRB|= (0x07 & Chanel);	// Kanal setzen
		ADCSRA|= 1<<ADSC;			// Wandlung starten	
		return  1;	
	}
	else return  0; 
	
}
//----------------------------------------------------------------------------



/*--------------+-----------------------------------------------------------+
| Name         | GetADC_Val                                                |
+--------------+-----------------------------------------------------------+
| Beschreibung | Gibt den 10Bit ADC-Wert als uint16_t zurück.              |
|              | Parameter : Chanel : Kanalnummer 0..7                     |
+--------------+-----------------------------------------------------------+
|Autor         |  Michael Barten - HWR-Berlin                              |
+--------------+-----------------------------------------------------------+
| Notes        | Version 1.0 -- 11.04.2016                                 |
+--------------+-----------------------------------------------------------*/
uint16_t GetADC_Val()
{
	uint16_t  Wert;
	//Zuerst L-Byte lesen, um Datenkonsistenz zu gewährleisten
	Wert= (uint16_t)ADCL;
	Wert += (uint16_t)(ADCH<<8);
	Wert = Wert+1;
	return Wert;
}
//----------------------------------------------------------------------------




/*--------------+-----------------------------------------------------------+
| Name         | ChkConversionStatus                                       |
+--------------+-----------------------------------------------------------+
| Beschreibung | Prüft ob einmalig Wandlung beendet ist.                   |
|              | RRücgabewert : 1:: Wanlung beendet, o:: Wandlung läuft    |
+--------------+-----------------------------------------------------------+
|Autor         |  Michael Barten - HWR-Berlin                              |
+--------------+-----------------------------------------------------------+
| Notes        | Version 1.0 -- 11.04.2016                                 |
+--------------+-----------------------------------------------------------*/
uint8_t ChkConversionSatus(void)
{
	if ((ADCSRA & (1<< ADSC) )== 0)
		 return 1; // Wandlung beendet
	else return 0;
}
//----------------------------------------------------------------------------
