#include <stdio.h>

typedef enum ADC_Pin{

	PC0_ = 1, 
	PC1_ =2,
	PC2_= 3, 
	PC3_ = 4, 
	PC4_ = 5, 
	PC5_ = 6


} ADC_Pin; 

enum ADC_Pin Selected_Pin(char c ); 

void Adc_Init(char Telegramm[]):
uint8_t Get_Adc(char receivedData[]); 