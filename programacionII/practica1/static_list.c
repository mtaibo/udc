/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "static_list.h"

/*
 * Esta es una forma de llamar a la función
 * que crea las EmptyList, cuando hacemos tList lista;
 * lo que estamos haciendo es reservar espacio en memoria
 * para el struct tList, pero en la memoria habrá basura.
 * Para decir que esa lista es vacía, se tendrá que declarar
 * que la última posición de la lista es LNULL, es decir,
 * que la lista no tiene posiciones o lo que es lo mismo,
 * es una lista vacía.
 *
 * Se pasa &lista de esta forma porque la función pretende
 * modificar el array y necesita la dirección de memoria.
 *
 * tList lista;
 * createEmptyList(&lista);
*/

void createEmptyList (tList *L) {
  L -> lastPos = LNULL; // Con esta flecha estamos haciendo (*L).lastPos
}

bool isEmptyList (tList *L) {
  return (L -> lastPos == LNULL);
}
