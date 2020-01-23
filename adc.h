/* *********  Header.File des Moduls adc.c  ***************************************************************
*Enthält die externe Deklaration der öffentlichen Funktionen, die für AD- bzw. DA Wandlung notwernding sind 
* 
*
* 
* 
*
***********************************************************************************************************/

#ifndef ADC_H
#define ADC_H

//*************** öffentliche Enumerations ************************

//*****************************************************************



//**************** öffentliche Konstanten *************************

//*****************************************************************



//*************** öffentliche Strukturen *************************

//**************************************************************



//******************** Typdefinitionen *************************
typedef enum ADC_Pin{

	ADC_PC0_ = 1, 
	ADC_PC1_ =2,
	ADC_PC2_= 3, 
	ADC_PC3_ = 4, 
	ADC_PC4_ = 5, 
	ADC_PC5_ = 6


} ADC_Pin;
//*******************************++*****************************



//******* Vorwärtsdeklarationen öffentliche Funktionen ********



void Adc_Init(char Telegramm[]); 
uint8_t Get_Adc(char Telegramm[]); 
/*static Funtkionen. Vollständigkeithalber erwähnt, Die sind im C datei definert. 
enum ADC_Pin Selected_Pin(char c ); */

 //*************************************************************





 


#endif