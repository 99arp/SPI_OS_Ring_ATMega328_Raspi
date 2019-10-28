#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "Ringspeicher.h"

struct circular_buf_t
{
	uint8_t* buffer; 
	size_t head; 
	size_t tail; 
	size_t max; 
	bool full; 
	
};