#ifndef RINGSPEICHER_H_
#define RINGSPEICHER_H_
/* reference https://github.com/embeddedartistry/embedded-resources/blob/master/examples/c/circular_buffer/circular_buffer.h*/

typedef struct ringspeicher_t ringspeicher_t; 
typedef ringspeicher_t* ringspeicher_handle_t; 



ringspeicher_handle_t ringspeicher_init(uint8_t* buffer, size_t size ); 


void ringspeicher_klaeren(ringspeicher_handle_t rspeicher); 

void ringspeicher_reset (ringspeicher_handle_t rspeicher); 


void ringspeicher_put_override (ringspeicher_handle_t rspeicher, uint8_t data); 


void ringspeicher_put_ignore (ringspeicher_handle_t rspeicher, uint8_t data); 


int ringspeicher_get_value(ringspeicher_handle_t, uint8_t* data); 


bool ringspeicher_leer (ringspeicher_handle_t rspeicher); 

bool ringspeicher_voll (ringspeicher_handle_t rspeicher); 


size_t ringspeicher_kapazitaet(ringspeicher_handle_t rspeicher); 


size_t ringspeicher_size (ringspeicher_handle_t rspeicher);























#endif