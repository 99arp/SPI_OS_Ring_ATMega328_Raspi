#include <stdio.h>

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

enum DutyCycle_Value DutyCycle(char c)
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



int main(int argc, char const *argv[])
{	
	enum DutyCycle_Value x = DutyCycle(10);
	
	switch(x)
	{
		case(DutyCycle10 ):printf("value is %i\n",10 ); //do this
		default: return 0; 


	}


	return 0;
}