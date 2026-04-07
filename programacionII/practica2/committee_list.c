/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 10 / 04 / 26
 */

#include "committee_list.h"

#include <string.h> /* Librería que incluye el strcmp() para comparar nombres de proyectos. */
#include "stdio.h"

void createEmptyListC(tListC *L) {
    L->lastPos = NULLC;
}

bool isEmptyListC(tListC L) {
    return (L.lastPos == NULLC);
}

tPosC firstC(tListC L) {
    return 0;
}

tPosC last(tListC L) {
    return (L.lastPos);
}

tPosC next(tPosC p, tListC L) {
    return (p == lastC(L)) ? NULLC : p + 1;
}

tPosC previousC(tPosC p, tListC L) {
    return (p == 0) ? NULLC : p - 1;
}

tItemC getItemC(tPosC p, tListC L) {
    return L.data[p];
}

tPosC findItemC(tCommitteeName n, tListC L) {

    for (tPosC i = firstC(L); i != NULLC; i = next(i, L)) { // i: variable para recorrer posiciones en la lista.
        if (strcmp(getItemC(i, L).committeeName, n) == 0) return i;
    } 
    
    return NULLC;
}

void updateItemC(tItemC d, tPosC p, tListC *L) {
    L->data[p] = d;
}

void deleteAtPositionC(tPosC p, tListC *L) {

    tPosC lastPos = lastC(*L);  // Ahorra la llamada a last(*L) en cada iteración del bucle. Variable que almacena la última posición de la lista.

    // Bucle para mover los elementos a la izquierda para cerrar el espacio generado al eliminar un elemento.
    for (tPosC i = p; i < lastPos; i++) { // i: variable para recorrer posiciones en la lista.
        L->data[i] = L->data[i + 1];
    } 
    
    L->lastPos--;  // Reduce el tamaño de la lista.
}

bool insertItemC(tItemC d, tPosC p, tListC *L) {
 
    tPosC lastPos = last(*L);  // Ahorra la llamada a last(*L) en cada iteración del bucle. Variable que almacena la última posición de la lista.

    if (lastPos == MAX - 1) return false;  // La inserción no es posible por falta de tamaño.
    if (p == NULLC) p = lastPos + 1;  // Con p = LNULL, inserción al final de la lista.

    // Bucle para mover los elementos a la derecha y abrir espacio para el nuevo elemento.
    for (tPosC i = lastPos; i >= p; i--) { // i: variable para recorrer posiciones en la lista.
        L->data[i + 1] = L->data[i];
    }

    L->data[p] = d; // Asigna el nuevo dato en la lista.
    L->lastPos += 1; // Aumenta el tamaño de la lista.
    return true;
}