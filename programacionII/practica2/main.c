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


void create(tListC* list, char* committee, char* totalEvaluators) {}
void new(tListC* list, char* committee, char* project, char* category) {}
void stats(tListC* list) {}
void vote(tListC* list, char* committee, char* project) {}
void disqualify(tListC* list, char* project) {}
void remove(tListC* list) {}
void winners(tListC* list) {}


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
