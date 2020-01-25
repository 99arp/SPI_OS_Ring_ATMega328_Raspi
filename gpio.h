/* *********  Header.File des Moduls gpio.c  ***************************************************************
*Enthält die externe Deklaration der öffentlichen Funktionen, die zum Setzten bzw. Rücksetzen und Schreiben bzw. 
*Lesen des GPIO Pins notwending ist.  
* 
*
* 
* 
*
***********************************************************************************************************/

#ifndef GPIO_H
#define GPIO_H

//*************** öffentliche Enumerations ************************

//*****************************************************************



//**************** öffentliche Konstanten *************************

//*****************************************************************



//*************** öffentliche Strukturen *************************

//**************************************************************



//******************** Typdefinitionen *************************
typedef enum Pin_Number{

	PB0_ = 1,  // Liste der Pins, die auf der Erweiterungskarte ansprechbar sind
	PB1_ = 2,  // Unterstrich, damit der Variablename von AVR Port Konstante unterschiedlich sind
	PC0_ = 3, 
	PC1_ = 4, 
	PC2_ = 5, 
	PC3_ = 6, 
	PC4_ = 7, 
	PC5_ = 8, 
	PC6_ = 9, 
	PD3_ = 10,
	PD5_ = 11, 
	PD6_ = 12, 
	PD7_ = 13 


} Pin_Number; 

typedef enum Mode {
	Input = 1, 
	Output = 2
} Mode; 

typedef enum Pin_Set_Reset {
	Set = 1, 
	Reset = 2
} Pin_Set_Reset;

//*******************************++*****************************



//******* Vorwärtsdeklarationen öffentliche Funktionen ********






void Pin_Init(char Telegramm[]); 
void Pin_Manipulation(char Telegramm[]); 
int Read_Single_Pin(char  Telegramm[] ); 
void Pin_Set_Read_Write(char Telegramm[]); 
/* static Funtkionen. Vollständigkeithalber erwähnt, Die sind im C datei definert. 
enum Pin_Number Pin(char Telegramm[]); 
enum Mode Pin_Function(char c); 
enum Pin_Set_Reset  Pin_Set_Reset_Funktion(char c); 
*/

 //*************************************************************





 


#endif








