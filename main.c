
/* ***********************  C-Modul: main.c  **********************************************************
*
*  main.c der Studienprojekt-II Fortf�hrung: Fortf�hrung: Programmentwicklung f�r eine SPI gest�tzte
*  Kommunikation zwischen einem Raspberry Pi und einem ATmega328
*   
*  Die Entwicklungsauftr�ge wurden umgesetzt. Es wurde folgende �nderungen und Erweiterungen vorgenommen:
*      ->Entwicklung eines Ringspeichers
*      ->Entwicklung eines Mini OSs mit Zeitbasis, die Funktionen aufrufen kann
*      ->SPI Handler vom Pollen nach eingegangenen Daten umstellen auf Interruptbetrieb.
*            (Hier wurde mit Funktionezeiger SPIHandler realisiert. )
*      ->AD-Wandlung auf Interruptbetreib umgestellt
*      ->Einf�hrung von enums um die Lesbarkeit des Programms zu verbesseren in Daten
*      ->Einbindung eines 16 bit PWMs
*          (8 bit-PWM auch implementiert und mit entsprechenden Befehl aufrufbar. Siehe pwm.c)
*      ->Basisfunktionalit�t wie Setzen, R�cksetzen, Schreiben und Lesen von Pins so wie viele 
*        andere Funktionen 
**
*  Dar�ber hinaus wurden "Naked Numbers". Falls es  Erweiterung im Kommunikationsprotokoll vorgenommen werden 
*  soll, kann dies einfach �ber die �nderung der enum Werte in entsprechenden typedefs der Funktionenvariable. 
*
*  Beispiel: Wenn  PWM Duty Cycle von 55 im Kommunikationsprotokoll hinzugef�gt werden soll, erfolgt diese 
*  einfach �ber Addition von 
*            Variable DutyCylce65 = 65 in  typdef enum DutyCycle_Value
*
*  Die Funktionen und Entwicklungsidee jeder Funktionen sind in jeweiligen .c Datei ausf�hrlich beschrieben. 
*  Dabei wurde es darauf geachtet, dass dieses Projekt auch ohne dazugeh�rigen Studienprojekt alleine anhand des
*  Sourcecodes verst�ndlich ist. 
*
*
*  Es wurde auch Testfunktionen geschreiben, damit die Funktionalit�t auch ohne den Raspberry Pi getest werden kann.
*  Diese aber nicht der Teil des Entwicklungsauftrags.  Die sind unter test.c zu finden. 
*
* WICHTIG: Wenn man in Atmel Studio Optimization an l�sst, kann es dazu f�hren, dass Ringspeicher nicht funktionert. 
*  Da der Puffer des Ringspeichers  immer wieder leerger�umt wird. Optimization soll ausgeschaltet bleiben damit
*  das Projekt wie erw�nscht funktionert.  
*
* Hier ist  ISR-Routine f�r SPI so wie AD-Wandlung sowie  in main Datei Aufruf einer Funktion mithilfe des
* SPIHandler angezeigt. Es ist nun beliebige Erweiterung unter Verwendung der entwickelten Funktionen m�glich
*
*
* Autor- Jamakatel 01.2019
*
********************************************************************************************************/

//************* Header-Dateien ****************


#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

//************ weitere Include-Dateien *********


#include "Ringspeicher.h"
#include "minios.h"
#include "SPIHandler.h"
#include "pwm.h"
#include "adc.h"


//**************************************************




//*****************�ffentliche Konstanten **********

#define MAX_TELEGRAMM_LAENGE 3  // Maximale L�nge des Telegramms.
#define F_CPU 16000000UL        //CPU Freqeunz
//**************************************************




//********* nicht �ffentliche Strukturen ***********

//**************************************************




//****** nicht �ffentliche Typendefinitionen *******

//**************************************************




//************* File-Scope-Variablen ***************



volatile char Telegramm[MAX_TELEGRAMM_LAENGE];
uint8_t Ringspeicher_buffer[50];  //Puffer f�r Ringspeicher
int ringspeicher_size= 10; 

Ringspeicher_handle_t  Ringspeicher_fuer_adc; //Handle f�r Ringspeicher

int SPI_transfer_flag = 0; 
int anzahl_der_eingetroffenen_byte = 0; 
//************* Interrup Service Routine ***************
ISR(SPI_STC_vect)
{
	
	anzahl_der_eingetroffenen_byte++; 
	if(anzahl_der_eingetroffenen_byte > 2)	 // erste Byte Start-Byte zweite Byte ist Adress Byte 3. Byte gibt Anzahl �ber die Datenl�nge Daten ab die wird hier im 
											// Telegramm aufgenommen. 
	{
		  int Telegramm_index=0;
		  SPI_transfer_flag = 0;  // SPI Transfer Flag gesetzt erst nach Max Telegramm L�nge eingetroffen ist.  davor 0 
		  if(sizeof(Telegramm)==0)  // Erste Datenbyteindex = 0
		  {
		  Telegramm_index = 0; 
		  }
		else // Index erh�hen 
		  {
		  Telegramm_index++; 
  
		  }
		  Telegramm[Telegramm_index] = SPI_SlaveReceive(); // SPI_Datei im Telegramm speichern. 
		  if(Telegramm_index > MAX_TELEGRAMM_LAENGE ) // Wenn die L�nge mehr als 5 ist  wird Array mit nullen gef�llt. 
		  { SPI_transfer_flag =1; // SPI Transfer Flag gesetzt erst nach Max Telegramm L�nge eingetroffen ist.  davor 0 
			memset(Telegramm, 0, sizeof(Telegramm));
		  }  
		  }
}

ISR(TIMER0_OVF_vect)
{
  uint8_t  x = Get_Adc(Telegramm);
  Ringspeicher_Put_Override(Ringspeicher_fuer_adc, x); // AD-Wandlung werte im Ringspeicher speicheren 
}


/*Main Function */

int main()
{
 Ringspeicher_Init(Ringspeicher_buffer, ringspeicher_size); //Ringspeicher mit der Gr��e 10
  SPI_SlaveInit(); 

  {
    sei(); 
    while(1)
    {
      if(SPI_transfer_flag==0 )
      {
        fptr Auszufuehrende_Funktion = Telegramm_Function_Assigner(Telegramm[1]);  // erster Datenbyte enth�lt Information dar�ber welche Funtkion aufgerufen werden soll
        Auszufuehrende_Funktion(Telegramm); // 
        
      }
  
    }
    
  }



  
}
