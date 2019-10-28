/*
 * SPI.h
 *
 * 
 *  
 */ 
//----------------------------------------------------------------------------

#ifndef __SPI_H /* avoid double inclusions */
#define __SPI_H

//----------------------------------------------------------------------------

extern char IniSPI(unsigned int Baudrate);

//----------------------------------------------------------------------------

extern uint8_t SPI_RxAvailable(void);

//----------------------------------------------------------------------------

extern uint8_t SPI_Getc(void);

//----------------------------------------------------------------------------

extern void StartSPI_Transmission(uint8_t *SendPtr);
//----------------------------------------------------------------------------

extern uint8_t GetTxStatus(void);

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

#endif /* __SPI_H */