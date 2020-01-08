/*

Interrupt Driven ADC 
Tutorial from Site

http://www.glennsweeney.com/tutorials/interrupt-driven-analog-conversion-with-an-atmega328p */






#include<avr/interrupts.h>
#include<avr/io.h>



/*



The statement "the value can be changed by means outside of this code" basically means 
that another program or hardware can update that variable. 

*/


volatile  int readFlag; // High when a value is ready to read

volatile int analogVal; // Value to store analog result 

void setup(void){      // Initialization



/*

ADMUX  (ADC Multiplexer Selection Register) -> This register is used to select reference voltage souce
, how the result should be stored (either left adjusted or right adjusted), analog port channel to be
used for conversion. 

Left Adjusted and Right Adjusted  Meaning

The  width of register that holds to result be 16 bits. 
A right-adjusted result  means that the bits [(N-1):0] (where N is the numbers of bits of percision) of the
register contain the ADC value and most-significant bits of the register are set to zero

A left-adjusted result means that bits [15. (16-N)] of the register hold the result and the bits [15-N :0 are
set to zero .
For example if your actual conversion result is 0x123, it would read as 0x0123 if the register was right adjusted 
and it would read as 0x1230 if it was left adjusted

Using left-justified result: you can take just the most significant byte of the register, giving 8 bits precision. 
This can be useful if you dont need extra precision 






*/

	// ADMUX	: ADC Multiplexer Selection Register
	// Bit 7	: REFS1	 = 0	: Reference Selection Bits:   00:: Pin AREF  , 01 :: Pin AVcc  , 10 :: --   11:: 1,1V intern
	// Bit 6	: REFS0	 = 1
	// Bit 5	: ADLAR  = 0	: ADC Left Adjust Result  :   geeignet, wenn nur 8 Bits gelesen werden sollen
	// Bit 4	: --
	// Bit 3	: MUX3   = 0    : Kanalnummer
	// Bit 2	: MUX2   = 0
	// Bit 1	: MUX1   = 0
	// Bit 0	: MUX0	 = 0


	ADMUX &= 0xDF;   //clear ADLAR in ADMUX . 3 MSB in ADMUX is for ADLAR  DF = 0b1101 1111; 

	ADMUX |= 0x40;   // 0b 0100 0000  change reference voltage to souce 6th Bit of ADMux. ADMUX register sehen 

	ADMUX |= 0x08;    ///0b 0000 1000


	/*
		

	// ADCSRA	: ADC Control Status Register A 
	// Bit 7	: ADEN = 1		: ADC Enable  1:: enabled , 0:: disabled
	// Bit 6	: ADSC = 0      : ADC Singel Conversion  1:: Startet SIngel Conversion, Bit wird danach rückgesetzt - Verwendung Statusabfrage
	// Bit 5	: ADATE = 0     : AUto Trigger Enable 1:: Wandlung bei jeder positiven Flanke der Triggerquelle
	// Bit 4    : ADIF = 0		: ADC Interrupt Flag  zeigt Wandlungsende an, verwenden  bei ISR Applikation , wird in ISR gelöscht.
	// Bit 3	: ADIE = 0		: ADC Interrupt Enable  1:: Interrupt freigegeben.
	// Bit 2	: ADPS2 = 1		: ADC Prescaler Bits : Takt SYsclk/Prescaler muss für ADC muss 50kHz... 200kHz betragen.  Wandlungszeit 13 Takte
	// Bit 1	: ADPS1 = 1		:                      000::2 , 001::2 , 010:: 4 , 011:: 8 , 100:: 16 , 101:: 32 , 110: 64 , 111:: 128
	// Bit 0	: ADPS0 = 1		:  16MHz/128 = 125khz --> Wandlungszeit : 13/125kHz= 104 us


	*/  

	ADCSRA |=0x80;   // 0b 1000 0000 0x87 = 1000 0111 to set the prescaler change bits 2:0. That is what barten did in his adc

	ADCSRA |=0x20;  // Auto Triggering enabled Binary equivalent 0b 0010 0000


	// ADCSRB	: ADC Control Status Register B
	// Bit 7	:--  //reserviert
	// Bit 6	: ACME = 0	: Analog Comperator Multiplexer Enable
	// Bit 5	: -- // reserviert
	// Bit 4	: -- // reserviert
	// Bit 3	: -- // reserviert
	// Bit 2:	: ADTS2	=0	:ADC Auto Trigger Source Select Bits : 000:: free running , 001:: Analog Comperator , 010:: External IR0 , 011::T0 Compare Match
	// Bit 1:	: ADTS1	=0	                                   100::T0 Overflow , 101:: T1 Compare Match , 110:: T1 Overflow , 111:T1 Capture Event
	// Bit 0:	: ADTS0	=0	

	// ADCSB ist nach Reset = 0x00, keine Zuweisung notwendig	



	ADCSRB &= 0xF8; // binary Equivalent 0b 1111 1000  . Here the last 3 bits are cleared- When last bits are cleared kontinuerlicher Betreib

	ADCSRA |= 0x07; // Prescaler to 128

	ADCSRA |= 0x08; //0b0000 1000 Enable ADC Interrupt. Without this internal interrupt will not be cleared. 



	sei(); // Enable global interrupts ATMEGa . It is important if you want to use Interrupts at all

/*
his raises the next point;  by default, interrupts are themselves not interruptable. When an interrupt fires, the AVR CPU will automatically 
disable the Global Interrupt Enable bit, to prevent the ISR from being itself interrupted. This is to prevent stack overflows from too ma
ny interrupts occurring at once and to prevent the ISRs from running too long, as most uses of interrupts are to hav
e minimal latency when processing an event. It's perfectly possible to set the Global Interrupt Enablebit again as part of the ISR so that nested interr
upts can occur, but this is highly not recommended as it is dangerous.  



*/

/*
Data shared between the ISR and your main program must be both volatile and global in scopein the C language. Without the 
volatile keyword, the compiler may optimize out accesses to a variable you update in an ISR, as the C language 
itself has no concept of different execution threads. Take the following example:  


*/	

	readFlag = 0;  // kick off the first ADC

	ADCSRA |= 0x40; // binary equivalent 0b 0100 0000




}


uint8_t StartSingleADC(uint8_t Channel)
{

	if(Channel < 8  )
	{
		ADMUX &= 0xF0;  // Kanalbitsnullen die letzte 4 bits sind für Kanal zuständig
		ADMUX |= (0x07 & Channel)  // 0b 0000 0111 &  channel werte. Kanal setzen

		ADCSRA |= 1 << ADSC;    // Wandlung starten 

        /*
		
		Above Statement calculates to  ADCSRA = ADSCRA | (1 << ADSC)
												= ADSCRA |(ADSCVALUE and 0)		

		ADCSRA 
		ADCSR = ADCSR    (1 << ADSC ) 5 = 101 10 = 1010 

        */

		return 1; 



	}
	else return 0; 
}



/*

ADCL and ADCH Data  Register   ADCL = ADC Low Bye. ADC High Byte. 

The result of ADC Conversion is stored here. Since ADC has resolution of 10 bits, it requires 10 bits
to store the result. 
One Single Rgister is not sufficient. 





*/




uint16_t GetADCVal()
{

	uint16_t volatile Wert; 

	DISABLE_IRs();  //cei/(
	Wert = (uint16_t ) ADCL;  //  values saved at low bits + values saved at high bits
	Wert += (uint16_t)(ADCH << 8);   /* Because this here is 16 bit integer it makes sense to shift by 8 bits*/
	Wert = Wert+1; 
	ENABLE_IRs(); 

	return Wert; 





}