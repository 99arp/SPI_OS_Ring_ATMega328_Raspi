#include "SPIhandler.h"






Auszufuehrende_Funktion char_analyser(char c)
{

	switch (c){
		case(0x01) : return IO_Init; 
		case(0x02) : return Pin_on_off; 
		case(0x03) : return PWM_Init; 
		case(0x04) : return PWM_on; 
		case(0x05) : return PWM_off; 
		case(0x06) : return ADC_Init; 
		case(0x07) : return ADC_on; 
		default    : return ERROR; 

	}

}

 


 