/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 10 / 04 / 26
 */

#include "committee_list.h"

#include <string.h> // Librería que incluye el strcmp() para comparar nombres de proyectos.
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

tPosC lastC(tListC L) {
    return (L.lastPos);
}

tPosC nextC(tPosC p, tListC L) {
    return (p == lastC(L)) ? NULLC : p + 1;
}

tPosC previousC(tPosC p, tListC L) {
    return (p == 0) ? NULLC : p - 1;
}

tItemC getItemC(tPosC p, tListC L) {
    return L.data[p];
}

tPosC findItemC(tCommitteeName n, tListC L) {

    tPosC p; // p: Variable para recorrer las posiciones de la lista y almacenar la posición final.

    // Bucle que recorre la lista con p hasta que el nombre buscado esté alfabéticamente por debajo del actual.
    for (p = firstC(L); (p != NULLC) && (strcmp(getItemC(p, L).committeeName, n) < 0); p = nextC(p, L));

    // Comprobación final para determinar el motivo de la parada del bucle y devolver la posición consecuente.
    if (p != NULLC && strcmp(getItemC(p, L).committeeName, n) == 0) return p;
    return NULLC;
}

void updateItemC(tItemC d, tPosC p, tListC *L) {
    L->data[p] = d;
}

void deleteAtPositionC(tPosC p, tListC *L) {

    // Bucle para mover los elementos a la izquierda para cerrar el espacio generado al eliminar un elemento.
    for (tPosC i = p; i < lastC(*L); i++) { // i: variable para recorrer posiciones en la lista.
        L->data[i] = L->data[i + 1];
    } 
    
    L->lastPos--;  // Reduce el tamaño de la lista.
}

bool insertItemC(tItemC d, tListC *L) {
 
    tPosC p;
 
    if (lastC(*L) == MAX - 1) return false;  // La inserción no es posible por falta de tamaño.

    if (isEmptyListC(*L)) { // Inserción en lista vacía

        updateItemC(d, firstC(*L), L);

    } else { // Inserción en lista no vacía

        // Buscamos la posición donde se debe insertar
        for (p = firstC(*L); (nextC(p, *L) != NULLC) && (strcmp(getItemC(p, *L).committeeName, d.committeeName) < 0); p = nextC(p, *L)); 

        if (strcmp(getItemC(p, *L).committeeName, d.committeeName) < 0) updateItemC(d, p+1, L); // Inserción en el final de la lista

        else { // Inserción en posición intermedia

            // Bucle para mover los elementos a la derecha y abrir espacio para el nuevo elemento.
            for (tPosC i = lastC(*L); i >= p; i--) { // i: variable para recorrer posiciones en la lista.
                L->data[i + 1] = L->data[i];
            }

            L->data[p] = d; // Asigna el nuevo dato en la lista.
        }
    }

    L->lastPos += 1; // Aumenta el tamaño de la lista.

    return true;
}