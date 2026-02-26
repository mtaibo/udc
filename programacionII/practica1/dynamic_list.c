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

void deleteAtPosition (tPosL p, tLast *L) {

  tPosL q;

  if (p == *L) { // Eliminamos el primer nodo
    *L = (*L) -> next;
  }
  else if (p -> next == LNULL) { // Eliminar último nodo
    for (q = *L; q->next != p; q = q->next) {
      q -> next = LNULL;
    }
  }
  else { // Eliminar nodo intermedio
    q = p -> next;
    p -> data = q -> data;
    p -> next = q -> next;
    p = q; // Para que free(p) elimine el nodo correcto
  }

  free(p);
}

bool insertItem (tItemL d, tPosL p, tList *L) {

  tPosL q, r;

  // Si no se ha podido crear un nuevo nodo de la lista,
  // no se podrá insertar un nuevo elemento
  if (!createNode(&q)) return false;

  q -> data = d;
  q -> next = LNULL;

  if (isEmptyList(L)) *L = q; // Inserción en una lista vacía
  else if (p == LNULL) { // Inserción en el final de la lista
    for (r = *L; r -> next != LNULL; r = r -> next) {
      r -> next = q;
    }
  }
  else if () { // Inserción al principio de la lista
    q -> next = p;
    *L = q;
  }
  else if () { // Insertar en una posición intermedia
    q -> data = p -> data;
    p -> data = d;
    q -> next = p -> next;
    p -> next = q;
  }

  return true;
}
