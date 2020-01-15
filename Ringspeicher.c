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
/*--------------+------------------------------------------------------------------+
| Name         |  Ringspeicher_Ausgabe                                             |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Inhalt des Ringspeichers ausgeben                                |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t rspeicher                       |
|              |  Rückgabewert: void                                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
void Ringspeicher_Ausgabe(ringspeicher_handle_t rspeicher)
{
    int c;
    for( c = 0; c < ringspeicher_size(rspeicher); c++)
    {
        printf("  head::%i  tail::%i  ", rspeicher->buffer[rspeicher->head], rspeicher->buffer[rspeicher->tail]);

        if(c == ringspeicher_size(rspeicher))
            printf("Ant the size i s %i " , ringspeicher_size(rspeicher));
    }
}
/*--------------+------------------------------------------------------------------+
| Name         |  Ringspeicher_Init                                                |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Ringspeicher Initialisiern.                                      |
|              |                                                                   |
|              |  Parameter: uint8_t* buffer: Ort wo die Daten die im Ringspeicher |
|              |             gespeichert werden sollen, gespeichert sind.          |
|              |             size_t size   : Größe des Ringspeichers               |
|              |  Rückgabewert: ringspeicher_handle_t                              |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
ringspeicher_handle_t Ringspeicher_Init(uint8_t* buffer, size_t size)
{

    ringspeicher_handle_t rspeicher = malloc(sizeof(ringspeicher_t));  // create the pointer data type with malloc and assign the required memory

    rspeicher->buffer = buffer;
    rspeicher->max = size;
    ringspeicher_reset(rspeicher);
    return rspeicher;


}

/*--------------+------------------------------------------------------------------+
| Name         |   static  zeiger_vor                                              |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion. Zeiger für Ringspeicher nach vorne rücken        |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t                                 |
|              |  Rückgabewert:  void                                              |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
static void  Zeiger_Vor(ringspeicher_handle_t rspeicher)   //move the pointer vorwärts if new element is added
{

    if (rspeicher->full)
    {
        rspeicher->tail = (rspeicher->tail + 1) % rspeicher->max;

    }

    rspeicher->head = (rspeicher->head + 1) % rspeicher->max;

    rspeicher->full = (rspeicher->head == rspeicher->tail);

}
/*--------------+------------------------------------------------------------------+
| Name         |   static  zeiger_rueck                                            |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion. Zeiger für Ringspeicher nach hinten rücken       |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t                                 |
|              |  Rückgabewert:  void                                              |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/

static void Zeiger_Rueck(ringspeicher_handle_t rspeicher)  // file scope function. Only implemented in this file
{
    rspeicher->full = false; 							//move the
    rspeicher->tail = (rspeicher->tail + 1) % rspeicher->max;

}


/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Klaeren                                           |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion. Klärt den Ringspeicher                           |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t                                 |
|              |  Rückgabewert:  void                                              |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/

void Ringspeicher_Klaeren(ringspeicher_handle_t rspeicher)
{
    free(rspeicher);  // deallocates the memoory assigned during creation through malloc
}

/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Reset                                             |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion. Resettet  den Ringspeicher                       |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t                                 |
|              |  Rückgabewert:  void                                              |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
void Ringspeicher_Reset(ringspeicher_handle_t rspeicher)
{
    rspeicher->head = 0;
    rspeicher->tail = 0;
    rspeicher->full = false;

}
/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Size                                              |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion. gibt größe des Ringspeichers zurück              |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t                                 |
|              |  Rückgabewert:  size_t                                            |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
size_t Ringspeicher_Size(ringspeicher_handle_t rspeicher)
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
/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Kapazitaet                                        |
+--------------+-------------------------------------------------------------------+
| Beschreibung |  Helferfunktion. gibt maximale Kapazitaet des Ringspeichers       |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t                                 |
|              |  Rückgabewert:  size_t                                            |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
size_t Ringspeicher_Kapazitaet(ringspeicher_handle_t rspeicher)  //maximum capacity of ringspeicher
{
    return rspeicher->max;

}
/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Put_Override                                      |
+--------------+-------------------------------------------------------------------+
|              | Beschreibung:  Neue Datei im Ringspeicher hinzufügen. Wenn neue   |
|              |       Daten eintreffen und der Ringspeicher voll ist, wird der als| 
|              |       erste eingetroffenen Datenbyte überschierben                |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t rspeicher, uint8_t data         |
|              |  Rückgabewert:  void                                              |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
void Ringspeicher_Put_Override(ringspeicher_handle_t rspeicher, uint8_t data) // replace the first data byte //change to other data type to store other data type
{

    rspeicher->buffer[rspeicher->head] = data;
    Zeiger_Vor(rspeicher);

}
/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Put_Ignore                                      |
+--------------+-------------------------------------------------------------------+
|              | Beschreibung:  Neue Datei im Ringspeicher hinzufügen. Wenn neue   |
|              |       Daten eintreffen und der Ringspeicher voll ist, wird der als| 
|              |       erste eingetroffenen Datenbyte überschierben                |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t                                 |
|              |  Rückgabewert:  size_t                                            |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/

int Ringspeicher_Put_Ignore(ringspeicher_handle_t rspeicher, uint8_t data)  //ignore the data bytes if ring is full
{
    if (!Ringspeicher_Voll(rspeicher))   // return 0 if transmission is sucessful -1 if not
    {
        data = rspeicher->buffer[rspeicher->tail],
                Zeiger_Rueck(rspeicher);
        return 0;
    }
    return -1;

}
/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Get_Value                                         |
+--------------+-------------------------------------------------------------------+
|              | Beschreibung: Gibt der erste Wert vom Buffer zurück               |
|              |                                                                   |
|              |  Parameter: ringspeicher_handle_t                                 |
|              |  Rückgabewert:  size_t                                            |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
int  Ringspeicher_Get_Value(ringspeicher_handle_t rspeicher)
{
    int data;
    if (!Ringspeicher_Leer(rspeicher)) // return 0 if transmission is sucessful 1 if not
    {
        data = rspeicher->buffer[rspeicher->head]; //changed from tail to head
        Zeiger_Rueck(rspeicher);

    }

    return data;

}

/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Leer                                              |
+--------------+-------------------------------------------------------------------+
|              | Beschreibung: Überprüfen ob Ringspeicher leer ist                 |
|              |                                                                   |
|              |                                                                   |
|              | Parameter: ringspeicher_handle_t                                  |
|              | Rückgabewert:  bool                                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
bool Ringspeicher_Leer(ringspeicher_handle_t rspeicher)  //check if the buffer is empty
{

    return(!rspeicher->full && (rspeicher->head == rspeicher->tail));
}

/*--------------+------------------------------------------------------------------+
| Name         |    Ringspeicher_Voll                                              |
+--------------+-------------------------------------------------------------------+
|              | Beschreibung: Überprüfen ob Ringspeicher voll ist                 |
|              |                                                                   |
|              | Parameter: ringspeicher_handle_t                                  |
|              | Rückgabewert:  bool                                               |
+--------------+-------------------------------------------------------------------+
|Autor         |  Jamakatel                                                        |
+--------------+-------------------------------------------------------------------+
| Notes        |  Version 1.0 -- 31.10.2019                                        |
|              |                                                                   |
|              |                                                                   |
+--------------+------------------------------------------------------------------*/
bool Ringspeicher_Voll(ringspeicher_handle_t rspeicher)
{
    return rspeicher->full;
}




/*

Citable book:  https://books.google.de/books?id=pfdaDwAAQBAJ&pg=PA221&dq=ring+buffer+design+c&hl=en&sa=X&ved=0ahUKEwiBq_2Y4L7lAhUJ86YKHVefAMgQ6AEIOjAC#v=onepage&q=ring%20buffer%20design%20c&f=false

To my understanding on date 28.10 the following steps should be taken to implement the ring buffer

ringspeicher_int() Here the size of ring buffer is initialized with data varaiable and buffer does
the following:







*/