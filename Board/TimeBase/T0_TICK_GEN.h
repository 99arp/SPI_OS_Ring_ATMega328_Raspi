/*
 * T0_TICK_GEN.h
 *
 * Created: 11.04.2016 12:18:36
 *  Author: Michael
 */ 



#ifndef T0_TICK_GEN_H_
#define T0_TICK_GEN_H_





#endif /* T0_TICK_GEN_H_ */



// Makros
#define DISABLE_TIMER0_OVERFLOW() TIMSK0 &= ~0x01			// Overflow Interrupt sperren   : TOIE0-Bit = 0
#define ENABLE_TIMER0_OVERFLOW() TIMSK0 |= 0x01				// Overflow Interrupt freigeben : TOIE0-Bit = 1
#define START_T0()  TCCR0B |= 0x05	                        // Starten des Zählers durch Setzen des Prescalers auf Wert <> 0  hier 0x05 für Prescaler =1024
#define STOP_T0()   TCCR0B &= ~(0x05)						// Stoppen des Zählers durch Setzen des Prescalers auf Wert 0



// Konstanten
//Reload Wert  T0 -Aufwärtszähler bei Prescaler = 1024 und 10ms Zykluszeit
#define T0_RELOAD_10MSEC		255-(int)(0.01* BoardClock/1024)+1


#define STIMER1 1	// Nummern der Software-Timer
#define STIMER2 2
#define STIMER3 3 
#define STIMER4 4

#define TIMER_REGISTER TCNT0

#define START   1
#define STOP    0


// Enumerations
enum StartError { NO_ERROR, PTR_ERROR, ID_ERROR};


// Öffentliche Funktionen
extern void TickInit(void);
extern void TerminateSwTimer(void);
extern uint8_t StartTimer (uint8_t soft_id, uint16_t ticks, void (*funcptr) (void));
extern uint8_t KillTimer(uint8_t soft_id);