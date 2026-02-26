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
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct tNode* tPosL;
typedef tPosL tList;

typedef struct tNode {
  tItemL data;
  tPosL next;
} tNode;

void createEmptyList (tList *L);
bool isEmptyList (tList L);

tPosL first (tList L);
tPosL last (tList L);
tPosL next (tPosL p, tList L);
tPosL previous (tPosL p, tList L);

bool createNode(tPosL *P);

bool insertItem (tItemL d, tPosL p, tList *L);
void deleteAtPosition (tPosL p, tList *L);
void updateItem (tItemL d, tPosL p, tList *L);

tItemL getItem (tPosL p, tList L);
tPosL findItem (tProjectName n, tList L);

#endif
