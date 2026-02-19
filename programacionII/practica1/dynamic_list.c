/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: ** / 02 / 26
 */

#include "dynamic_list.h"

void createEmptyList (tList *L) {
  *L = LNULL;
}

bool createNode(tPosL *p) {
  *p = malloc(sizeof(struct tNode));
  return *p != NULL;
}

bool insertItem (tItemL d, tPosL p, tList *L) {
  tPosL q, r;

  // Si no se ha podido crear un nuevo nodo de la lista,
  // no se podrá insertar un nuevo elemento
  if (!createNode(&q)) return false;

  q -> data = d;
  q -> next = LNULL;

  if (*L == LNULL) *L = q; // Si la lista está vacía
  else if (p == LNULL) // Si se quiere insertar al final
}
