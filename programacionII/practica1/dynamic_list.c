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

void deleteAtPosition(tPosL p, tList *L) {

    tPosL q; // q : Posición auxiliar para eliminar items.

    if (p == *L) *L = next(p, *L); // Eliminamos el primer nodo

    else if (next(p, *L) == LNULL) {  // Eliminar último nodo

        for (q = *L; next(q, *L) != p; q = next(q, *L));
        q->next = LNULL;

    } else {  // Eliminar nodo intermedio

        q = next(p, *L); // q : Puntero al elemento que se va a copiar en p y se eliminará.
        p->next = next(q, *L);
        updateItem(getItem(q, *L), p, L);

        p = q;  // Para que free(p) elimine el nodo correcto
    }

    free(p);
}

bool insertItem(tItemL d, tPosL p, tList *L) {

    tPosL q;

    // Si no se ha podido crear un nuevo nodo de la lista,
    // no se podrá insertar un nuevo elemento
    if ((q = malloc(sizeof(struct tNode))) == NULL ) return false;

    q->data = d;
    q->next = LNULL;

    if (isEmptyList(*L)) *L = q; // Inserción en una lista vacía
    else if (p == LNULL) last(*L) -> next = q; // Inserción en el final de la lista

    else {  // Insertar en una posición intermedia

        q->data = getItem(p, *L);
        q->next = next(p, *L);
        updateItem(d, p, L);

        p->next = q;
    }

    return true;
}