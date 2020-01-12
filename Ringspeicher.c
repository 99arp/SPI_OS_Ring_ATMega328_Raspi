//
// Created by praka on 15.11.2019.
//

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#include "Ringspeicher.h"


struct ringspeicher_t  //_t jsut means its "user defined typ
{
    uint8_t* buffer;   // die gespeicherte Daten
    size_t head;  // Speicher Anfang
    size_t tail;  // Speicher Ende
    size_t max;   //Max Größe vom Speicher, definiert in ringspeicher_init()
    bool full;   // ist der Ringspeicher voll?

};

void ringspeicher_ausgabe(ringspeicher_handle_t rspeicher)
{
    int c;
    for( c = 0; c < ringspeicher_size(rspeicher); c++)
    {
        printf("  head::%i  tail::%i  ", rspeicher->buffer[rspeicher->head], rspeicher->buffer[rspeicher->tail]);

        if(c == ringspeicher_size(rspeicher))
            printf("Ant the size i s %i " , ringspeicher_size(rspeicher));
    }
}

ringspeicher_handle_t ringspeicher_init(uint8_t* buffer, size_t size)
{

    ringspeicher_handle_t rspeicher = malloc(sizeof(ringspeicher_t));  // create the pointer data type with malloc and assign the required memory

    rspeicher->buffer = buffer;
    rspeicher->max = size;
    ringspeicher_reset(rspeicher);
    return rspeicher;


}


static void  zeiger_vor(ringspeicher_handle_t rspeicher)   //move the pointer vorwärts if new element is added
{

    if (rspeicher->full)
    {
        rspeicher->tail = (rspeicher->tail + 1) % rspeicher->max;

    }

    rspeicher->head = (rspeicher->head + 1) % rspeicher->max;

    rspeicher->full = (rspeicher->head == rspeicher->tail);

}


static void zeiger_rueck(ringspeicher_handle_t rspeicher)  // file scope function. Only implemented in this file
{
    rspeicher->full = false; 							//move the
    rspeicher->tail = (rspeicher->tail + 1) % rspeicher->max;

}




void ringspeicher_klaeren(ringspeicher_handle_t rspeicher)
{
    free(rspeicher);  // deallocates the memoory assigned during creation through malloc
}


void ringspeicher_reset(ringspeicher_handle_t rspeicher)
{
    rspeicher->head = 0;
    rspeicher->tail = 0;
    rspeicher->full = false;

}

size_t ringspeicher_size(ringspeicher_handle_t rspeicher)
{
    size_t size = rspeicher->max;

    if (!rspeicher->full)
    {
        if (rspeicher->head == rspeicher->tail)
        {
            size = (rspeicher->head - rspeicher->tail);  // 0 if the pointer to head and tail are same
            printf("print 1");
        }
        else
        {
            size = (/*rspeicher->max +*/ rspeicher->head - rspeicher->tail);  // if not completely full  max element
            /* rspeicher->max  commented out because it works that way); */
            printf("print 2");
        }
    }

    return size;

}

size_t ringspeicher_kapazitaet(ringspeicher_handle_t rspeicher)  //maximum capacity of ringspeicher
{
    return rspeicher->max;

}

void ringspeicher_put_override(ringspeicher_handle_t rspeicher, uint8_t data) // replace the first data byte
{

    rspeicher->buffer[rspeicher->head] = data;
    zeiger_vor(rspeicher);

}

int ringspeicher_put_ignore(ringspeicher_handle_t rspeicher, uint8_t data)  //ignore the data bytes if ring is full
{
    if (!ringspeicher_voll(rspeicher))   // return 0 if transmission is sucessful -1 if not
    {
        data = rspeicher->buffer[rspeicher->tail],
                zeiger_rueck(rspeicher);
        return 0;
    }
    return -1;

}

int  ringspeicher_get_value(ringspeicher_handle_t rspeicher)
{
    int data;
    if (!ringspeicher_leer(rspeicher)) // return 0 if transmission is sucessful 1 if not
    {
        data = rspeicher->buffer[rspeicher->head]; //changed from tail to head
        zeiger_rueck(rspeicher);

    }

    return data;

}

bool ringspeicher_leer(ringspeicher_handle_t rspeicher)  //check if the buffer is empty
{

    return(!rspeicher->full && (rspeicher->head == rspeicher->tail));
}

bool ringspeicher_voll(ringspeicher_handle_t rspeicher)
{
    return rspeicher->full;
}




/*

Citable book:  https://books.google.de/books?id=pfdaDwAAQBAJ&pg=PA221&dq=ring+buffer+design+c&hl=en&sa=X&ved=0ahUKEwiBq_2Y4L7lAhUJ86YKHVefAMgQ6AEIOjAC#v=onepage&q=ring%20buffer%20design%20c&f=false

To my understanding on date 28.10 the following steps should be taken to implement the ring buffer

ringspeicher_int() Here the size of ring buffer is initialized with data varaiable and buffer does
the following:







*/