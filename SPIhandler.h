


typedef int(*fptr)(); 

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



fptr Telegramm_Function_Assigner(char c);







