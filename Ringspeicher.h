#pragma once
#ifndef RINGSPEICHER_H_
#define RINGSPEICHER_H_

#include <stdbool.h>

/* reference https://github.com/embeddedartistry/embedded-resources/blob/master/examples/c/circular_buffer/circular_buffer.h*/

typedef struct ringspeicher_t Ringspeicher_t;
typedef ringspeicher_t* Ringspeicher_handle_t;


/*
An opaque pointer is one in which no details are revealed of the underlying data
Hides the encapsulated data and makes it safe

typedef ringspeicher_t* ringspeicher_handle_t;

*/


ringspeicher_handle_t Ringspeicher_init(uint8_t* buffer, size_t size);


void Ringspeicher_Klaeren(ringspeicher_handle_t rspeicher);

void Ringspeicher_Reset(ringspeicher_handle_t rspeicher);


void Ringspeicher_Put_Override(ringspeicher_handle_t rspeicher, uint8_t data);


int Ringspeicher_Put_Ignore(ringspeicher_handle_t rspeicher, uint8_t data);


int Ringspeicher_Get_Value(ringspeicher_handle_t);


bool Ringspeicher_Leer(ringspeicher_handle_t rspeicher);

bool Ringspeicher_Voll(ringspeicher_handle_t rspeicher);


size_t Ringspeicher_Kapazitaet(ringspeicher_handle_t rspeicher);


size_t Ringspeicher_Size(ringspeicher_handle_t rspeicher);


void Ringspeicher_Ausgabe(ringspeicher_handle_t rspeicher);






















#endif