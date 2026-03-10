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

#define DYNAMIC_LIST

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

tList L;
int nullVotes = 0;
int totalVotes = 0;

void processCommand(char* commandNumber, char command, char* param1, char* param2) {
    switch (command) {

        case 'N': {

            tItemL newItem;

            strcpy(newItem.projectName, param1);
            newItem.numVotes = 0;
            newItem.projectEco = (strcmp(param2, "eco") == 0);

            printf("* New: project %s category %s\n", param1, param2);
            if (!insertItem(newItem, LNULL, &L)) printf("+ Error: New not possible\n");

            break;
        }

        case 'V': {

            tPosL itemPos;
            tItemL item;

            itemPos = findItem(param1, L);

            if (itemPos != LNULL) {
                item = getItem(itemPos, L);
                item.numVotes++;
                totalVotes++;
                updateItem(item, itemPos, &L);
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

            tPosL itemPos;
            tItemL item;

            itemPos = findItem(param1, L);

            if (itemPos != LNULL && !isEmptyList(L)) {
                item = getItem(itemPos, L);
                nullVotes += item.numVotes;
                totalVotes -= item.numVotes;
                deleteAtPosition(itemPos, &L);
                printf("* Disqualify: project %s category %s\n", 
                    param1, 
                    (item.projectEco) ? "eco" : "non-eco"
                );

            } else {
                printf("+ Error: Disqualify not possible\n");
                nullVotes++;
            }

            break;
        }

        case 'S': {

            tItemL item;

            if (isEmptyList(L)) {
                printf("+ Error: Stats not possible\n");
                break;
            }

            for (tPosL p = first(L); p != LNULL; p = next(p, L)) {
                item = getItem(p, L);
                printf("Project %s category %s numvotes %d (%.2f%%)\n",
                    item.projectName,
                    (item.projectEco) ? "eco" : "non-eco",
                    item.numVotes,
                    (totalVotes == 0) ? 0.0 : ((float) item.numVotes / (float) totalVotes) * 100
                );
            }

            printf("Null votes %d\n", nullVotes);
            printf("Participation: %d votes from %s evaluators (%.2f%%)\n",
                totalVotes,
                param1,
                (atoi(param1) == 0) ? 0.0: ((float) totalVotes / atoi(param1)) * 100
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