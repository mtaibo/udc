/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 10 / 04 / 26
 */

#include "project_list.h"
#include <string.h> /* Librería que incluye el strcmp() para comparar nombres de proyectos. */
#include <stdlib.h> /* Librería que incluye el malloc() para reservar memoria para nuevos nodos de la lista. */
#include <stdio.h>


void createEmptyListP(tListP* L) {
    *L = NULLP;
}

bool isEmptyListP(tListP L) {
    return L == NULLP;
}

tPosP firstP(tListP L) {
    return L;
}

tPosP nextP(tPosP p, tListP L) {
    return p->next;
}

tPosP lastP(tListP L) {
    tPosP p; // p: Variable para recorrer las posiciones de la lista.
    for (p = firstP(L); nextP(p, L) != NULLP ; p = nextP(p, L)); // Bucle que recorre la lista con p hasta el último elemento.
    return p;
}

tPosP previousP(tPosP p, tListP L) {
    tPosP q; // q: Variable para recorrer las posiciones de la lista.
    if (p == L) return NULLP; // El primer elemento no tiene elemento anterior.
    for (q = firstP(L); nextP(q, L) != p; q = nextP(q, L)); // Bucle que recorre la lista con q hasta que el siguiente elemento sea p.
    return q;
}

tPosP findItemP(tProjectName n, tListP L) {
    tPosP p;
    for (p = L; (p != NULLP) && (strcmp(p->data.projectName, n) != 0); p = nextP(p, L)); // Bucle que recorre la lista con p hasta que los nombres son iguales.
    return p;
}

tItemP getItemP(tPosP p, tListP L) {
    return p->data;
}

void updateItemP(tItemP d, tPosP p, tListP* L) {
    p->data = d;
}

void deleteAtPositionP(tPosP p, tListP *L) {

    tPosP q; // q : Posición auxiliar para eliminar items.
    if (p == *L) *L = nextP(p, *L); // Eliminamos el primer nodo
    else if (nextP(p, *L) == NULLP) {  // Eliminar último nodo

        for (q = *L; nextP(q, *L) != p; q = next(q, *L));
        q->next = NULLP;

    } else {  // Eliminar nodo intermedio
        q = nextP(p, *L); // q : Puntero al elemento que se va a copiar en p y se eliminará.
        p->next = nextP(q, *L);
        updateItemP(getItemP(q, *L), p, L);

        p = q;  // Para que free(p) elimine el nodo correcto
    }

    free(p);
}

bool insertItemP(tItemP d, tPosP p, tListP *L) {

    tPosP q;

    // Si no se ha podido crear un nuevo nodo de la lista,
    // no se podrá insertar un nuevo elemento
    if ((q = malloc(sizeof(struct tNode))) == NULL ) return false;

    q->data = d;
    q->next = NULLP;

    if (isEmptyListP(*L)) *L = q; // Inserción en una lista vacía
    else if (p == NULLP) lastP(*L) -> next = q; // Inserción en el final de la lista

    else {  // Insertar en una posición intermedia
        q->data = getItemP(p, *L);
        q->next = nextP(p, *L);
        updateItemP(d, p, L);

        p->next = q;
    }

    return true;
}