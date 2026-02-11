/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "static_list.h"

/*
 * Esta es una forma de llamar a la función
 * que crea las EmptyList, cuando hacemos tList lista;
 * lo que estamos haciendo es reservar espacio en memoria
 * para el struct tList, pero en la memoria habrá basura.
 * Para decir que esa lista es vacía, se tendrá que declarar
 * que la última posición de la lista es LNULL, es decir,
 * que la lista no tiene posiciones o lo que es lo mismo,
 * es una lista vacía.
 *
 * Se pasa &lista de esta forma porque la función pretende
 * modificar el array y necesita la dirección de memoria.
 *
 * tList lista;
 * createEmptyList(&lista);
*/

void createEmptyList (tList *L) {
  L -> lastPos = LNULL; // Con esta flecha estamos haciendo (*L).lastPos
}

bool isEmptyList (tList L) {
  return (L.lastPos == LNULL);
}

tPosL first (tList L) {
  return 0;
}

tPosL last (tList L) {
  return (L.lastPos);
}

tPosL next (tPosL p, tList L) {
  return (p == last(L)) ? LNULL : p+1;
}

tPosL previous (tPosL p, tList L) {
  return (p == 0) ? LNULL : p-1;
}

tItemL getItem (tPosL p, tList L) {
  return L.data[p];
}

tPosL findItem (tProjectName n, tList L) {
  for (tPosL i = first(L); i != LNULL; i = next(i, L)) {
    if (strcmp(getItem(i, L).projectName, n) == 0) return i;
  } return LNULL;
}

void updateItem(tItemL d, tPosL p, tList *L) {
  L -> data[p] = d;
}

void deleteAtPosition (tPosL p, tList *L) {
  tPosL lastPos = last(L);
  for (tPosL i = p; i < lastPos; i++) {
    L -> data[i] = L -> data[i+1];
  } L -> lastPos -= 1;
}

bool insertItem (tItemL d, tPosL p, tList *L) {

  if (last(L) == MAX - 1) return false;

  if (p == LNULL) {
    L -> data[last(L)+1] = d;
    L -> lastPos += 1;
    return true;
  }

  for (tPosL i = last(L); i >= p; i--) {
    L -> data[i+1] = L -> data[i]; 
  } L -> data[p] = d; L -> lastPos += 1; return true;
}
