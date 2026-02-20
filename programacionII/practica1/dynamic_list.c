/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: ** / 02 / 26
 */

#include "dynamic_list.h"

// Hecho en clase
void createEmptyList (tList *L) {
  *L = LNULL;
}

bool isEmptyList (tList L) {
  return L == LNULL;
}

tPosL first (tList L) {
  return L; // Devuelve la propia lista como posición ya que L es un tPosL al primer elemento
}

tPosL next (tPosL p, tList L) {
  return p -> next;
}

tPosL last (tList L) {
  tPosL p = first(L); // Empezar a recorrer la lista desde el primer elemento
  while (next(p, L) != LNULL) {p = next(p, L);} // Mientras la siguiente posición no sea LNULL, seguir avanzando por la lista
  return p; // Cuando la posición siguiente a la del nodo actual sea LNULL, ese será el último elemento de la lista
}

tPosL previous (tPosL p, tList L) {
  tPosL q = first(L);
  if (q == p) return LNULL;
  while (next(q, L) != p) {q = next(q, L);}
  return q;
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
