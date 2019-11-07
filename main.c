#include<stdio.h>
#include<stddef.h>

#include "Ringspeicher.h"
#include "minios.h"


int main()
{






	OS_Befehlgenerieren(&Funktion1, 2,  BLOCKED);   //OS_Rueckmeldung OS_Befehlgenerieren(fncPtr Befehl, uint8_t periodendauer, OS_State dstate )
	OS_Befehlgenerieren(&Funktion2, 3, BLOCKED); 


	/*Die Funktionen oben generieren die Befehle und speicheren diese Befehle in 
	  static OS_struct befehl_array[OS_MAX_BEFEHLE_NUM] . Die folgende Funktion führt dann alle 
	  Befehle die in dieser Array gespeichert sind. */

	OS_Befehlausfuehren();                     // Führt die Befehle die generiert worden sind aus





}