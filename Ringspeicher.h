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
typedef ringspeicher_t* Ringspeicher_handle_t;
//*******************************++*****************************



//******* Vorwärtsdeklarationen öffentliche Funktionen ********




ringspeicher_handle_t Ringspeicher_init(uint8_t* buffer, size_t size);
void Ringspeicher_Leeren(ringspeicher_handle_t rspeicher);
void Ringspeicher_Reset(ringspeicher_handle_t rspeicher);
void Ringspeicher_Put_Override(ringspeicher_handle_t rspeicher, uint8_t data);
int Ringspeicher_Put_Ignore(ringspeicher_handle_t rspeicher, uint8_t data);
int Ringspeicher_Get_Value(ringspeicher_handle_t);
bool Ringspeicher_Leer(ringspeicher_handle_t rspeicher);
bool Ringspeicher_Voll(ringspeicher_handle_t rspeicher);
size_t Ringspeicher_Kapazitaet(ringspeicher_handle_t rspeicher);
size_t Ringspeicher_Size(ringspeicher_handle_t rspeicher);
void Ringspeicher_Ausgabe(ringspeicher_handle_t rspeicher);

/*static Funtkionen. Vollständigkeithalber erwähnt, Die sind im C datei definert. 
 */

 //*************************************************************



#include <stdbool.h>

























#endif