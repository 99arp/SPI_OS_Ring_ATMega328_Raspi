/*https://www.avrfreaks.net/forum/tutc-multi-tasking-tutorial-part-1?page=all
https://github.com/ferenc-nemeth/avr-simple-scheduler/blob/master/Scheduler/OS/OS.h
*/

/*
This is a Non Premeptive OS. It just means that there is no Interrupt in this timer.  

*/
#ifndef MINIOS_H_
#define MINIOS_H_

#include <avr/io.h>
#include <stddef.h>


#define OS_MAX_BEFEHLE_NUM ((uint8_t) 10)  //Maximale Anzahl an Befehle die durchgeführt werden können
#define OS_MAX_ZEIT     ((uint8_t) 10 ) // Maximale Lauzeit eines Befhels
#define OS_MIN_ZEIT     ((uint8_t) 1 ) //u suffix means that the integer value is unsigned


typedef void (*fncPtr) (void);    // Funktionenzeiger um Befehle zu registiren


typedef struct
{
	fncPtr function ;  /* diese Funktion wird perodisch aufgerufen*/
	uint8_t periodendauer;   //Period für die Funktion
	uint8_t zeit; // Zähler, wenn zeit = perioden Dauer OS_State = ready
	OS_State state;  //Befehlstatus

} OS_Struct; 

typedef enum
{
	BLOCKED = 0;  // Hier wird  au fden Timer gewartet. 
	READY,        // Hier 
	SUSPENDED    // OS wird suspende
} OS_State; 




typedef enum 
{
	Erfolgreich = 1;  //wenn alles erfolgreich erfolgte
	Fehlerhaft = 2;   // mögliche Feheler. Null pointer als Befehlzeiger, Nicht einhaltung der Limits, and andere
	Default 
	
} OS_Rueckmeldung;



/*Funktionen*/

OS_Rueckmeldung OS_Befehlgenerieren(fncPtr Befehl, uint8_t periodendauer, OS_State default ); 
void  OS_Befehltimer(void); 
void OS_Befehlausfueheren(void); 


/*Funktionen die, die werte zurückgeben*/

// these methods might not be necessary for my use

/*
OS_State OS_Befehlstaterueckgabe(uint8_t befehlnummer ); 
uint8_t OS_Periodendauer(uint8_t befehlnummer); 
uint8_t OS_Zeit(uint8_t befehlnummer);


/* Funktionen die die werte setzen */
/*
void OS_Setbefehlstaterueckgabe(uint8_t befehlnummer, OS_State neu_state); 
void OS_Setperiodendauer(uint8_t befehlnummer, uint8_t neu_periodendauer); 
void OS_Setzeit(uint8_t befehlnummer, uint8_t neu_zeit)

*/



#endif



