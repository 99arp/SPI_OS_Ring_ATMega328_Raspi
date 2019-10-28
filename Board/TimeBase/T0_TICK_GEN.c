/*
 * T0_TICK_GEN.c
 *
 * Created: 11.04.2016 12:12:00
 *  Author: Michael
 */ 
/*
 * tick.c
 *
 * Created: 22.01.16 10:52:49
 *  Author: danielstraube
 */ 
//----------------------------------------------------------------------------


#include <avr/io.h>
#include <avr/interrupt.h>
#include "T0_TICK_GEN.h"
#include "BoardDependencies.h"


// 4 Software-Timer : gesetzt mit Anzahl der Ticks bevor Prozessausführung
static uint16_t T0_Ctrl1 = 0;
static uint16_t T0_Ctrl2 = 0;
static uint16_t T0_Ctrl3 = 0;
static uint16_t T0_Ctrl4 = 0;

// Reload-Werte für die SW-Timer
static uint16_t T0_Rl1 = 0;
static uint16_t T0_Rl2 = 0;
static uint16_t T0_Rl3 = 0;
static uint16_t T0_Rl4 = 0;		

// 4 Zeiger auf Funktionen, die von den Soft-Timer aufgerufen werden
static void (*T0_Ptr1) (void);
static void (*T0_Ptr2) (void);
static void (*T0_Ptr3) (void);
static void (*T0_Ptr4) (void);


 static uint8_t RunControl;				 // Statusbit:  1:: Soft-Timer läuft
 static uint8_t FktCount;				 // Anzahl der aktiven SW.Timer
 static uint8_t TimerVal ;                   // Relaod-Wert





 
/**
 * @brief timer0 isr, gets called every 1msec
 * @par none
 */
ISR(TIMER0_OVF_vect)
{
	 /* stop timer */
	STOP_T0();
	TIMER_REGISTER =TimerVal;
	/* start timer */
    START_T0();	
	if ( T0_Ctrl1 != 0 )         /* check softtimer 1 */
	{
		if ( --T0_Ctrl1 == 0 )
		{
			T0_Ctrl1 = T0_Rl1;  // Reload SW-Timer
			if ( T0_Ptr1 != 0 )
			T0_Ptr1();  /* if counter becomes zero execute user- */
			}                   /* defined routine */
		}

		if ( T0_Ctrl2 != 0 )         /* check softtimer 2 */
		{
			if ( --T0_Ctrl2 == 0 )
			{
				T0_Ctrl2 = T0_Rl2;  // Reload SW-Timer
				if ( T0_Ptr2 != 0 )
				T0_Ptr2();
			}
		}

		if ( T0_Ctrl3 != 0 )         /* check softtimer 3 */
		{
			if ( --T0_Ctrl3 == 0 )
			{
				T0_Ctrl3 = T0_Rl3;  // Reload SW-Timer
				if ( T0_Ptr3 != 0 )
				T0_Ptr3();
			}
		}

		if ( T0_Ctrl4 != 0 )         /* check softtimer 4 */
		{
			if ( --T0_Ctrl4 == 0 )
			{
				T0_Ctrl4 = T0_Rl4;  // Reload SW-Timer
				if ( T0_Ptr4 != 0 )
				T0_Ptr4();
			}
		}
		// Fehlerbehandlung : Falls ein Funktionsaufruf  den Zähler gestoppt hatte gain - Neu Starten 
		START_T0();
}
//----------------------------------------------------------------------------



/*--------------+-----------------------------------------------------------+
 | Name         | Tick_Init                                                 |
 +--------------+-----------------------------------------------------------+
 | Beschreibung | T0-Register Intialisierung und ISR-Freigabe               |
 +--------------+-----------------------------------------------------------+
 |Autor         |  Michael Barten - HWR-Berlin                              |
 +--------------+-----------------------------------------------------------+
 | Notes        | Version 1.0 -- 11.04.2016                                 |
 +--------------+-----------------------------------------------------------*/
void TickInit(void)
{
	// Hier die Steuerregister des Timers initialisieren:
	
	// TCCR0A	: Timer Counter Control Register A (T0)		
	//    Bits 7-2  : Festlegung Outputpins für T0 -> Default belassen, d.h. Bits = 0 (Port-Pins frei)
	//    Bit 1		: Wave Generation Mode Bit 1	: 0													
	//    Bit 0		: Wave Generation Mode Bit 0    : 0		: 00 -> Aufwährtszähler mit Timer Overflow bei FFh Interrupt freigegeben
	//   TCCR0A ist nach dem Reset auf 0x00 gesetzt, also keine Zuweisung notwendig


	// TCCR0B  : Timer Counter Control Register B (T0)	
	//    Bits 7-3	: Weitere Bits zur  EInstellung PWM-Mode --> Default belassen, d.h. Bits = 0 	
	//	  Bit 2		: 1
	//    Bit 1		: 0
	//    Bit 0     : 1   :: CPU clock prescaler = 0 --> Zähler gestoppt
	//   TCCR0B ist nach dem Reset auf 0x00 gesetzt, also keine Zuweisung notwendig
	
	
	// TIMSK0	: Timer Counter Interrupt Mask Register
	//    Bits 7-3	: not used --> auf 0 setzen
	//    Bit 2:	OCIE0B	: Interrupt Enable bei Compare Match B  --> 0
	//    Bit 1:	OCIE0A	: Interrupt Enable bei Compare Match A  --> 0
	//    Bit 0:	TOIE0	: Interrupt Enable Overflow --> 0= Disable
	// TIMSK0 ist nach Reset auf 0x00 gesetzt, also keine Zuweisung notwendig
	
	// Hier die Zeitbasis einstellen
	TimerVal =T0_RELOAD_10MSEC;
	
	FktCount = 0;		// Noch keine SW-Timer aktiviert
	RunControl = STOP;   // 

}
//----------------------------------------------------------------------------


/*--------------+-----------------------------------------------------------+
 | Name         | TerminateSwTimer                                          |
 +--------------+-----------------------------------------------------------+
 | Beschreibung | Stopt Soft-Timer (sperrt T0_ISR) und setzt RunTimer = 0   |
 +--------------+-----------------------------------------------------------+
 |Autor         |  Michael Barten - HWR-Berlin                              |
 +--------------+-----------------------------------------------------------+
 | Notes        | Version 1.0 -- 11.04.2016                                 |
 +--------------+-----------------------------------------------------------*/
void TerminateSwTimer(void)
{
    // T0-Overflow Interrupt sperren
	DISABLE_TIMER0_OVERFLOW();
	
	// T0 anhalten
	STOP_T0();
}
//----------------------------------------------------------------------------




/*--------------+-----------------------------------------------------------+
 | Name         | StartTimer                                                |
 +--------------+-----------------------------------------------------------+
 | Beschreibung |  Startet winen  Soft-Timer und den zugehörigen Prozesse   |
 |              | Adr. der Userfunktion die ausgelöst werden soll.          |
 +--------------+-----------------------------------------------------------+
 | Parameter    | Soft-Timer-Id, Anzahl der Ticks vor Aufruf,               |
 |              | Adresse der Userfunktion die ausgeführt werden soll.      |
  +--------------+-----------------------------------------------------------+
 |Autor         |  Michael Barten - HWR-Berlin                              |
 +--------------+-----------------------------------------------------------+
 | Notes        | Version 1.0 -- 11.04.2016                                 |
 +--------------+-----------------------------------------------------------*/
 uint8_t StartTimer (uint8_t soft_id, uint16_t ticks, void (*funcptr) (void))
{
	uint8_t error = NO_ERROR;
	
	DISABLE_TIMER0_OVERFLOW();
	switch (soft_id)
	{
        case STIMER1:
			T0_Ctrl1 = ticks; 
			T0_Rl1 = ticks;
			T0_Ptr1 = funcptr;
            break;

        case STIMER2:
			T0_Ctrl2 = ticks;
			T0_Rl2 = ticks;
			T0_Ptr2 = funcptr; 
 			break;

        case STIMER3:
 	        T0_Ctrl3 = ticks;
			T0_Rl3 = ticks;
	        T0_Ptr3 = funcptr;
			break;

        case STIMER4:
			T0_Ctrl4 = ticks;
			T0_Rl4 = ticks;
			T0_Ptr4 = funcptr;
			break;

 		default	: error = ID_ERROR;
    } /* switch */
	ENABLE_TIMER0_OVERFLOW();
	if ( RunControl == STOP  && error == NO_ERROR) /* restart timer */
	{
		 TIMER_REGISTER = TimerVal;
		 START_T0();
		 RunControl = START;
	}
	return error;
} /* StartTimer */
//----------------------------------------------------------------------------




/*--------------+-----------------------------------------------------------+
 | Name         | KillTimer                                                 |
 +--------------+-----------------------------------------------------------+
 | Beschreibung | Beendet einenSW-Timer Prozess                             |
 +--------------+-----------------------------------------------------------+
 | Parameter    | Soft-Timer-Id                                             |
  +--------------+-----------------------------------------------------------+
 |Autor         |  Michael Barten - HWR-Berlin                              |
 +--------------+-----------------------------------------------------------+
 | Notes        | Version 1.0 -- 11.04.2016                                 |
 +--------------+-----------------------------------------------------------*/
uint8_t KillTimer(uint8_t soft_id)
{
	uint8_t error = NO_ERROR;
	
	DISABLE_TIMER0_OVERFLOW();
	switch (soft_id)
	{
        case STIMER1:
			T0_Ctrl1 = 0;
			T0_Rl1   = 0;
			T0_Ptr1  = 0;
			if	(FktCount > 0)
				--FktCount;               
            break;

        case STIMER2:
  			T0_Ctrl2 = 0;
  			T0_Rl2   = 0;
  			T0_Ptr2  = 0;
  			if	(FktCount > 0)
  			--FktCount;
            break;

        case STIMER3:
 			T0_Ctrl3 = 0;
 			T0_Rl3   = 0;
 			T0_Ptr3  = 0;
 			if	(FktCount > 0)
 			--FktCount;
            break;

        case STIMER4:
			T0_Ctrl4 = 0;
			T0_Rl4   = 0;
			T0_Ptr4  = 0;
			if	(FktCount > 0)
			--FktCount;
            break;
 
		default	: error = ID_ERROR;
			
	}
	if (FktCount == 0)
	{
		// T0 anhalten
		STOP_T0();
		RunControl = STOP;
	}
	else
	{
		ENABLE_TIMER0_OVERFLOW();
	}
	return error;
} /* KillTimer */
//----------------------------------------------------------------------------






