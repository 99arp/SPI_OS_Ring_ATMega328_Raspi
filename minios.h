/* *********  Header.File des Moduls minios.c  ***************************************************************
*Enthält die externe Deklaration der öffentlichen Funktionen, die zur Realsierung einer Mini-OS benötigt sind. Hierbei handelt es sich um eine
* non pre emptiv OS. Wie diese OS verwendet werden kann ist im C Datei dokumentiert. 
* 
*
* 
* 
*
***********************************************************************************************************/

#ifndef MINIOS_H
#define MINIOS_H

//*************** öffentliche Enumerations ************************

//*****************************************************************



//**************** öffentliche Konstanten *************************
#define OS_MAX_BEFEHLE_NUM ((uint8_t) 10)  //Maximale Anzahl an Befehle die durchgeführt werden können
#define OS_MAX_ZEIT     ((uint8_t) 10 ) // Maximale Lauzeit eines Befhels
#define OS_MIN_ZEIT     ((uint8_t) 1 ) //u suffix means that the integer value is unsigned
//*****************************************************************



//*************** öffentliche Strukturen *************************

//**************************************************************



//******************** Typdefinitionen *************************

typedef void (*fncPtr) (void);    // Funktionenzeiger um Befehle zu registiren


typedef enum OS_State
{
    BLOCKED = 0,  // Hier wird  au fden Timer gewartet.
    READY,        // Bereit
    SUSPENDED    // OS wird suspended
} OS_State;

typedef struct
{
    fncPtr function ;  /* diese Funktion wird perodisch aufgerufen*/
    uint8_t periodendauer;   //Period für die Funktion
    uint8_t zeit; // Zähler, wenn zeit = perioden Dauer OS_State = ready
    OS_State state;  //Befehlstatus

} OS_Struct;





typedef enum
{
    Erfolgreich = 1,  //wenn alles erfolgreich erfolgte
    Fehlerhaft = 2,   // mögliche Feheler. Null pointer als Befehlzeiger, Nicht einhaltung der Limits, and andere
    Default

} OS_Rueckmeldung;

//*******************************++*****************************



//******* Vorwärtsdeklarationen öffentliche Funktionen ********


OS_Rueckmeldung OS_Befehlgenerieren(fncPtr Befehl, uint8_t periodendauer, OS_State Default );
void  OS_Befehltimer(void);
void OS_Befehlausfueheren(void);


/*Funktionen die, die werte zurückgeben. Diese Stellen die mögliche Erweiterung der Funtkionalität dar*/



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



