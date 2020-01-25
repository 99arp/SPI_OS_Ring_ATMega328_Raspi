

/* ***********************  C-Modul: minios.c  ********************************************
*
* Dieses Programm wurde mit Atmelstudio 7  als  Konsolenanwendung  erstellt.
*
* Das Modul ist in Ansi-C (C89) geschrieben. Die Erweiterungen des C99 Standard finden bis auf:
*
*   
*
*  keine Anwendung.
*
*
* In diesem Modul sind alle Funktionen realisiert, die zur Realsierung einer Mini-OS benötigt sind
* 
* Die Folgende Beispiel stellt die mögliche Verwendung des OSs dar. hir wird dargestellt wie verschiedene Funktionen die in verschiedenen 
* Datein deklariert sind periodisch aufgeruft werden. Es werden drei Funktionen die in drei verschiedenen Datein die sich befinden  und LED
* Blinken können als Beispiel genommen.  
*
*
*   #include <avr/io.h>
*   #include <avr/interrupt.h>

*   #include "OS.h"
*   #include "Task0.h"  // Datein wo verschiedenen Funtkionen deklariert sind
*   #include "Task1.h"
*   #include "Task2.h"
*
*                                   
*   ISR (TIMER1_OVF_vect) --> ISR   Timer interrupt. The OS_Befehltimer () soll immer hier sein. 
*   {
*     TCNT1 = 31250;
*     OS_Befehltimer ();
*   }
*
*    Main function. 
*   int16_t main(void)
*   {
*     
*    DDRD = (1 << DDD0) | (1 << DDD1) | (1 << DDD2);  // Initaialiserung der Portpins
*    PORTD &= ~(1 << PORTD0) & ~(1 << PORTD1) & ~(1 << PORTD2); 
*
*     
*    TCCR1B = (1 << CS12); // Timer ruft Interreupt jede Sekunde
*    TCNT1 = 31250;
*    TIMSK1 = (1 << TOIE1);
*    sei();   // globale Interrupt aktiviert. 
*
*     
*    OS_Befehlgenerieren(&Funktion_1, 1, BLOCKED); // Zeiger auf die  Funktion 1, Zeit der Ausführung und OS Status  
*    OS_Befehlgenerieren(&Funktion_2, 2, BLOCKED); // Zeiger auf die  Funktion 2, Zeit der Ausführung und OS Status 
*    OS_Befehlgenerieren(&Funktion_3, 5, BLOCKED); // Zeiger auf die  Funktion 3, Zeit der Ausführung und OS Status 
*
*     
*    while (1) 
*    {
*        OS_Befehlaufuehren(); // muss in einer While-Schleife aufgerufen werden
*    }
*    return 0;
}
*
*
*
* Das C- Modul arbeitet mit den Files-Scope-Variablen:
*
*  - Typ    Name              : 
*       
*
* Globale Variablen gibt es nicht. Das Modul stellt als Schnittstelle öffentliche
* Funktionen bereit:
*
*
*  OS_Rueckmeldung OS_Befehlgenerieren(fncPtr Befehl, uint8_t periodendauer, OS_State Default ) --> Genereiert ausführbare Befehle
*  void  OS_Befehltimer(void;  // Zeit dauer benötigt um zu aufürhung eines Befehls
*  void OS_Befehlausfueheren(void) // führt die Befehhle aus 
*  https://github.com/ferenc-nemeth/avr-simple-scheduler/blob/master/Scheduler/OS/OS.h
*
* Die ausführliche Beschreibung der Funtkionen sind unten von deren Definition zu finden. 
*
*
*
*
*
* Alle anderen Funktionen des Moduls sind durch den vorangestellten static Qualifier als lokale
* Funktionen ausgezeichnet.
*
********************************************************************************************************/

//************* Header-Dateien ****************


#include <stdio.h>
#include <stdlib.h>

//************ weitere Include-Dateien *********
#include <stdint.h>
#include "minios.h"
#include <stdbool.h>
//**************************************************




//********** nicht öffentliche Konstanten **********

//**************************************************




//********* nicht öffentliche Strukturen ***********

//**************************************************




//****** nicht öffentliche Typendefinitionen *******

//**************************************************




//************* File-Scope-Variablen ***************

static OS_Struct befehl_array[OS_MAX_BEFEHLE_NUM] ; //Variablen und Informatinen für einzelne Befehle
static uint8_t befehl_nummer = 0; // Anzahl der regestierte Befehle

//**************************************************

//****************** Funktionen ********************







/*--------------+-----------------------------------------------------------+
| Name         | OS_Befehlgenerieren                                        |
+--------------+------------------------------------------------------------+
| Beschreibung |  Registriert die Befehle, überprüft ob fehler vorliegt     |
|              |  Parameter: fncPtr* Befehl, uint8_t periodendauer
|              |  Rückgabewert: OS_Rueckmeldung  |
+--------------+-----------------------------------------------------------+
|Autor         |          Jamakatel                                        |
+--------------+-----------------------------------------------------------+
| Notes        | Version 1.0 -- 31.10.2019
|              | Es wurden verschiedne Tutorials zur Hilfe genommnen
|    		   | Verletzungen des Copyright sind nicht beabsichtigt.
+--------------+-----------------------------------------------------------*/


OS_Rueckmeldung OS_Befehlgenerieren(fncPtr Befehl, uint8_t periodendauer, OS_State dstate )
{
    OS_Rueckmeldung ret = Default;

    bool richtigkeit = (!( NULL == befehl_array)  //überprüft ob die richtige befehl geneiert wird
                        && (OS_MIN_ZEIT > periodendauer ||  OS_MAX_ZEIT < periodendauer )
                        && (OS_MAX_BEFEHLE_NUM <= befehl_nummer));

    if(richtigkeit)
    {

        befehl_array[befehl_nummer].function = Befehl;  // befehl_array ist array von struct
        befehl_array[befehl_nummer].periodendauer = periodendauer;
        befehl_array[befehl_nummer].state = dstate;
        befehl_array[befehl_nummer].zeit = 1;
        befehl_nummer++;
        ret = Erfolgreich;


    }
    else
    {
        ret = Fehlerhaft;
    }
    return ret;








}


/*--------------+-----------------------------------------------------------+
| Name         | OS_Befehltimer                                       |
+--------------+------------------------------------------------------------+
| Beschreibung |  Registreirt die Befehle, überprüft ob fehler vorliegt     |
|              |  Parameter: fncPtr Befehl, uint8_t periodendauer
|              |  Rückgabewert: OS_Rueckmeldung  |
+--------------+-----------------------------------------------------------+
|Autor         |          Jamakatel                                        |
+--------------+-----------------------------------------------------------+
| Notes        | Version 1.0 -- 31.10.2019
|              | Es wurden verschiedne Tutorials zur Hilfe genommnen
|    		   | Verletzungen des Copyright sind nicht beabsichtigt.
+--------------+-----------------------------------------------------------*/

void  OS_Befehltimer(void)
{
    for(uint8_t i = 0; i <befehl_nummer; i++)
    {
        if(SUSPENDED != befehl_array[i].state)
        {

            if(befehl_array[i].periodendauer <= befehl_array[i].zeit)
            {
                befehl_array[i].zeit = 1;
                befehl_array[i].state = READY;


            }

            else
            {
                befehl_array[i].zeit++;
            }

        }


    }


}
/*--------------+-----------------------------------------------------------+
| Name         | OS_Befehltimer                                       |
+--------------+------------------------------------------------------------+
| Beschreibung |  Registreirt die Befehle, überprüft ob fehler vorliegt     |
|              |  Parameter: fncPtr Befehl, uint8_t periodendauer
|              |  Rückgabewert: OS_Rueckmeldung  |
+--------------+-----------------------------------------------------------+
|Autor         |          Jamakatel                                        |
+--------------+-----------------------------------------------------------+
| Notes        | Version 1.0 -- 31.10.2019
|              | Es wurden verschiedne Tutorials zur Hilfe genommnen
|    		   | Verletzungen des Copyright sind nicht beabsichtigt.
+--------------+-----------------------------------------------------------*/

void OS_Befehlausfueheren(void)
{
    for(uint8_t i = 0; i < befehl_nummer; i++)
    {
        if(READY == befehl_array[i].state)
        {
            befehl_array[i].function();
            befehl_array[i].state = BLOCKED;
        }

    }

}


