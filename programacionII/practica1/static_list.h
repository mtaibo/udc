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

tList createEmptyList (tList *L);
bool isEmptyList (tList L);

tPosL first (tList L);
tPosL last (tList L);
tPosL next (tPosL p, tList L);
tPosL previous (tPosL p, tList L);

bool insertItem (tItemL d, tPosL p, tList *L);
tList deleteAtPosition (tPosL p, tList *L);
tList updateItem (tItemL d, tPosL p, tList *L);

tItemL getItem (tPosL, tList);
tPosL findItem (tProjectName, tList);

#endif
