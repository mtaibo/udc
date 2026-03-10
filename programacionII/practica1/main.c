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

/* Definición de variables globales, tanto la lista de proyectos, 
 * como las variables para la contabilización de votos y la estadística posterior */
tList L;
int nullVotes = 0;
int totalVotes = 0;


void processCommand(char* commandNumber, char command, char* param1, char* param2) {

    /* Impresión de la cabecera */
    printf("********************\n");

    switch (command) {

        case 'N': {

            /* Impresión del comando que se va a procesar */
            printf("%s %c: project %s category %s\n", commandNumber, command, param1, param2);

            /* Creación del nuevo elemento a insertar */
            tItemL newItem;
            strcpy(newItem.projectName, param1);
            newItem.numVotes = 0;
            newItem.projectEco = (strcmp(param2, "eco") == 0);

            /* Prevención contra elementos duplicados con comprobación de lista vacía 
             * para cumplir con la precondición de findItem */
            if (!isEmptyList(L) && (findItem(newItem.projectName, L) != LNULL)) {
                printf("+ Error: New not possible\n"); break;
            }

            /* Inserción del elemento en la lista, con comprobación ante errores de inserción */
            else if (!insertItem(newItem, LNULL, &L)) printf("+ Error: New not possible\n");
            else printf("* New: project %s category %s\n", param1, param2);

            break;
        }

        case 'V': {

            /* Impresión del comando que se va a procesar */
            printf("%s %c: project %s\n", commandNumber, command, param1);

            /* Comprobación ante listas vacías, en ese caso, imprimir mensaje de error 
             * y contabilizar el voto como nulo */
            if (isEmptyList(L)) {
                printf("+ Error: Vote not possible. Project %s not found. NULLVOTE\n", param1);
                nullVotes++;
            }

            /* Búsqueda del elemento en la lista al que se quiere añadir un voto */
            tPosL itemPos;
            itemPos = findItem(param1, L);

            /* Comprobación de si la búsqueda del elemento lo ha encontrado,
             * en caso de no encontrarlo, imprimir mensaje de error y contabilizar el voto como nulo */
            if (itemPos != LNULL) {

                /* Obtención del item que se quiere actualizar sumando un voto */
                tItemL item;
                item = getItem(itemPos, L);

                /* Aumento de un voto dentro del item y actualización del mismo en la lista */
                item.numVotes++;
                updateItem(item, itemPos, &L);

                /* Aumento de votos en el contador global de votos */
                totalVotes++;

                /* Impresión del resultado satisfactorio del comando procesado */
                printf("* Vote: project %s category %s numvotes %d\n", 
                    param1, 
                    (item.projectEco) ? "eco" : "non-eco", 
                    item.numVotes
                );

            } else {
                printf("+ Error: Vote not possible. Project %s not found. NULLVOTE\n", param1);
                nullVotes++;
            }
            
            break;
        }

        case 'D': {

            /* Impresión del comando que se va a procesar */
            printf("%s %c: project %s\n", commandNumber, command, param1);

            /* Comprobación ante listas vacías */
            if (isEmptyList(L)) {
                printf("+ Error: Disqualify not possible\n");
                break;
            }

            /* Búsqueda del elemento en la lista que se quiere descalificar */
            tPosL itemPos;
            itemPos = findItem(param1, L);

            /* Comprobación de si la búsqueda del elemento lo ha encontrado,
             * en caso de no encontrarlo, imprimir mensaje de error */
            if (itemPos != LNULL) {

                /* Obtención del item que se quiere descalificar */
                tItemL item;
                item = getItem(itemPos, L);

                /* Contabilización de sus votos como nulos y eliminarlos 
                 * de los votos totales antes de descalificarlo */
                nullVotes += item.numVotes;
                totalVotes -= item.numVotes;

                /* Descalificación del elemento eliminandolo de la lista */
                deleteAtPosition(itemPos, &L);

                /* Impresión del resultado satisfactorio del comando procesado */
                printf("* Disqualify: project %s category %s\n", 
                    param1, 
                    (item.projectEco) ? "eco" : "non-eco"
                );

            } else printf("+ Error: Disqualify not possible\n");

            break;
        }

        case 'S': {

            /* Impresión del comando que se va a procesar */
            printf("%s %c: totalevaluators %s\n", commandNumber, command, param1);

            /* Comprobación ante listas vacías */
            if (isEmptyList(L)) {
                printf("+ Error: Stats not possible\n");
                break;
            }

            tItemL item; // item: variable para obtener el elemento al recorrer la lista

            /* Bucle para recorrer toda la lista para imprimir las estadísticas de cada elemento */
            for (tPosL p = first(L); p != LNULL; p = next(p, L)) {

                item = getItem(p, L); // Obtener el contenido elemento en la lista

                /* Impresión de las estadísticas de cada elemento individual */
                printf("Project %s category %s numvotes %d (%.2f%%)\n",
                    item.projectName,
                    (item.projectEco) ? "eco" : "non-eco",
                    item.numVotes,
                    /* Cálculo del porcentaje de votos con los votos del proyecto respecto al total de votos de proyectos */
                    (totalVotes == 0) ? 0.0 : ((float) item.numVotes / (float) totalVotes) * 100
                );
            }

            /* Impresión de los votos nulos */
            printf("Null votes %d\n", nullVotes);

            /* Impresión de la participación general */
            printf("Participation: %d votes from %s evaluators (%.2f%%)\n",
                totalVotes+nullVotes,
                param1,
                /* Cálculo del porcentaje de participación respecto a los votos totales (incluyendo nulos) respecto al número de votantes */
                (atoi(param1) == 0) ? 0.0: ((float) (totalVotes + nullVotes) / atoi(param1)) * 100
            );

            break;
        }

        default:
            break;
    }
}

void readTasks(char* filename) {
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

            processCommand(commandNumber, command[0], param1, param2);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char** args) {
    char* file_name = "new.txt";

    /* Inicializar la lista vacía al inicio de la ejecución 
     * del programa para evitar memoria residual */
    createEmptyList(&L);

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
            file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}