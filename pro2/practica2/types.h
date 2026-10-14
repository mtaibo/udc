#ifndef PRO2_2026_P2_TYPES_H
#define PRO2_2026_P2_TYPES_H

#include <stdbool.h> /* Librería que incluye los valores booleanos (true/false). */

/* Definición de constantes */
#define NAME_LENGTH_LIMIT 25

/* Definición de tipos */
typedef char tCommitteeName[NAME_LENGTH_LIMIT];    /* Cadena de caracteres para el nombre del comité. */
typedef char tProjectName[NAME_LENGTH_LIMIT];      /* Cadena de caracteres para el nombre del proyecto. */
typedef int tNumVotes;                             /* Número entero que contabiliza los votos recibidos. */
typedef bool tProjectEco;                          /* Valor booleano que indica si el proyecto es ecológico. */

#endif  // PRO2_2026_P2_TYPES_H