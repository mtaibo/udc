/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 06 / 03 / 26
 */

#include "dynamic_list.h"

void createEmptyList(tList* L) {
    *L = LNULL;
}

bool isEmptyList(tList L) {
    return L == LNULL;
}

tPosL first(tList L) {
    return L;
}

tPosL next(tPosL p, tList L) {
    return p->next;
}

tPosL last(tList L) {
    tPosL p; // p: Variable para recorrer las posiciones de la lista.
    for (p = first(L); next(p, L) != LNULL ; p = next(p, L)); // Bucle que recorre la lista con p hasta el último elemento.
    return p;
}

tPosL previous(tPosL p, tList L) {

    if (p == L) return LNULL; // El primer elemento no tiene elemento anterior.

    tPosL q; // q: Variable para recorrer las posiciones de la lista.
    for (q = first(L); next(q, L) != p; q = next(q, L)); // Bucle que recorre la lista con q hasta que el siguiente elemento sea p.
    return q;
}

tPosL findItem(tProjectName n, tList L) {
    tPosL p;
    for (p = L; (p != LNULL) && (strcmp(p->data.projectName, n) != 0); p = next(p, L));
    return p;
}

tItemL getItem(tPosL p, tList L) {
    return p->data;
}

void updateItem(tItemL d, tPosL p, tList* L) {
    p->data = d;
}

void deleteAtPosition(tPosL p, tList* L) {

    /* En este caso empleamos unas instrucciones poco eficientes
     * ya que la complejidad de implementación es mucho menor y
     * deja un código mucho más sencillo de leer mientras que la 
     * eficiencia que se pierde con un máximo de 25 elementos es ínfima.
     */

    /* Para el primer elemento es diferente que para el resto */
    if (p == first(*L)) *L = next(p, *L); // El primer elemento de la lista será ahora el segundo.
    else previous(p, *L) -> next = next(p, *L); // Posición a eliminar es una intermedia

    free(p); // Liberar la memoria que se encontraba en el nodo de p.
}

bool insertItem(tItemL d, tPosL p, tList* L) {

    /* En este caso empleamos unas instrucciones poco eficientes
     * ya que la complejidad de implementación es mucho menor y
     * deja un código mucho más sencillo de leer mientras que la 
     * eficiencia que se pierde con un máximo de 25 elementos es ínfima.
     */

    tPosL q;

    /* Creación del nuevo elemento que se va a insertar en la lista */
    if ((q = malloc(sizeof(struct tNode))) == NULL ) return false;

    /* Insertar los datos dentro del nuevo elemento */
    q->data = d;
    q->next = LNULL;

    if (isEmptyList(*L)) *L = q; // Inserción en una lista vacía
    else if (p == LNULL) last(*L) -> next = q; // Inserción en el final de la lista

    else if (p == *L) {  // Inserción al principio de la lista
        q->next = p;
        *L = q;

    } else {  // Insertar en una posición intermedia
        previous(p, *L) -> next = q;
        q -> next = p;
    }

    return true;
}