#ifndef PRO2_2026_P1_TYPES_H
#define PRO2_2026_P1_TYPES_H

#define NAME_LENGTH_LIMIT 25
#include <stdbool.h>

typedef char tProjectName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;
typedef bool tProjectEco;

typedef struct tItemL {
    tProjectName projectName;
    tNumVotes numVotes;
    tProjectEco projectEco;
} tItemL;

#endif //PRO2_2026_P1_TYPES_H
