#ifndef PRO2_2026_P1_TYPES_H
#define PRO2_2026_P1_TYPES_H

#include <stdbool.h> /* Librería que incluye los valores booleanos (true/false). */

/* Definición de constantes */
#define NAME_LENGTH_LIMIT 25

/* Definición de tipos */
typedef char tProjectName[NAME_LENGTH_LIMIT];      /* Cadena de caracteres para el nombre del proyecto. */
typedef int tNumVotes;                             /* Número entero que contabiliza los votos recibidos. */
typedef bool tProjectEco;                          /* Valor booleano que indica si el proyecto es ecológico. */

typedef struct tItemL {             /* Definición de la estructura que conforma cada elemento de una lista. */
    tProjectName projectName;       /* Nombre del proyecto. */
    tNumVotes numVotes;             /* Contador de votos. */
    tProjectEco projectEco;         /* Indicador de si un proyecto es ecológico. */
} tItemL;

#endif  // PRO2_2026_P1_TYPES_H