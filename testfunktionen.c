/* GPIO PC0 bis PD1 test Program*/

///Test Funktionen. Simuliert Kommunikationsprotokoll und kann ohne Raspberry Pi die Funktionalität teste. 
//Funktion um zu testen ob GPIO setzen bzw. Rücksetzen werden kann. 
void GPIOtest(){
	for (i =0; i <0; i++)  // Simulate SPI Daten von Rasperrry Pi 
	{
		
	char entsprechnede_num_wert_zu_Pin_Init = 1; //ersten Funktionenbyte. 
	char  telegramm[3] = {1, 0x80, i}; // Beispiel Kommunikationsprotokoll
	fptr Pin_Init_Zeiger = Telegramm_Function_Assigner(c);  // Funktionenzeiger, die die entsprechenden Funktion aufruft. In diesem Fall Pin_Init
	
	Pin_Init_Zeiger(telegramm); // ruft GPIO init mit Telegramm als Argument 
	
	char entsprechnede_num_wert_zu_Pin_Set_Reset = 7;  // 7, weil die char Wert von Pin_Set_Reset = 7 
	char abc[3] = {1,0x08, i}; // Siehe oben(Beispieltelegramm)
	fptr Pin_Set_Reset_Zeiger = Telegramm_Function_Assigner(entsprechnede_num_wert_zu_Pin_Set_Reset);  // Funktionezeiger zum Pin_Set_Reset()
	Pin_Set_Reset_Zeiger(abc);  //ruft die Funktion Pin_Set_Reset() auf
	}

}


void PWM_Test(){
	while(1)

{
	char entsprechnede_num_wert_zu_PMM_Init_Set_Prescaler = 2; 
	char  telegramm[3] = {1, 1,0x10 };  // simulate Kommunikationsprotokoll
	fptr PWM_Init_Set_Prescaler_Zeiger  = Telegramm_Function_Assigner(entsprechnede_num_wert_zu_PMM_Init_Set_Prescaler); //  Funktionenzeiger
	PWM_Init_Set_Prescaler_Zeiger(telegramm);
	
	char entsprechnede_num_wert_zu_PMM_On = 3;
	char abc[3] = {1,1, 0x50}; // Simulate Kommunikationsprotokoll
	fptr PWM_On_Zeiger = Telegramm_Function_Assigner(entsprechnede_num_wert_zu_PMM_On);
	PWM_On_Zeiger(abc); //ruft die Funktion PWM_an auf
	_delay_ms(10000); // Delay of 1 Second


	char entsprechnede_num_wert_zu_PMM_Off = 4; 
	char def[3] = {1, 10, 1};  //Simulate Kommunikationsprotokoll
	fptr PWM_On_Zeiger = Telegramm_Function_Assigner(entsprechnede_num_wert_zu_PMM_Off); 
	PWM_On_Zeiger(def); 
	
	
}
}

void ADC_Test()
{
	ADC_Init(Telegramm[]);  
	Timer0_Init(20); // jede 20s wird Timeroverflow geben. Diese Parameter auch erweiterbar
ISR(TIMER0_OVF_vect) 
{
   uint8_t = getAdc();  // adc value
} 
}

void Ringspiecher_Test()
{
	uint8_t bigarray[100]; // soll im Porgramm global  sein, da es ganze Zeit zugänglich sein soll. Auch möglich es im Stack zu speicher
	ringspeicher_handle_t  workingdata;
    workingdata = ringspeicher_init(bigarray, 5);
    printf(" size :: %i \n", ringspeicher_size(workingdata));
    for( i = 0; i <100; i++)
    {
        ringspeicher_put_override( workingdata, i);
        printf(" in: %i , out %i \n", i, ringspeicher_get_value(workingdata ));




    }
}

void MiniOS_test()
{

   ISR (TIMER1_OVF_vect) //--> ISR   Timer interrupt. The OS_Befehltimer () soll immer hier sein. 
   {
     TCNT1 = 31250;
     OS_Befehltimer ();
   }
  
    DDRD = (1 << DDD0) | (1 << DDD1) | (1 << DDD2);  // Initaialiserung der Portpins
    PORTD &= ~(1 << PORTD0) & ~(1 << PORTD1) & ~(1 << PORTD2); 

     
    TCCR1B = (1 << CS12); // Timer ruft Interreupt jede Sekunde
    TCNT1 = 31250;
    TIMSK1 = (1 << TOIE1);
    sei();   // globale Interrupt aktiviert. 

     
    OS_Befehlgenerieren(&PWM_On, 1, BLOCKED); // Zeiger auf die  Funktion 1, Zeit der Ausführung und OS Status 
    OS_Befehlgenerieren(&PWM_Off, 2, BLOCKED); // Zeiger auf die  Funktion 2, Zeit der Ausführung und OS Status      
    while (1) 
    {
        OS_Befehlaufuehren(); // muss in einer While-Schleife aufgerufen werden
    }
    return 0;
}