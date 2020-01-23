/* *********  Header.File des Moduls SPIHandler.c  ***************************************************************
*Enthält die externe Deklaration der öffentlichen Funktionen, die für AD- bzw. DA Wandlung notwernding sind 
* 
*
* 
* 
*
***********************************************************************************************************/

#ifndef SPIHANDLER_H
#define SPIHANDLER_H

//*************** öffentliche Enumerations ************************

//*****************************************************************



//**************** öffentliche Konstanten *************************

//*****************************************************************



//*************** öffentliche Strukturen *************************

//**************************************************************



//******************** Typdefinitionen *************************
typedef void(* fptr)(char Telegramm[]);  // Ein Zeiger auf ein Funtkion, die Char Telegramm[] als Eingabeparameter velangt
//*******************************++*****************************



//******* Vorwärtsdeklarationen öffentliche Funktionen ********


void SPI_SlaveInit(void);
void SPI_SlaveSend(char sendBits);
fptr Telegramm_Function_Assigner(char c);

/*static Funtkionen. Vollständigkeithalber erwähnt, Die sind im C datei definert. 
 */

 //*************************************************************



/*
typedef enum  Auszufuehrende_Funktion {

    	IO_Init,
        Pin_on_off,
        PWM_Init,
        PWM_on,
        PWM_off,
        ADC_Init,
        ADC_on,
        ERROR = 100

}Auszufuehrende_Funktion; */











