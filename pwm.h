/* Prescaler Funktion here till correct files are created */

#ifndef __PWM_H
#define __PWM_H

typedef enum Prescaler_Value{

	Prescaler1 = 1,
	Prescaler8 = 8, 
	Prescaler64 = 64,
	Prescaler256 = 256, 
	Prescaler1024 = 1024,  
	ERROR = 0


} Prescaler_value; 

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
	


} DutyCycle_value; 

typedef enum Selected_Kanal {

	Kanal1 = 1, 
	Kanal2 = 2, 
	ERROR = 0

}Selected_kanal; 


enum Prescaler_Value Prescale_Calculator(char c);
enum DutyCycle_Value DutyCycle(char c);
enum  Selected_Kanal Kanal_Select (char c); 

void Set_Frequency(char receivedData[]);
void Pwm_Init
void Set_Pwm(char receivedData[]);
void Pwm_Off(char receivedData[]);

 
#endif // Ende pwm.h
