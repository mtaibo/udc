#ifndef PRO2_2026_P1_TYPES_H
#define PRO2_2026_P1_TYPES_H

#define NAME_LENGTH_LIMIT 25
#define LNULL -1
#define MAX 25

#include <stdbool.h>
#include <string.h>

typedef char tProjectName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;
typedef bool tProjectEco;
typedef int tPosL;

typedef struct tItemL {
    tProjectName projectName;
    tNumVotes numVotes;
    tProjectEco projectEco;
} tItemL;

typedef struct tList {
    tItemL data[MAX];
    tPosL lastPos;
} tList;

#endif //PRO2_2026_P1_TYPES_H
