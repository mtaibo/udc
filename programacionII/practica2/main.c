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


void new(tListC* committeeList, char* committeeName, char* projectName, char* projectCategory) {}
void stats(tListC* committeeList) {}
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
            stats(list);
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
