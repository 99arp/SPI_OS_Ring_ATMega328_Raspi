

/* ***********************  C-Modul: crc.c  ********************************************
*
* Dieses Programm wurde mit Atmelstudio 7  als  Konsolenanwendung  erstellt.
*
* Das Modul ist in Ansi-C (C89) geschrieben. Die Erweiterungen des C99 Standard finden bis auf:
*
*   
*
*  keine Anwendung.
*
*
* In diesem Modul sind alle Funktionen realisiert, die
* zur Realierung eines CRC-Prüfverfahrens benötigt sind
*
*
*
*
* Das C- Modul arbeitet mit den Files-Scope-Variablen:
*
*  - Typ    Name              : 
*       
*
* Globale Variablen gibt es nicht. Das Modul stellt als Schnittstelle öffentliche
* Funktionen bereit:
*
*
*   unsigned crc8(unsigned crc, unsigned char const *data, size_t len); --> Arbeitet mit der Tabelle der im Header-Datei definiert ist 
*   unsigned crc8_slow(unsigned crc, unsigned char const *data, size_t len); --> Arbeitet ohne die Tabelle 
* 
*   /* Beispiel Anwerndung der CRC-Prüfverfahren /*
*       #ifdef TEST
*       #include <stdio.h>
*       #define CHUNK 16384
*
*       int main(void) {
*           unsigned char buf[CHUNK];
*           unsigned crc = crc8(0, NULL, 0);
*           size_t len;
*           do {
*                len = fread(buf, 1, CHUNK, stdin);
*                    crc = crc8(crc, buf, len);
*               } while (len == CHUNK);
*           printf("%#02x\n", crc);
*            return 0;
*       }
*       #endif
*
* Die ausfürhliche Beschreibung der Funtkionen sind unten von deren Difinition zu finden. 
*
*
*
*
*
* Alle anderen Funktionen des Moduls sind durch den vorangestellten static Qualifier als lokale
* Funktionen ausgezeichnet.
*
********************************************************************************************************/

//************* Header-Dateien ****************


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
//************ weitere Include-Dateien *********

#include "crc.h"

//**************************************************




//********** nicht öffentliche Konstanten **********

//**************************************************




//********* nicht öffentliche Strukturen ***********

//**************************************************




//****** nicht öffentliche Typendefinitionen *******

//**************************************************




//************* File-Scope-Variablen ***************

//**************************************************

//****************** Funktionen ********************


// 8-bit CRC using the polynomial x^8+x^6+x^3+x^2+1, 0x14D.
// Chosen based on Koopman, et al. (0xA6 in his notation = 0x14D >> 1):
// http://www.ece.cmu.edu/~koopman/roses/dsn04/koopman04_crc_poly_embedded.pdf
//
// This implementation is reflected, processing the least-significant bit of the
// input first, has an initial CRC register value of 0xff, and exclusive-or's
// the final register value with 0xff. As a result the CRC of an empty string,
// and therefore the initial CRC value, is zero.
//
// The standard description of this CRC is:
// width=8 poly=0x4d init=0xff refin=true refout=true xorout=0xff check=0xd8
// name="CRC-8/KOOP"




// Returns the CRC-8 of data[0..len-1] applied to the seed crc. This permits the
// calculation of a CRC a chunk at a time, using the previously returned value
// for the next seed. If data is NULL, then return the initial seed. See the
// test code for an example of the proper usage.

/*--------------+-----------------------------------------------------------+
| Name         | crc8                                                       |
+--------------+------------------------------------------------------------+
| Beschreibung |  Realisierung eines crc8 Algorithmus                       |
|              |  Parameter: unsigned char crc                              |
|              |             unsigned char const *data                      |
|              |             size_t   len                                   |
|              | Gibt die CRC-8 der Daten[0..len-1] zurück, die auf die     |
|              | Seed-CRC angewendet wurde. Dies erlaubt die                |
|              | Berechnung eines CRC ein Stück zu einer Zeit,              |
|              | mit dem vorher zurückgegebenen Wert                        |
|              | für die nächste Aussaat. Wenn die Daten                    |
|              | NULL sind, dann geben Sie den ursprünglichen Seed zurück.  | 
|              |                                                            |
|              |                                                            |
|              |  Rückgabewert: unsigned char crc                           |
|              |                                                            |
+--------------+------------------------------------------------------------+
|Autor         |          Jamakatel                                         |
+--------------+------------------------------------------------------------+
|              | Note: Es wurden verschiedne Tutorials zur Hilfe genommnen  |
|              | Verletzungen des Copyright sind nicht beabsichtigt.        |
+--------------+-----------------------------------------------------------*/

unsigned crc8(unsigned crc, unsigned char const *data, size_t len)
{
    if (data == NULL)
        return 0;
    crc &= 0xff;
    unsigned char const *end = data + len;
    while (data < end)
        crc = crc8_table[crc ^ *data++];
    return crc;
}



/*--------------+------------------------------------------------------------- ---+
| Name         | crc8_slow                                                       |
+--------------+-----------------------------------------------------------------+
| Beschreibung |  Realisierung eines crc8 Algorithmus ohne Datentabelle          |
|              |  Parameter: unsigned char crc                                   |
|              |             unsigned char const *data                           |
|              |             size_t   len                                        |
|              | crc8_slow() ist eine äquivalente bitweise Implementierung von   | 
|              | crc8(), die keine Tabelle benötigt,und die verwendet werden kann| 
|              | um crc8_table[] zu erzeugen. Der Eintrag k in thetable ist der  |
|              | CRC-8 des einzelnen Bytes k, mit einem anfänglichen crc-Wert von|
|              | null 0xb2 ist die Bit-Reflektion von 0x4d, das Polynom          |
|              | Koeffizienten unter x^8.                                        |
|              |                                                                 |
|              |                                                                 |
|              |  Rückgabewert: unsigned char crc                                |
|              |                                                                 |
+--------------+-----------------------------------------------------------------+
|Autor         |          Jamakatel                                              |
+--------------+-----------------------------------------------------------------+
|              | Note: Es wurden verschiedne Tutorials zur Hilfe genommnen       |
|              | Verletzungen des Copyright sind nicht beabsichtigt.             |
+--------------+----------------------------------------------------------------*/
unsigned crc8_slow(unsigned crc, unsigned char const *data, size_t len)
{
    if (data == NULL)
        return 0;
    crc = ~crc & 0xff;
    while (len--) {
        crc ^= *data++;
        for (unsigned k = 0; k < 8; k++)
            crc = crc & 1 ? (crc >> 1) ^ 0xb2 : crc >> 1;
    }
    return crc ^ 0xff;
}

