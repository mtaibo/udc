/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Taibo Pérez LOGIN 1: miguel.taibo.perez@udc.es
 * AUTHOR 2: Marcos Estévez Besada LOGIN 2: marcos.estevez1@udc.es
 * GROUP: 2.1
 * DATE: 24 / 04 / 26
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "committee_list.h"

#define MAX_BUFFER 255


/* Objetivo: Calcular un porcentaje a partir de dos enteros.
 * Entradas:
 *   - part: Número de casos sobre los que calcular el porcentaje.
 *   - total: Número total de casos.
 * Salida: El porcentaje en un número tipo float.
 * Precondiciones: Ninguna precondición.
 * Postcondiciones: Ninguna postcondición.
 */

float calculatePercentage(int part, int total) {
    return (total > 0 ? part / (float) total * 100 : 0.0);
}


/* Objetivo: Incorporar el comité con el nombre y el número de evaluadores indicado a la lista.
 * Entradas:
 *   - committeeList: Puntero a la lista de comités.
 *   - committeeName: Nombre del nuevo comité a añadir.
 *   - totalEvaluators: Número de evaluadores del nuevo comité a añadir.
 * Salida: La lista de comités con el nuevo comité indicado.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: El nuevo comité tendra los votos válidos y nulos a 0.
 */

void create(tListC* committeeList, char* committeeName, char* totalEvaluators) {

    if (findItemC(committeeName, *committeeList) == NULLC) {  // Prevención contra comités duplicados

        tItemC newCommittee;

        /* Asignación de los valores iniciales al nuevo comité */
        strcpy(newCommittee.committeeName, committeeName);
        newCommittee.totalEvaluators = atoi(totalEvaluators);
        newCommittee.validVotes = 0;
        newCommittee.nullVotes = 0;
        createEmptyListP(&newCommittee.projectList);

        /* Inserción del nuevo comité en la lista e impresión del mensaje de satisfacción o error */
        if (!insertItemC(newCommittee, committeeList)) printf("+ Error: Create not possible\n");
        else printf("* Create: committee %s totalevaluators %s\n", committeeName, totalEvaluators);

    } else printf("+ Error: Create not possible\n");
}


/* Objetivo: Dar de alta un nuevo proyecto en el comité indicado.
 * Entradas:
 *   - committeeList: Puntero a la lista de comités.
 *   - committeeName: Nombre del comité donde se dará de alta el nuevo proyecto.
 *   - projectName: Nombre del nuevo proyecto a dar de alta.
 *   - projectEco: Categoría del nuevo proyecto a dar de alta.
 * Salida: La lista de comités con el comité indicado modificado con un nuevo proyecto.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: El nuevo proyecto tendrá 0 votos.
 */

void new(tListC* committeeList, char* committeeName, char* projectName, char* projectEco) {

    tPosC committeePos = findItemC(committeeName, *committeeList);

    if (committeePos != NULLC) { // Validación de la existencia del comité

        tItemC committee = getItemC(committeePos, *committeeList);

        if (findItemP(projectName, committee.projectList) == NULLP) { // Prevención contra proyectos duplicados

            tItemP newItem;

            /* Asignación de los valores iniciales al nuevo proyecto */
            strcpy(newItem.projectName, projectName);
            newItem.numVotes = 0;
            newItem.projectEco = strcmp(projectEco, "eco") == 0;

            /* Inserción del nuevo proyecto en la lista e impresión del mensaje de satisfacción o error */
            if (!insertItemP(newItem, &committee.projectList)) {
                printf("+ Error: New not possible\n");
            } else { 
                updateItemC(committee, committeePos, committeeList);
                printf("* New: committee %s project %s category %s\n", committeeName, projectName, projectEco);
            }

        } else printf("+ Error: New not possible\n");

    } else printf("+ Error: New not possible\n");
}


/* Objetivo: Mostrar estadísticas de voto y participación para cada comité y sus proyectos.
 * Entradas:
 *   - committeeList: Lista de comités.
 * Salida: Mensajes indicando estadísticas de los votos y la participación en los comités y sus proyectos.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Ninguna postcondición.
 */

void stats(tListC committeeList) {

    if (!isEmptyListC(committeeList)) {

        /* Bucle para recorrer los comités */
        for (tPosC p = firstC(committeeList); p != NULLC; p = nextC(p, committeeList)) {

            tItemC committee = getItemC(p, committeeList);
            printf("Committee %s\n", committee.committeeName);

            if (!isEmptyListP(committee.projectList)) {

                /* Bucle para recorrer los proyectos de un comité */
                for (tPosP q = firstP(committee.projectList); q != NULLP; q = nextP(q, committee.projectList)) {

                    /* Obtención del proyecto e impresión de sus propiedades y estadísticas */
                    tItemP project = getItemP(q, committee.projectList);
                    printf("Project %s category %s numvotes %d (%.2f%%)\n",
                        project.projectName,
                        project.projectEco ? "eco" : "non-eco",
                        project.numVotes,
                        calculatePercentage(project.numVotes, committee.validVotes)
                    );
                }

            } else printf("No projects\n");

            /* Impresión de las estadísticas generales del comité */
            printf("Nullvotes %d\n", committee.nullVotes);
            printf("Participation: %d votes from %d evaluators (%.2f%%)\n\n", 
                committee.validVotes + committee.nullVotes, 
                committee.totalEvaluators, 
                calculatePercentage(committee.validVotes + committee.nullVotes, committee.totalEvaluators)
            );
        }

    } else printf("+ Error: Stats not possible\n");
}


/* Objetivo: Añadir un voto al proyecto indicado del comité indicado.
 * Entradas:
 *   - committeeList: Puntero a la lista de comités.
 *   - committeeName: Nombre del comité donde se encuentra el proyecto que se quiere votar.
 *   - projectName: Nombre del proyecto al cuál se le quiere sumar un voto.
 * Salida: El proyecto indicado del comité indicado verá su número de votos incrementado en 1.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Si no se encuentra el proyecto dentro del comité indicado, el voto se contabilizará como nulo.
 */

void vote(tListC* committeeList, char* committeeName, char* projectName) {

    tPosC committeePos = findItemC(committeeName, *committeeList);

    if (committeePos != NULLC) { // Validación de la existencia del comité

        tItemC committee = getItemC(committeePos, *committeeList);
        tPosP projectPos = findItemP(projectName, committee.projectList);

        if (projectPos == NULLP) { // Contabilización del voto como nulo si no encontrado
            committee.nullVotes++;
            printf("+ Error: Vote not possible. Project %s not found in committee %s. NULLVOTE\n", projectName, committeeName);

        } else { // Contabilización del voto como válido si es encontrado

            tItemP project = getItemP(projectPos, committee.projectList);
            project.numVotes++;
            committee.validVotes++;
            updateItemP(project, projectPos, &committee.projectList);

            printf("* Vote: committee %s project %s category %s numvotes %d\n",
                committeeName,
                projectName,
                project.projectEco ? "eco" : "non-eco",
                project.numVotes
            );
        }

        /* Actualizar el comité, independientemente de como se contabilizó el voto */
        updateItemC(committee, committeePos, committeeList);

    } else printf("+ Error: Vote not possible\n");
}


/* Objetivo: Descalificar un proyecto de todos los comités.
 * Entradas:
 *   - committeeList: Puntero a la lista de comités.
 *   - projectName: Nombre del/los proyectos que se quieren descalificar.
 * Salida: Todos los comités donde se encuentre el proyecto indicado, tendrán ese proyecto eliminado de su lista.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Los votos de los proyectos eliminados serán contabilizados como nulos.
 */

void disqualify(tListC* committeeList, char* projectName) {

    if (!isEmptyListC(*committeeList)) {

        /* Bucle para recorrer todos los comités */
        for (tPosC p = firstC(*committeeList); p != NULLC; p = nextC(p, *committeeList)) {

            tItemC committee = getItemC(p, *committeeList);
            printf("Committee %s\n", committee.committeeName);
        
            tPosP projectPos = findItemP(projectName, committee.projectList);
            if (projectPos == NULLP) printf("No project %s\n\n", projectName);
            else {

                int votes = getItemP(projectPos, committee.projectList).numVotes;

                committee.validVotes -= votes;
                committee.nullVotes += votes;

                deleteAtPositionP(projectPos, &committee.projectList);
                updateItemC(committee, p, committeeList);

                printf("Project %s disqualified\n\n", projectName);
            }
        }

    } else printf("+ Error: Disqualify not possible\n");
}


/* Objetivo: Eliminar los comités con 0 votos válidos.
 * Entradas:
 *   - committeeList: Puntero a la lista de comités.
 * Salida: La lista de comités con todos los comités con 0 votos válidos elminados.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Ninguna postcondición.
 */

void removeInactiveCommittees(tListC* committeeList) {

    bool removed = false; // removed: Variable para detectar si se ha eliminado algún elemento o no.

    if (!isEmptyListC(*committeeList)) {

        tPosC p = firstC(*committeeList);
        while (p != NULLC) { // Bucle while y no for para controlar manualmente cuando avanzar por la lista.

            tItemC committee = getItemC(p, *committeeList);

            if (committee.validVotes == 0) {

                /* Antes de borrar un comité, se debe librerar la memoria de la lista que contiene */
                while (!isEmptyListP(committee.projectList)) {
                    deleteAtPositionP(firstP(committee.projectList), &committee.projectList);
                }

                printf("* Remove: committee %s\n", committee.committeeName);
                deleteAtPositionC(p, committeeList); // En lista ordenada, cuando eliminas p, p apuntará al siguiente elemento.
                
                removed = true;

            } else p = nextC(p, *committeeList);
        }
    } 

    if (!removed) printf("+ Error: Remove not possible\n");
}


/* Objetivo: Mostrar los proyectos con más votos de cada categoría en cada comité evaluador.
 * Entradas:
 *   - committeeList: Puntero a la lista de comités.
 * Salida: Mensajes indicando los ganadores de cada categoría por cada comité.
 * Precondiciones: La lista debe estar inicializada.
 * Postcondiciones: Ninguna postcondición.
 */

void winners(tListC committeeList) {

    if (!isEmptyListC(committeeList)) {

        /* Bucle para recorrer los comités */
        for (tPosC p = firstC(committeeList); p != NULLC; p = nextC(p, committeeList)) {

            tItemC committee = getItemC(p, committeeList);
            tListP projectList = committee.projectList;

            /* Declaración de las variables para almacenar los ganadores */
            tItemP ecoWinner = {"", -1, true};
            tItemP nonEcoWinner = {"", -1, false};

            /* Declaración de los flags para saber si el ganador es válido */
            bool isAnyEcoWinner = false;
            bool isAnyNonEcoWinner = false;

            /* Bucle sobre la lista de proyectos de comité para buscar los ganadores */
            for (tPosP q = firstP(projectList); q != NULLP; q = nextP(q, projectList)) {

                tItemP project = getItemP(q, projectList);

                /* Comprobar si el proyecto actual es eco y debe ser ganador */
                if (project.projectEco) {

                    if (project.numVotes == ecoWinner.numVotes) isAnyEcoWinner = false;
                    else if (project.numVotes > ecoWinner.numVotes) {
                        ecoWinner = project;
                        isAnyEcoWinner = true;
                    }

                /* Comprobar si el proyecto actual es no-eco y debe ser ganador */
                } else {

                    if (project.numVotes == nonEcoWinner.numVotes) isAnyNonEcoWinner = false;
                    else if (project.numVotes > nonEcoWinner.numVotes) {
                        nonEcoWinner = project;
                        isAnyNonEcoWinner = true;
                    }
                }
            }

            printf("Committee %s\n", committee.committeeName);

            printf("Category eco: ");
            if (isAnyEcoWinner) printf("Project %s numvotes %d\n", ecoWinner.projectName, ecoWinner.numVotes);
            else printf("No winner\n");

            printf("Category non-eco: ");
            if (isAnyNonEcoWinner) printf("Project %s numvotes %d\n\n", nonEcoWinner.projectName, nonEcoWinner.numVotes);
            else printf("No winner\n\n");
        }

    } else printf("+ Error: Winners not possible");
}


void processCommand(tListC* committeeList, char *commandNumber, char command, char *param1,char *param2, char *param3) {

    printf("********************\n");

    switch (command) {
        case 'C':
            printf("%s %c: committee %s totalevaluators %s\n", commandNumber, command, param1, param2);
            create(committeeList, param1, param2);
            break;        

        case 'N':
            printf("%s %c: committee %s project %s category %s\n", commandNumber, command, param1, param2, param3);
            new(committeeList, param1, param2, param3);
            break;

        case 'S':
            printf("%s %c:\n", commandNumber, command);
            stats(*committeeList);
            break;

        case 'V':
            printf("%s %c: committee %s project %s\n", commandNumber, command, param1, param2);
            vote(committeeList, param1, param2);
            break;

        case 'D':
            printf("%s %c: project %s\n", commandNumber, command, param1);
            disqualify(committeeList, param1);
            break;

        case 'R':
            printf("%s %c:\n", commandNumber, command);
            removeInactiveCommittees(committeeList);
            break;

        case 'W':
            printf("%s %c:\n", commandNumber, command);
            winners(*committeeList);
            break;

        default:
            break;
    }
}

void readTasks(char *filename, tListC* committeeList) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(committeeList, commandNumber, command[0], param1, param2, param3);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "create.txt";

    tListC committeeList; // committeeList: Variable con la lista de comités

    /* Inicialización de la lista */
    createEmptyListC(&committeeList);

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name, &committeeList);

    /* Finalización del programa, liberación de toda la memoria */
    while (!isEmptyListC(committeeList)) {
        tItemC committee = getItemC(firstC(committeeList), committeeList);
        while (!isEmptyListP(committee.projectList)) {
            deleteAtPositionP(firstP(committee.projectList), &committee.projectList);
        } deleteAtPositionC(firstC(committeeList), &committeeList);
    }

    return 0;
}
