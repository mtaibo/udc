/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 23 / 02 / 26
 */

#include "static_list.h"

// Esta función crea una lista vacía simplemente definiendo
// la última posición de la lista como LNULL, dejándola así
// "vacía", aunque el array del data tenga contenido residual.
//
// Esta función tiene una PostCondición que implica que cuando
// a la lista se le pone la lastPos en LNULL, no tendrá elementos.
void createEmptyList(tList* L) {
    L->lastPos = LNULL;  // Con esta flecha estamos haciendo (*L).lastPos
}

// Esta función únicamente controla si la función está o no
// vacía en función de la última posición, que en el
// caso de ser la posición LNULL estará vacía y devolverá true.
bool isEmptyList(tList L) {
    return (L.lastPos == LNULL);
}

// Esta función devuelve la primera posición de la lista
// Como precondición, la lista que se le envíe a esta función
// no puede ser una lista vacía, por lo que no es necesario comprobar
// si la primera posición es LNULL para devolver el 0.
tPosL first(tList L) {
    return 0;
}

// Esta función devuelve la última posición de la lista
// accediendo a la propiedad lastPos del struct tList L
// Al igual que en la función anterior, la lista será no vacía
// siempre como precondición, por lo que la lastPos nunca será LNULL.
tPosL last(tList L) {
    return (L.lastPos);
}

// Esta función devuelve el siguiente elemento a p en la lista L
// que se le pasa a la función. En el caso de que la posición
// enviada como atributo a esta función sea la última, devuelve LNULL
// Como precondición, esta función recibe solo posiciones p válidas en L.
tPosL next(tPosL p, tList L) {
    return (p == last(L)) ? LNULL : p + 1;
}

// Esta función es la inversa a la de next, devuelve el elemento
// anterior a p en la lista L que se le pasa a la función. Si la
// posición ya es la primera, se devuelve LNULL.
// Al igual que en la función anterior, esta función solo recibe
// posiciones p válidas en la lista L.
tPosL previous(tPosL p, tList L) {
    return (p == 0) ? LNULL : p - 1;
}

// Esta función obtiene un elemento tItemL de la lista
// que se encuentra en la posición p. Simplemente accede
// a la lista L y en el array de data devuelve la posición p.
// De nuevo, esta función solo recibe posiciones p válidas en L.
// No es necesario una verificación de la validez de p.
tItemL getItem(tPosL p, tList L) {
    return L.data[p];
}

// Esta función encuentra el primer ítem cuyo tProjectName sea n
// dentro de la lista L y devuelve su posición dentro de la lista.
// Esto se realiza mediante un bucle que recorre toda la lista
// mediante first(L) y mediante next(i,L) y su salida, esperando a
// que sea LNULL para parar el bucle. En cada posición que itera
// el bucle, se entrará dentro del item correspondiente a esa posición
// con getItem(i,L) y a su atributo correspondiente projectName para
// comprobar mediante strcmp() si ese item y n son iguales. En caso
// afirmativo, se devolverá la posición i de ese item dentro de L.
// Si no se encuentra ese valor en toda la lista, se devuelve LNULL.
tPosL findItem(tProjectName n, tList L) {
    for (tPosL i = first(L); i != LNULL; i = next(i, L)) {
        if (strcmp(getItem(i, L).projectName, n) == 0)
            return i;
    }
    return LNULL;
}

// Esta función simplemente actualiza el valor del elemento p
// de la lista L con el valor de d, accediendo a la lista L que
// fue pasada a la función como puntero para poder modificarla.
// La posición p será una posición válida en la lista, y en esta
// función, el orden de la lista no se verá modificado después
// de actualizar el valor de un item.
void updateItem(tItemL d, tPosL p, tList* L) {
    L->data[p] = d;
}

// Esta función se encarga de eliminar el elemento de la lista L
// que se encuentra en la posición p. Para poder borrar un elemento,
// sin dejar huecos en el medio de la lista, se deberá reestructurar
// todos los elementos posteriores al elemento que se quiere eliminar,
// moviendolos una posición hacia atrás en la lista. Para reducir el
// tamaño después de mover los elementos, se reduce la lastPos en 1.
// Como precondición, esta función recibe solo posiciones p válidas en L.
// Después de aplicar esta función, las posiciones de los valores
// posteriores a p pueden haber variado.
void deleteAtPosition(tPosL p, tList* L) {
    tPosL lastPos = last(*L);  // Esto ahorra tener que llamar a last(*L) en cada iteración del bucle
    for (tPosL i = p; i < lastPos; i++) {
        L->data[i] = L->data[i + 1];  // Sobreescribe la posición actual con la siguiente
    }
    L->lastPos -= 1;  // Reduce el tamaño de la lista en 1
}

// Esta función se encarga de añadir un item d a la lista L en una
// posición p, y devolverá true si fue insertado correctamente, y false
// de lo contrario. Para insertar un nuevo elemento, se debe tener en cuenta
// el desplazamiento de los elementos ya existentes como en la función anterior,
// para ello encontramos un bucle que empezará en la última posición e irá moviendo
// los items de la lista a la siguiente posición hasta llegar a la posición deseada.
// Al llegar a esa posición, introducirá el nuevo valor d, incrementará la última
// posición en 1 y devolverá true.
//
// Para la posición p, en el caso de ser LNULL, el elemento será añadido al final
// de la lista, por lo que simplemente se añadirá el elemento en lastPos+1, y
// posteriormente se incrementará lastPos en 1.
//
// Para prevenir un acceso al array en una posición no existente, antes de nada
// se comprueba si la lastPos de la lista ya es el máximo permitido y no se puede
// añadir ningún elemento más a la lista por falta de espacio en memoria.
//
// La posición p que recibe esa función será una posición válida en L como precondición,
// y las posiciones de los elementos posteriores a p en la lista pueden verse modificados.
bool insertItem(tItemL d, tPosL p, tList* L) {
    tPosL lastPos = last(*L);

    if (lastPos == MAX - 1)
        return false;  // Comprobación de si la lista es apta para añadir un elemento
    if (p == LNULL)
        p = lastPos + 1;  // Si p == LNULL, la posición para añadir el elemento será al final

    // Bucle para mover los elementos posteriores a p y hacerle hueco en el array
    for (tPosL i = lastPos; i >= p; i--) {
        L->data[i + 1] = L->data[i];
    }

    // Insertar el nuevo elemento en la posición p,
    // incrementar el tamaño del array y devolver true
    L->data[p] = d;
    L->lastPos += 1;
    return true;
}