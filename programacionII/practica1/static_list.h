/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#define NULL 
#define MAX 1000

typedef int tItemL;
typedef int tPosL;
typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
} tList;

// Función que crea una lista vacía, 
// y otra función que devuelve si una lista
// esta vacía o no
tList createEmptyList (tList *L);
bool isEmptyList (tList L);

// Funciones que sirven para 
// moverse por la lista, obtener posiciones
// siguientes, anteriores y primera o última posición
tPosL first (tList L);
tPosL last (tList L);
tPosL next (tPosL p, tList L);
tPosL previous (tPosL p, tList L);

// Funciones que modifican la lista, añaden, eliminan
// o actualizan un elemento de la lista
bool insertItem (tItemL d, tPosL p, tList *L);
tList deleteAtPosition (tPosL p, tList *L);
tList updateItem (tItemL d, tPosL p, tList *L);

// Funciones que se encargan de devolver 
// items o su posición en la lista
// (no modifican la lista)
tItemL getItem (tPosL p, tList L);
tPosL findItem (tProjectName n, tList L);

#endif
