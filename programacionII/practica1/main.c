/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 13 / 03 / 26
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

/* Objetivo: Calcular un porcentaje a partir de dos enteros.
 * Entradas:
 *   - part: Número de casos sobre los que calcular el porcentaje.
 *   - total: Número total de casos.
 * Salida: El porcentaje en un número tipo float.
 * Precondiciones: Las entradas son números int válidos.
 * Postcondiciones: Ninguna postcondición.
 */

float calcPercentage(int part, int total) {
    if (total == 0) return 0.0;
    return (float)part / (float)total * 100;
}

/* Objetivo: Incorporar un proyecto al final de la lista de proyectos.
 * Entradas:
 *   - list: Puntero a la lista de proyectos
 *   - projectName: Nombre del nuevo proyecto
 *   - projectEco: Array de caracteres que indica si un proyecto es o no eco.
 * Salidas: 
 *   - Valor booleano indicando si se ha podido ejecutar el comando con éxito.
 *   - Un nuevo elemento al final de la lista de proyectos.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Los votos quedarán inicializados a 0.
 */

bool new(tList* list, char* projectName, char* projectEco) {

    /* Prevención contra elementos duplicados, comprobando si la lista está vacía
     * para cumplir con la precondición de findItem */
    if (!isEmptyList(*list) && (findItem(projectName, *list) != LNULL)) {
        return false;
    }

    /* Creación del nuevo elemento a insertar e inicialización del mismo */
    tItemL newItem;
    strcpy(newItem.projectName, projectName);
    newItem.projectEco = strcmp(projectEco, "eco") == 0;
    newItem.numVotes = 0;

    /* Inserción del nuevo item en la lista e impresión del mensaje de éxito o error */
    if (!insertItem(newItem, LNULL, list)) {
        return false;
    } else {
        printf("* New: project %s category %s\n", projectName, projectEco);
        return true;
    }
}

/* Objetivo: Aumentar en uno el contador de votos del proyecto indicado.
 * Entradas:
 *   - list: Puntero a la lista de proyectos.
 *   - nullVotes: Puntero al contador global de votos nulos.
 *   - totalVotes: Puntero al contador global de votos totales.
 *   - projectName: Nombre del proyecto en el que se quiere votar.
 * Salidas: 
 *   - Valor booleano indicando si se ha podido ejecutar el comando con éxito.
 *   - Proyecto de la lista de proyectos actualizado en el caso de un comando exitoso.
 *   - Contador de votos totales aumentado en uno en el caso de un comando exitoso.
 *   - Contador de votos nulos aumentado en uno en el caso de un comando fallido.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Si no existe el proyecto o si la lista está vacía, el voto contará como nulo.
 */

bool vote(tList* list, int* nullVotes, int* totalVotes, char* projectName) {

    /* Si la lista está vacía, contabilizar el voto como nulo */
    if (isEmptyList(*list)) {
        (*nullVotes)++;
        return false;
    }

    /* Búsqueda del elemento en la lista */
    tPosL itemPos;
    itemPos = findItem(projectName, *list);

    /* Si el elemento no se ha encontrado, contabilizar como nulo el voto */
    if (itemPos == LNULL) {
        (*nullVotes)++;
        return false;
    }

    /* Modificación del item en la lista */
    tItemL item;
    item = getItem(itemPos, *list);
    item.numVotes++;
    updateItem(item, itemPos, list);

    /* Contabilizar el voto como válido en el contador general */
    (*totalVotes)++;

    /* Impresión del mensaje de éxito */
    printf("* Vote: project %s category %s numvotes %d\n", 
        projectName, 
        item.projectEco ? "eco" : "non-eco",
        item.numVotes
    );

    return true;
}

/* Objetivo: Eliminar un proyecto de la lista de proyectos.
 * Entradas:
 *   - list: Puntero a la lista de proyectos.
 *   - nullVotes: Puntero al contador global de votos nulos.
 *   - totalVotes: Puntero al contador global de votos totales.
 *   - projectName: Nombre del proyecto en que se quiere descalificar.
 * Salidas: 
 *   - Valor booleano indicando si se ha podido ejecutar el comando con éxito.
 *   - Proyecto de la lista de proyectos eliminado en el caso de un comando exitoso.
 *   - Contador de votos totales disminuído en el caso de un comando exitoso.
 *   - Contador de votos nulos aumentado en el caso de un comando exitoso.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Los votos del proyecto descalificado serán contabilizados como nulos.
 */

bool disqualify(tList* list, int* nullVotes, int* totalVotes, char* projectName) {

    /* Comprobación ante listas vacías */
    if (isEmptyList(*list)) {
        return false;
    }

    /* Búsqueda del elemento en la lista */
    tPosL itemPos;
    itemPos = findItem(projectName, *list);

    /* Comprobación ante elemento no encontrado */
    if (itemPos == LNULL) {
        return false;
    }

    /* Obtención del item */
    tItemL item;
    item = getItem(itemPos, *list);

    /* Pasar sus votos a nulos en los contadores globales */
    (*nullVotes) += item.numVotes;
    (*totalVotes) -= item.numVotes;

    /* Descalificación del elemento eliminandolo de la lista */
    deleteAtPosition(itemPos, list);

    /* Impresión del mensaje de éxito */
    printf("* Disqualify: project %s category %s\n", 
        projectName, 
        item.projectEco ? "eco" : "non-eco"
    );
    return true;
}

/* Objetivo: Mostrar todos los proyectos y estadísticas individuales y globales acerca de los votos.
 * Entradas:
 *   - list: Puntero a la lista de proyectos.
 *   - nullVotes: Puntero al contador global de votos nulos.
 *   - totalVotes: Puntero al contador global de votos totales.
 *   - voters: Número de evaluadores (votantes) de los proyectos.
 * Salidas: 
 *   - Valor booleano indicando si se ha podido ejecutar el comando con éxito.
 *   - Mensajes indicando las características y estadísticas de cada proyectos y las globales.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Ninguna postcondición.
 */

bool stats(tList list, int nullVotes, int totalVotes, char* voters) {

    /* Comprobación ante listas vacías */
    if (isEmptyList(list)) {
        return false;
    }

    tItemL item;  // item: variable auxiliar para almacenar los elementos al recorrer la lista

    /* Bucle para recorrer toda la lista e imprimir las estadísticas de cada elemento */
    for (tPosL p = first(list); p != LNULL; p = next(p, list)) {
        item = getItem(p, list);  // Obtener el contenido elemento en la lista

        /* Impresión de las estadísticas de cada elemento individual */
        printf("Project %s category %s numvotes %d (%.2f%%)\n",
               item.projectName,
               (item.projectEco) ? "eco" : "non-eco",
               item.numVotes,
               calcPercentage(item.numVotes, totalVotes));
    }

    /* Impresión de los resultados generales */
    printf("Null votes %d\n", nullVotes);
    printf("Participation: %d votes from %s evaluators (%.2f%%)\n",
           totalVotes + nullVotes,
           voters,
           calcPercentage(totalVotes + nullVotes, atoi(voters)));

    return true;
}

void processCommand(tList* list, int* nullVotes, int* totalVotes, char* commandNumber, char command, char* param1, char* param2) {

    /* Impresión de la decoración de la cabecera del comando */
    printf("********************\n");

    switch (command) {

        case 'N':
            /* Impresión de la cabecera del comando */
            printf("%s %c: project %s category %s\n", commandNumber, command, param1, param2);

            /* Impresión del mensaje de error en caso de ejecución errónea del comando */
            if (!new(list, param1, param2)) {
                printf("+ Error: New not possible\n");
            }
            break;

        case 'V':

            /* Impresión de la cabecera del comando */
            printf("%s %c: project %s\n", commandNumber, command, param1);

            /* Impresión del mensaje de error en caso de ejecución errónea del comando */
            if (!vote(list, nullVotes, totalVotes, param1)) {
                printf("+ Error: Vote not possible. Project %s not found. NULLVOTE\n", param1);
            }
            break;

        case 'D':

            /* Impresión de la cabecera del comando */
            printf("%s %c: project %s\n", commandNumber, command, param1);

            /* Impresión del mensaje de error en caso de ejecución errónea del comando */
            if (!disqualify(list, nullVotes, totalVotes, param1)) {
                printf("+ Error: Disqualify not possible\n");
            }
            break;

        case 'S':

            /* Impresión de la cabecera del comando */
            printf("%s %c: totalevaluators %s\n", commandNumber, command, param1);

            /* Impresión del mensaje de error en caso de ejecución errónea del comando */
            if (!stats(*list, *nullVotes, *totalVotes, param1)) {
                printf("+ Error: Stats not possible\n");
            }

            break;

        default:
            break;
    }
}

void readTasks(char* filename, tList* list, int* nullVotes, int* totalVotes) {
    FILE* f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(list, nullVotes, totalVotes, commandNumber, command[0], param1, param2);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char** args) {
    char* file_name = "new.txt";

    /* Creación e inicialización de la lista para
     * guardar los proyectos solicitados. */
    static tList list;
    createEmptyList(&list);

    /* Contador para los votos nulos */
    int nullVotes = 0;

    /* Contador para los votos totales usado para el cálculo
     * de las estadísticas. */
    int totalVotes = 0;

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &list, &nullVotes, &totalVotes);
    return 0;
}