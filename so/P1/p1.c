/*
 *   Miguel Taibo Perez   (miguel.taibo.perez@udc.es)
 *   Aaron Mendez Agbamu  (aaron.mendez@udc.es)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "commands.h"
#include "commands.c"

#define MAXINPUT 2048

void DecideCommand(char *tr[]) {
    int i;
    if (tr[0] == NULL) return;
    for (i=0; C[i].name != NULL; i++) {
        if (!strcmp(C[i].name, tr[0])) { (*C[i].func)(tr+1); return; }
    }
    printf("\nCommand not found: %s\n", *tr);
}

int ParseInput(char * arr, char * pieces[]) {
    int i=1;
    if ((pieces[0] = strtok(arr, " \n\t")) == NULL) return 0;
    while ((pieces[i] = strtok(NULL, " \n\t")) != NULL) i++;
    return i;
}

void ProccessInput(char * input) {
   char *tr[MAXINPUT/2 + 1]; // Small fix
   if (ParseInput(input, tr) == 0) return;
   DecideCommand(tr);
}

int main() {

    char input[MAXINPUT];
    InitStdFiles(); // Register standard input/output/error

    while (1){
        printf ("\n--> ");
        if (fgets(input, MAXINPUT, stdin) == NULL) break; // Save exit from fgets
        ProccessInput(input);
    }

    return 0;
}
