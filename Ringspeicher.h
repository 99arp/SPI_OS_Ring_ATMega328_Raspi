/* *********  Header.File des Moduls Ringspeicher.c  ***************************************************************
*Enthält die externe Deklaration der öffentlichen Funktionen, die zur Realisierung eines Ringspeichers notwerdig sind
*
* 
* 
*
***********************************************************************************************************/

#ifndef RINGSPEICHER_H_
#define RINGSPEICHER_H_

//*************** öffentliche Enumerations ************************

//*****************************************************************



//**************** öffentliche Konstanten *************************

//*****************************************************************



//*************** öffentliche Strukturen *************************

//**************************************************************



//******************** Typdefinitionen *************************
typedef struct ringspeicher_t Ringspeicher_t;
typedef Ringspeicher_t* Ringspeicher_handle_t;
//*******************************++*****************************

#include <stdbool.h>

//******* Vorwärtsdeklarationen öffentliche Funktionen ********




Ringspeicher_handle_t Ringspeicher_init(uint8_t* buffer, size_t size);
void Ringspeicher_Leeren(Ringspeicher_handle_t rspeicher);
void Ringspeicher_Reset(Ringspeicher_handle_t rspeicher);
void Ringspeicher_Put_Override(Ringspeicher_handle_t rspeicher, uint8_t data);
int Ringspeicher_Put_Ignore(Ringspeicher_handle_t rspeicher, uint8_t data);
int Ringspeicher_Get_Value(Ringspeicher_handle_t);
bool Ringspeicher_Leer(Ringspeicher_handle_t rspeicher);
bool Ringspeicher_Voll(Ringspeicher_handle_t rspeicher);
size_t Ringspeicher_Kapazitaet(Ringspeicher_handle_t rspeicher);
size_t Ringspeicher_Size(Ringspeicher_handle_t rspeicher);
void Ringspeicher_Ausgabe(Ringspeicher_handle_t rspeicher);

/*static Funtkionen. Vollständigkeithalber erwähnt, Die sind im C datei definert. 
 */

 //*************************************************************



#include <stdbool.h>

























#endif