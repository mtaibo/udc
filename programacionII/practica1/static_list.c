/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 27 / 02 / 26
 */

#include "static_list.h"

void createEmptyList(tList *L) {
    L->lastPos = LNULL;
}

bool isEmptyList(tList L) {
    return (L.lastPos == LNULL);
}

tPosL first(tList L) {
    return 0;
}

tPosL last(tList L) {
    return (L.lastPos);
}

tPosL next(tPosL p, tList L) {
    return (p == last(L)) ? LNULL : p + 1;
}

tPosL previous(tPosL p, tList L) {
    return (p == 0) ? LNULL : p - 1;
}

tItemL getItem(tPosL p, tList L) {
    return L.data[p];
}

tPosL findItem(tProjectName n, tList L) {

    for (tPosL i = first(L); i != LNULL; i = next(i, L)) { // i: variable para recorrer posiciones en la lista.
        if (strcmp(getItem(i, L).projectName, n) == 0) return i;
    } 
    
    return LNULL;
}

void updateItem(tItemL d, tPosL p, tList *L) {
    L->data[p] = d;
}

void deleteAtPosition(tPosL p, tList *L) {

    tPosL lastPos = last(*L);  // Ahorra la llamada a last(*L) en cada iteración del bucle. Variable que almacena la última posición de la lista.

    // Bucle para mover los elementos a la izquierda para cerrar el espacio generado al eliminar un elemento.
    for (tPosL i = p; i < lastPos; i++) { // i: variable para recorrer posiciones en la lista.
        L->data[i] = L->data[i + 1];
    } 
    
    L->lastPos--;  // Reduce el tamaño de la lista.
}

bool insertItem(tItemL d, tPosL p, tList *L) {
 
    tPosL lastPos = last(*L);  // Ahorra la llamada a last(*L) en cada iteración del bucle. Variable que almacena la última posición de la lista.

    if (lastPos == MAX - 1) return false;  // La inserción no es posible por falta de tamaño.
    if (p == LNULL) p = lastPos + 1;  // Con p = LNULL, inserción al final de la lista.

    // Bucle para mover los elementos a la derecha y abrir espacio para el nuevo elemento.
    for (tPosL i = lastPos; i >= p; i--) { // i: variable para recorrer posiciones en la lista.
        L->data[i + 1] = L->data[i];
    }

    L->data[p] = d; // Asigna el nuevo dato en la lista.
    L->lastPos += 1; // Aumenta el tamaño de la lista.
    return true;
}