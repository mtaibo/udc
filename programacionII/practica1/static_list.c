/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: **********
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: **********
 * GROUP: 2.1
 * DATE: ** / ** / **
 */

#include "static_list.h"

// Esta función crea una lista vacía simplemente definiendo
// la última posición de la lista como LNULL, dejándola así
// vacía, aunque el array del data tenga contenido residual
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
    return (strcmp(getItem(i,L).projectName, n) == 0) ? i : LNULL;
  }
}

void updateItem(tItemL d, tPosL p, tList *L) {
  L -> data[p] = d;
}

void deleteAtPosition (tPosL p, tList *L) {
  tPosL lastPos = last(*L);
  for (tPosL i = p; i < lastPos; i++) {
    L -> data[i] = L -> data[i+1];
  } L -> lastPos -= 1;
}

bool insertItem (tItemL d, tPosL p, tList *L) {

  if (last(*L) == MAX - 1) return false;

  if (p == LNULL) {
    L -> data[last(*L)+1] = d;
    L -> lastPos += 1;
    return true;
  }

  for (tPosL i = last(*L); i >= p; i--) {
    L -> data[i+1] = L -> data[i]; 
  } L -> data[p] = d; L -> lastPos += 1; return true;
}
