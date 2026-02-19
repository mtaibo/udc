/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: ** / 02 / 26
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#define LNULL NULL

#include "types.h"

typedef struct tNode* tPosL;
typedef tPosL tList;

typedef struct tNode {
  iItemL data;
  tPosL next;
} tNode;

// Este grupo de funciones sirven para crear una lista vacía
// y para comprobar si una lista L está vacía o no.
void createEmptyList (tList *L);
bool isEmptyList (tList L);

// Este grupo de funciones sirven para moverse por la lista,
// obtener la posición siguiente, anterior, primera o última.
tPosL first (tList L);
tPosL last (tList L);
tPosL next (tPosL p, tList L);
tPosL previous (tPosL p, tList L);

bool createNode(tPosL *P);

// Este grupo de funciones modifican la lista, añadiendo,
// eliminando o actualizando los elementos de la misma.
bool insertItem (tItemL d, tPosL p, tList *L);
void deleteAtPosition (tPosL p, tList *L);
void updateItem (tItemL d, tPosL p, tList *L);

// Este grupo de funciones buscan en la lista para obtener
// un item concreto o la posición de un ítem concreto según
// el projectName del mismo. No modifican las listas.
tItemL getItem (tPosL p, tList L);
tPosL findItem (tProjectName n, tList L);

#endif
