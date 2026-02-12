
Realizado el test correspondiente para static_list con resultado satisfactorio

Comando necesario para compilar el proyecto:

gcc -Wall test.c static_list.c -o test -DSTATIC_LIST



El ./script.sh -p test ejecutado desde la máquina de referencia mediante ssh, devuelve el static_list.c con un OK, pero también devuelve un par de advertencias:

Running script for Static list...
Compiling test program using Static list with
gcc -Wall -Wextra -DSTATIC_LIST static_list.h static_list.c ./test.c -o ./test
static_list.c: In function ‘first’:
static_list.c:37:20: warning: unused parameter ‘L’ [-Wunused-parameter]
   37 | tPosL first (tList L) {
      |              ~~~~~~^
static_list.c: In function ‘previous’:
static_list.c:49:32: warning: unused parameter ‘L’ [-Wunused-parameter]
   49 | tPosL previous (tPosL p, tList L) {
      |                          ~~~~~~^

Checking test program output using Static list...

Input file                          Result  Notes
(no input file)                     OK      

Static List result (checkpoint #1 - February 27th): OK
