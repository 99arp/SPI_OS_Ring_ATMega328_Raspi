#include "minos.h"


static OS_struct befehl_array[OS_MAX_BEFEHLE_NUM]  //Variablen und Informatinen für einzelne Befehle
static uint8_t befehl_nummer = 0u  // Anzahl der regestierte Befehle



/*--------------+-----------------------------------------------------------+
| Name         | OS_Befehlgenerieren                                        |
+--------------+------------------------------------------------------------+
| Beschreibung |  Registreirt die Befehle, überprüft ob fehler vorliegt     |
|              |  Parameter: fncPtr Befehl, uint8_t periodendauer
|              |  Rückgabewert: OS_Rueckmeldung  |
+--------------+-----------------------------------------------------------+
|Autor         |  Prakash Jamakatel                                        |
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

	if(richitg)
	{

		befehl_array[befehl_nummer].function = function;  // befehl_array ist array von struct
		befehl_array[befehl_nummer].periodendauer = periodendauer; 
		befehl_array[befehl_nummer].state = dstate; 
		befehl_array[befehl_nummer].zeit = 1u; 
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
|Autor         |  Prakash Jamakatel                                        |
+--------------+-----------------------------------------------------------+
| Notes        | Version 1.0 -- 31.10.2019   
|              | Es wurden verschiedne Tutorials zur Hilfe genommnen 
|    		   | Verletzungen des Copyright sind nicht beabsichtigt. 
+--------------+-----------------------------------------------------------*/

void  OS_Befehltimer(void)
{
	for(uint8_t i = 0u, i <befehl_nummer; i++)
	{
		if(SUSPENDED != befehl_array[i].state)
		{

			if(befehl_array[i].periodendauer <= befehl_array[i].zeit)
			{
				befehl_array[].zeit = 1u; 
				befehl_array[].state = READY; 


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
|Autor         |  Prakash Jamakatel                                        |
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


