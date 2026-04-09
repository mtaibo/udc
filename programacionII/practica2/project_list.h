/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 10 / 04 / 26
 */

#ifndef PROJECT_LIST_H
#define PROJECT_LIST_H

#include "types.h"

/* Definición de constantes */
#define NULLP NULL /* Valor que representa una posición nula. */

/* Definición de tipos */
typedef struct tNode *tPosP; /* Tipo de dato de las posiciones de la lista, un puntero a un nodo. */
typedef tPosP tListP;        /* Definición de una lista, un puntero a su primer elemento. */

typedef struct tItemP {             /* Definición de la estructura que conforma cada elemento de la lista. */
    tProjectName projectName;       /* Nombre del proyecto. */
    tNumVotes numVotes;             /* Contador de votos. */
    tProjectEco projectEco;         /* Indicador de si un proyecto es ecológico. */
} tItemP;

typedef struct tNode { /* Definición de la estructura que conforma un nodo de la lista. */
    tItemP data;       /* Datos de un nodo de la lista. */
    tPosP next;        /* Siguiente nodo de la lista en orden. */
} tNode;


/* INICIALIZACIÓN DE LISTAS */

/* Objetivo: Crea una lista vacía.
 * Entradas:
 *   - L: Puntero a la lista que se quiere inicializar.
 * Salida: L, lista vacía inicializada.
 * Precondiciones: Ninguna precondición.
 * Postcondiciones: La lista queda inicializada y no contendrá elementos.
 */

void createEmptyListP(tListP* L);

/* Objetivo: Determina si la lista está vacía.
 * Entradas:
 *   - L: Lista a comprobar.
 * Salida: Valor booleano que indica si la lista está vacía (true) o no (false). 
 * Precondiciones: Ninguna precondición.
 * Postcondiciones: Ninguna postcondición.
 */

bool isEmptyListP(tListP L);


/* MOVIMIENTO A TRAVÉS DE LA LISTA */
 
/* Objetivo: Devuelve la posición del primer elemento de la lista.
 * Entradas:
 *   - L: Lista de la que se quiere el primer elemento.
 * Salida: Posición del primer elemento de la lista L.
 * Precondiciones: La lista no está vacía.
 * Postcondiciones: Ninguna postcondición.
 */

tPosP firstP(tListP L);

/* Objetivo: Devuelve la posición del último elemento de la lista.
 * Entradas:
 *   - L: Lista de la que se quiere el último elemento.
 * Salida: Posición del último elemento de la lista L.
 * Precondiciones: La lista no está vacía.
 * Postcondiciones: Ninguna postcondición.
 */

tPosP lastP(tListP L);

/* Objetivo: Devuelve la posición siguiente en la lista a una indicada, o LNULL si no hay posición siguiente.
 * Entradas:
 *   - p: Posición inidicada, de la que se quiere obtener la siguiente posición.
 *   - L: Lista sobre la que se encuentran la posición indicada y la siguiente solicitada.
 * Salida: Posición del siguiente elemento a la posición indicada, o LNULL si no hay posición siguiente.
 * Precondiciones: La posición indicada es una posición válida dentro de la lista.
 * Postcondiciones: Ninguna postcondición.
 */

tPosP nextP(tPosP p, tListP L);

/* Objetivo: Devuelve la posición anterior a la posición indicada, o LNULL si no hay posición anterior.
 * Entradas:
 *   - p: Posición indicada, de la que se quiere obtener la anterior posición.
 *   - L: Lista sobre la que se encuentran la posición indicada y la anterior solicitada.
 * Salida: Posición del anterior elemento a la posición indicada, o LNULL si no hay posición anterior.
 * Precondiciones: La posición indicada es una posición válida dentro de la lista.
 * Postcondiciones: Ninguna postcondición.
 */

tPosP previousP(tPosP p, tListP L);

/* MODIFICACIÓN DE LISTAS */

/* Objetivo: Insertar un elemento de forma ordenada en función del campo projectName.
 * Entradas:
 *   - d: Contenido del elemento a insertar.
 *   - p: Posición donde se quiere insertar el elemento en la lista.
 *   - L: Puntero a la lista donde se quiere insertar el elemento.
 * Salidas:
 *   - Valor booleano con valor true en el caso de que la inserción fuera correcta, y false si no se pudo producir la inserción.
 *   - La lista con el elemento insertado en la posición indicada en el caso de una inserción correcta.
 * Precondiciones: La posición indicada es una posición válida dentro de la lista, o la posición nula.
 * Postcondiciones: El orden de los elementos de la lista puede verse modificado, y la lista puede ver aumentado su tamaño.
 */

bool insertItemP(tItemP d, tListP* L);

/* Objetivo: Elimina de la lista el elemento en la posición indicada.
 * Entradas:
 *   - p: Posición del elemento que se quiere eliminar.
 *   - L: Puntero a la lista cuyo elemento se quiere eliminar.
 * Salidas: La lista con el elemento en la posición indicada eliminado.
 * Precondiciones: La posición indicada es una posición válida dentro de la lista.
 * Postcondiciones: El orden de los elementos de la lista puede verse modificado, y la lista verá reducido su tamaño.
 */

void deleteAtPositionP(tPosP p, tListP* L);

/* Objetivo: Modifica el contenido del elemento en la posición indicada con el nuevo contenido aportado en la lista dada.
 * Entradas:
 *   - d: Nuevo contenido del elemento que se quiere actualizar.
 *   - p: Posición del elemento que se quiere actualizar.
 *   - L: Puntero a la lista cuyo elemento se quiere actualizar.
 * Salida: La lista con el valor modificado.
 * Precondiciones: La posición indicada es una posición válida dentro de la lista.
 * Postcondiciones: El orden de los elementos de la lista no se ve modificado.
 */

void updateItemP(tItemP d, tPosP p, tListP* L);


/* BÚSQUEDA EN LAS LISTAS */

/* Objetivo: Obtener el contenido de una posición indicada en la lista indicada.
 * Entradas:
 *   - p: Posición indicada del elemento que se quiere obtener.
 *   - L: Lista donde se encuentra el elemento buscado en la posición indicada.
 * Salida: Contenido del elemento que se encuentra en la posición indicada de la lista dada.
 * Precondiciones: La posición indicada es una posición válida dentro de la lista.
 * Postcondiciones: Ninguna postcondición.
 */

tItemP getItemP(tPosP p, tListP L);

/* Objetivo: Obtiene el primer elemento de la lista cuyo nombre de proyecto coincide con el indicado.
 * Entradas:
 *   - n: Nombre del proyecto que se busca en la lista.
 *   - L: Lista donde se busca ese proyecto.
 * Salida: Posición en la lista del primer proyecto cuyo nombre coincide con el indicado (LNULL si no existe).
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Ninguna postcondición.
 */

tPosP findItemP(tProjectName n, tListP L);

#endif // PROJECT_LIST_H