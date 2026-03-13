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

void printHeader(char* commandNumber, char command, char* param1, char* param2) {

    /* Impresión de la decoración de la cabecera del comando */
    printf("********************\n");

    /* Impresión de la cabecera del comando correspondiente */
    switch (command) {
        case 'N': printf("%s %c: project %s category %s\n", commandNumber, command, param1, param2); break;
        case 'V': printf("%s %c: project %s\n", commandNumber, command, param1); break;
        case 'D': printf("%s %c: project %s\n", commandNumber, command, param1); break;
        case 'S': printf("%s %c: totalevaluators %s\n", commandNumber, command, param1); break;
        default: break;
    }
}

void printError(char command, char* param1, char* param2) {

    /* Impresión del error correspondiente a cada comando*/
    switch(command) {
        case 'N': printf("+ Error: New not possible\n"); break;
        case 'V': printf("+ Error: Vote not possible. Project %s not found. NULLVOTE\n", param1); break;
        case 'D': printf("+ Error: Vote not possible. Project %s not found. NULLVOTE\n", param1); break;
        case 'S': printf("+ Error: Stats not possible\n"); break;
        default: break;
    }
}

float calcPercentage(int cases, int total) {

    if (total == 0) return 0.0;
    return (float) cases / (float) total * 100;
}

void new(tList list, int nullVotes, int totalVotes, char* commandNumber, char command, char* param1, char* param2) {

    /* Creación del nuevo elemento a insertar */
    tItemL newItem;
    strcpy(newItem.projectName, param1);
    newItem.numVotes = 0;
    newItem.projectEco = (strcmp(param2, "eco") == 0);

    /* Prevención contra elementos duplicados con comprobación de lista vacía 
     * para cumplir con la precondición de findItem */
    if (!isEmptyList(list) && (findItem(newItem.projectName, list) != LNULL)) {
        printError(command, param1, param2);
    }

    /* Inserción del elemento en la lista, con comprobación ante errores de inserción */
    else if (!insertItem(newItem, LNULL, &list)) printError(command, param1, param2);
    else printf("* New: project %s category %s\n", param1, param2);
}

void vote(tList list, int nullVotes, int totalVotes, char* commandNumber, char command, char* param1, char* param2) {


    /* Comprobación ante listas vacías, en ese caso, imprimir mensaje de error 
     * y contabilizar el voto como nulo */
    if (isEmptyList(list)) {
        printError(command, param1, param2);
        nullVotes++;
    }

    /* Búsqueda del elemento en la lista al que se quiere añadir un voto */
    tPosL itemPos;
    itemPos = findItem(param1, list);

    /* Comprobación de si la búsqueda del elemento lo ha encontrado,
     * en caso de no encontrarlo, imprimir mensaje de error y contabilizar el voto como nulo */
    if (itemPos != LNULL) {

        /* Obtención del item que se quiere actualizar sumando un voto */
        tItemL item;
        item = getItem(itemPos, list);

        /* Aumento de un voto dentro del item y actualización del mismo en la lista */
        item.numVotes++;
        updateItem(item, itemPos, &list);

        /* Aumento de votos en el contador global de votos */
        totalVotes++;

        /* Impresión del resultado satisfactorio del comando procesado */
        printf("* Vote: project %s category %s numvotes %d\n", 
            param1, 
            (item.projectEco) ? "eco" : "non-eco", 
            item.numVotes
        );

    } else {
        printError(command, param1, param2);
        nullVotes++;
    }

}

void disqualify(tList list, int nullVotes, int totalVotes, char* commandNumber, char command, char* param1, char* param2) {

    /* Comprobación ante listas vacías */
    if (isEmptyList(list)) {
        printError(command, param1, param2);
        return;
    }

    /* Búsqueda del elemento en la lista que se quiere descalificar */
    tPosL itemPos;
    itemPos = findItem(param1, list);

    /* Comprobación de si la búsqueda del elemento lo ha encontrado,
     * en caso de no encontrarlo, imprimir mensaje de error */
    if (itemPos != LNULL) {

        /* Obtención del item que se quiere descalificar */
        tItemL item;
        item = getItem(itemPos, list);

        /* Contabilización de sus votos como nulos y eliminarlos 
         * de los votos totales antes de descalificarlo */
        nullVotes += item.numVotes;
        totalVotes -= item.numVotes;

        /* Descalificación del elemento eliminandolo de la lista */
        deleteAtPosition(itemPos, &list);

        /* Impresión del resultado satisfactorio del comando procesado */
        printf("* Disqualify: project %s category %s\n", 
            param1, 
            (item.projectEco) ? "eco" : "non-eco"
        );

    } else printError(command, param1, param2);
}

void stats(tList list, int nullVotes, int totalVotes, char* commandNumber, char command, char* param1, char* param2) {

    /* Comprobación ante listas vacías */
    if (isEmptyList(list)) {
        printError(command, param1, param2);
        return;
    }

    tItemL item; // item: variable para obtener el elemento al recorrer la lista

    /* Bucle para recorrer toda la lista para imprimir las estadísticas de cada elemento */
    for (tPosL p = first(list); p != LNULL; p = next(p, list)) {

        item = getItem(p, list); // Obtener el contenido elemento en la lista

        /* Impresión de las estadísticas de cada elemento individual */
        printf("Project %s category %s numvotes %d (%.2f%%)\n",
            item.projectName,
            (item.projectEco) ? "eco" : "non-eco",
            item.numVotes,
            calcPercentage(item.numVotes, totalVotes)
        );
    }

    /* Impresión de los votos nulos */
    printf("Null votes %d\n", nullVotes);

    /* Impresión de la participación general */
    printf("Participation: %d votes from %s evaluators (%.2f%%)\n",
        totalVotes+nullVotes,
        param1,
        calcPercentage(totalVotes+nullVotes, atoi(param1))
    );
}

void processCommand(tList list, int nullVotes, int totalVotes, char* commandNumber, char command, char* param1, char* param2) {

    /* Impresión de la cabecera */
    printHeader(commandNumber, command, param1, param2);

    /* Redirección según el comando a la función correspondiente */
    switch (command) {
        case 'N': new(list, nullVotes, totalVotes, commandNumber, command, param1, param2); break;
        case 'V': vote(list, nullVotes, totalVotes, commandNumber, command, param1, param2); break;
        case 'D': disqualify(list, nullVotes, totalVotes, commandNumber, command, param1, param2); break;
        case 'S': stats(list, nullVotes, totalVotes, commandNumber, command, param1, param2); break;
        default: break;
    }
}

void readTasks(char* filename, tList list, int nullVotes, int totalVotes) {
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

    readTasks(file_name, list, nullVotes, totalVotes);
    return 0;
}