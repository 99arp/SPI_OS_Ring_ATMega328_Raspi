
/* *********  Header.File des Moduls pwm.c  ***************************************************************
*Enthält die externe Deklaration der öffentlichen Funktionen, die für PWM notwendig sind
* 
*
* 
* 
*
***********************************************************************************************************/

#ifndef __PWM_H
#define __PWM_H

//*************** öffentliche Enumerations ************************

//*****************************************************************



//**************** öffentliche Konstanten *************************

//*****************************************************************



//*************** öffentliche Strukturen *************************

//**************************************************************



//******************** Typdefinitionen *************************
typedef enum Prescaler_Value{

	Prescaler1 = 1,
	Prescaler8 = 8, 
	Prescaler64 = 64,
	Prescaler256 = 256, 
	Prescaler1024 = 1024,  
	


} Prescaler_Value; 

typedef enum DutyCycle_Value{

	DutyCycle10 = 10,
	DutyCycle20 = 20,
	DutyCycle30 = 30,
	DutyCycle40 = 40,
	DutyCycle50 = 50,
	DutyCycle60 = 60,
	DutyCycle70 = 70,
	DutyCycle80 = 80,
	DutyCycle90 = 90,
	ON = 100
	


} DutyCycle_Value; 

typedef enum Selected_Kanal {

	Kanal1 = 1, 
	Kanal2 = 2, 
	

}Selected_Kanal; 

//*******************************++*****************************



//******* Vorwärtsdeklarationen öffentliche Funktionen ********




void Pwm_Init_And_Set_Prescaler(char Telegramm[]);

void Pwm_On(char Telegramm[]);
void Pwm_Off(char Telegramm[]);

void Pwm_Init_And_Set_Frequency_Timer0(char Telegramm[]);

void Pwm_On_Timer0(char Telegramm[]);
void Pwm_Off_Timer0(char Telegramm[]);


/*static Funtkionen. Vollständigkeithalber erwähnt, Die sind im C datei definert. 
enum Prescaler_Value Prescale_Calculator(char c);
enum DutyCycle_Value DutyCycle(char c);
enum  Selected_Kanal Kanal_Select (char c); */
 //*************************************************************





 





 
#endif // Ende pwm.h
