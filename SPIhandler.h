




typedef enum  Auszufuehrende_Funktion {

    	IO_Init,
        Pin_on_off,
        PWM_Init,
        PWM_on,
        PWM_off,
        ADC_Init,
        ADC_on,
        ERROR = 100

}Auszufuehrende_Funktion;



Auszufuehrende_Funktion char_analyser(char c);




/* Prescaler Funktion here till correct files are created */

typedef enum Prescaler_value{

	Prescaler1 = 1,
	Prescaler8 = 8, 
	PreScaler64 = 64,
	PreScaler256 = 256, 
	PreScaler1024 = 1024,  
	ERROR = 0


} Prescaler_value; 


 Prescaler_value prescale_calculator(char c)
 {

 	switch (c)
 	{
 		case(0x01):  return Prescaler1; 
 		case(0x08):  return Prescaler8; 
 		case(0x40):  return Prescaler64; 
 		case(0x100): return PreScaler256; 
 		case(0x400): return PreScaler1024; 
 		default:     return ERROR;   

 	}



 }


/* this block should be taken someplace right after everything is odne*/
 typedef enum DutyCycle_value{

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


DutyCycle_value DutyCycle(char c)
 {

 	switch (c)
 	{
 		case(10):  return DutyCycle10; 
 		case(20):  return DutyCycle20; 
 		case(30):  return DutyCycle30; 
 		case(40):  return DutyCycle40; 
 		case(50):  return DutyCycle50; 
 		case(60):  return DutyCycle60; 
 		case(70):  return DutyCycle70; 
 		case(80):  return DutyCycle80; 
 		case(90):  return DutyCycle90; 
 		
 		default:     return ON;   

 	}



 }