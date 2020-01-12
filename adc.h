#include <stdio.h>

typedef enum ADC_Pin{

	ADC_PC0_ = 1, 
	ADC_PC1_ =2,
	ADC_PC2_= 3, 
	ADC_PC3_ = 4, 
	ADC_PC4_ = 5, 
	ADC_PC5_ = 6


} ADC_Pin; 

enum ADC_Pin Selected_Pin(char c ); 

void Adc_Init(char Telegramm[]); 
uint8_t Get_Adc(char Telegramm[]); 