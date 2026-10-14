#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#define PHI ((1.0 + sqrt(5.0)) / 2.0)

typedef int (*Alg)(int);
typedef double (*Cota)(double);

typedef struct {
  Alg run;
  const char *name;
  int k;
  int *n;
  int sizeN;
  Cota f, g, h;
  const char *fn, *gn, *hn;
} AlgInfo;

// Cotas para fib1
double f1(double n) { return pow(1.1, n); } // Cota subestimada
double g1(double n) { return pow(PHI, n); } // Cota exacta
double h1(double n) { return pow(2.0, n); } // Cota sobreestimada

// Cotas para fib2
double f2(double n) { return pow(n, 0.8); } // Cota subestimada
double g2(double n) { return n; }           // Cota exacta
double h2(double n) { return n * log(n); }  // Cota sobreestimada

// Cotas para fib3
double f3(double n) { return sqrt(log(n)); } // Cota subestimada
double g3(double n) { return log(n); }       // Cota exacta
double h3(double n) { return pow(n, 0.5); }  // Cota sobreestimada

// Obtiene la hora actual en microsegundos
double microsegundos() {
  struct timeval t;
  if (gettimeofday(&t, NULL) < 0 )
    return 0.0;
  return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Algoritmo O(PHI^n)
int fib1 (int n) {
  if (n < 2) return n;
  else return fib1(n - 1) + fib1(n - 2);
}

// Algoritmo O(n)
int fib2 (int n) {
  int i, j, k;
  i=1; j=0; k=1;

  for (k=1 ;k <= n;k++) {
    j = i + j;
    i = j - i;
  }

  return j;
}

// Algoritmo O(log(n))
int fib3 (int n) {
  int i, j, k, h, t;
  i = 1; j = 0; k = 0; h = 1;

  while ( n > 0 ) {
    if ((n % 2) != 0) {
      t = j * h;
      j = (i * h) + (j * k) + t;
      i = (i * k) + t;
    }
    t = h * h;
    h = (2 * k * h) + t;
    k = (k * k) + t;
    n = n / 2;
  }

  return j;
}

// Función auxiliar para imprimir un caracter c, n veces
void printTimes(char c, int n) {
  int i;
  for (i = 0; i<n; i++) printf("%c", c);
}

// Impresión cabecera de la tabla de tiempos
void printHeader(AlgInfo alg) {
  printf("\n"); printTimes('=', 35);
  printf(" TABLA DE TIEMPOS %s ", alg.name);
  printTimes('=', 35); printf("\n\n");

  printf("%12s %15s %21s %20s %20s\n", "n", "t(n)", alg.fn, alg.gn, alg.hn);

  printTimes('-', 94); printf("\n");
}

// Impresión pie de la tabla de tiempos
void printFooter(AlgInfo alg) {
  printTimes('-', 94); printf("\n");
  printf("*: tiempo promedio de %d ejecuciones\n\n", alg.k);
}

void test(int n) {

  int i;

  printf("\n========== TEST DE VALIDACION ==========\n");
  printf("%5s %10s %10s %10s\n", "n", "fib1(n)", "fib2(n)", "fib3(n)");
  printTimes('-', 41); printf("\n");
  for (i = 1; i <= n; i++) {
    printf("%5d %10d %10d %10d \n", i, fib1(i), fib2(i), fib3(i));
  }
  printTimes('-', 41); printf("\n");
}

void timeTable(AlgInfo alg) {

  char mark;
  int i, j, n;
  double t, t1, t2;

  printHeader(alg); // Impresión de cabecera

  for (i = 0; i < alg.sizeN; i++) {
    n = alg.n[i];

    // Cálculo de tiempo en la n[i] correspondiente
    t1 = microsegundos();
    alg.run(n);
    t2 = microsegundos();
    t = t2 - t1;

    // Cuando el tiempo no supera el umbral de 500 microsegundos,
    // se calcula el promedio de tiempo después de k iteraciones del algoritmo
    if (t < 500) {
      t1 = microsegundos();
      for (j = 0; j < alg.k; j++) alg.run(n);
      t2 = microsegundos();
      t = (t2 - t1) / alg.k;
    }

    // Impresion de la línea correspondiente a n[i]
    mark = (t<500) ? '*' : ' ';
    printf("%12d %15.6f%c %20.6f %20.6f %20.8f\n", 
      n, t, mark, t/alg.f(n), t/alg.g(n), t/alg.h(n));
  }

  printFooter(alg); // Impresión del pie
}

int main(void) {

  int n[] = {2, 4, 8, 16, 32}; 
  int m[] = {1000, 10000, 100000, 1000000, 10000000}; 
  int sizeN = sizeof(n) / sizeof(n[0]); 
  int sizeM = sizeof(m) / sizeof(m[0]);

  AlgInfo fibonacci1 = {
    fib1, "FIB1", // alg func/name
    1000000, // k
    n, sizeN, // n
    f1, g1, h1, // cotas
    "t(n)/1.1^n", "t(n)/phi^n", "t(n)/2^n"
  };

  AlgInfo fibonacci2 = {
    fib2, "FIB2", // alg func/name
    1000, // k
    m, sizeM, // n
    f2, g2, h2, // cotas
    "t(n)/n^0.8", "t(n)/n", "t(n)/n*log(n)"
  };

  AlgInfo fibonacci3 = {
    fib3, "FIB3", // alg func/name
    100000, // k
    m, sizeM, // n
    f3, g3, h3, // cotas
    "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/sqrt(n)"
  };

  test(30);

  timeTable(fibonacci1);
  timeTable(fibonacci2);
  timeTable(fibonacci3);

  return 0;
}
