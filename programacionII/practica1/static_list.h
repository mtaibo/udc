/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: **********
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: **********
 * GROUP: 2.1
 * DATE: ** / ** / **
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#define LNULL -1
#define MAX 25

#include "types.h"
#include <string.h>

typedef int tPosL;

typedef struct tList {
    tItemL data[MAX];
    tPosL lastPos;
} tList;

// Función que crea una lista vacía, 
// y otra función que devuelve si una lista
// esta vacía o no
void createEmptyList (tList *L);
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
void deleteAtPosition (tPosL p, tList *L);
void updateItem (tItemL d, tPosL p, tList *L);

// Funciones que se encargan de devolver 
// items o su posición en la lista
// (no modifican la lista)
tItemL getItem (tPosL p, tList L);
tPosL findItem (tProjectName n, tList L);

#endif // STATIC_LIST_H
