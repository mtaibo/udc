/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "committee_list.h"

#define MAX_BUFFER 255


float calculatePercentage(int part, int total) {
    return (total > 0 ? part / (float) total * 100 : 0.0);
}


void create(tListC* committeeList, char* committeeName, char* totalEvaluators) {

    /* Prevención contra elementos duplicados, y comprobando si la lista
     * esta vacía para cumplir la precondición de findItemC */
    if (!isEmptyListC(*committeeList) && (findItemC(committeeName, *committeeList) != NULLC)) {
        printf("+ Error: Create not possible\n");
        return;
    }

    /* Creación del nuevo item y asignación de sus valores */
    tItemC newItem;

    strcpy(newItem.committeeName, committeeName);

    newItem.totalEvaluators = atoi(totalEvaluators);
    newItem.validVotes = 0;
    newItem.nullVotes = 0;

    tListP newProjectList;
    createEmptyListP(&newProjectList);

    newItem.projectList = newProjectList;

    if (!insertItemC(newItem, committeeList)) printf("+ Error: Create not possible\n");
    else printf("* Create: committee %s totalevaluators %s\n", committeeName, totalEvaluators);
    return;
}


////////// MEJORAR EFICIENCIA////////////
void new(tListC* committeeList, char* committeeName, char* projectName, char* projectEco) {

    tItemC itemToUpdate = getItemC(committeeName, *committeeList);
    tListP projectList = itemToUpdate.projectList;

    /* Prevención contra elementos duplicados, y comprobando si la lista
     * esta vacía para cumplir la precondición de findItemP */
    if (!isEmptyListP(projectList) && (findItemP(projectName, projectList) != NULLP)) {
        printf("+ Error: New not possible\n");
        return;
    }

    /* Creación del nuevo item y asignación de sus valores */
    tItemP newItem;

    strcpy(newItem.projectName, projectName);
    newItem.numVotes = 0;
    newItem.projectEco = strcmp(projectEco, "eco") == 0;

    itemToUpdate.projectList = projectList;

    if (!insertItemP(newItem, &projectList)) printf("+ Error: New not possible\n");
    else { 
        updateItemC(itemToUpdate, findItemC(committeeName, *committeeList), committeeList);
        printf("* New: committee %s project %s category %s\n", committeeName, projectName, projectEco);
    }
    return;
}


void stats(tListC committeeList) {

    if (!isEmptyListC(committeeList)) {

        for (tPosC p = firstC(committeeList); p != NULLC; p = nextC(p, committeeList)) {

            tItemC committee = getItemC(p, committeeList);
            tListP projectList = committee.projectList;

            printf("Committee %s\n", committee.committeeName);

            if (!isEmptyListP(projectList)) {

                for (tPosP q = firstP(projectList); q != NULLP; q = nextP(q, projectList)) {

                    tItemP project = getItemP(q, projectList);

                    printf("Project %s category %s numvotes %d (%.2f%%)\n",
                        project.projectName,
                        project.projectEco ? "eco" : "non-eco",
                        project.numVotes,
                        calculatePercentage(project.numVotes, committee.validVotes)
                    );

                }

            } else printf("No projects\n");

            printf("Nullvotes %d\n", committee.nullVotes);
            printf("Participation: %d votes from %d evaluators (%.2f%%)\n\n", 
                committee.validVotes, 
                committee.totalEvaluators, 
                calculatePercentage(committee.validVotes, committee.totalEvaluators)
            );
        }


    } else printf("+ Error: Stats not possible\n");
}


void vote(tListC* committeeList, char* committeeName, char* projectName) {}
void disqualify(tListC* committeeList, char* projectName) {}
void remove(tListC* committeeList) {}
void winners(tListC* committeeList) {}


void processCommand(tListC* list, char *commandNumber, char command, char *param1,char *param2, char *param3) {

    printf("********************\n");

    switch (command) {
        case 'C':
            printf("%s %c: committee %s totalevaluators %s\n", commandNumber, command, param1, param2);
            create(list, param1, param2);
            break;        

        case 'N':
            printf("%s %c: committee %s project %s category %s\n", commandNumber, command, param1, param2, param3);
            new(list, param1, param2, param3);
            break;

        case 'S':
            printf("%s %c:\n", commandNumber, command);
            stats(*list);
            break;

        case 'V':
            printf("%s %c: committee %s project %s\n", commandNumber, command, param1, param2);
            vote(list, param1, param2);
            break;

        case 'D':
            printf("%s %c: project %s\n", commandNumber, command, param1);
            disqualify(list, param1);
            break;

        case 'R':
            printf("%s %c:\n", commandNumber, command);
            remove(list);
            break;

        case 'W':
            printf("%s %c:\n", commandNumber, command);
            winners(list);
            break;

        default:
            break;
    }
}

void readTasks(char *filename, tListC* list) {
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

            processCommand(list, commandNumber, command[0], param1, param2, param3);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "create.txt";

    tListC list; // Declaración de la varibale con una lista de comités
    createEmptyListC(&list); // Inicialización en vacío de la lista

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name, &list);

    return 0;
}
