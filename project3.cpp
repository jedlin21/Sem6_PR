/* Wyznaczanie liczb pierwszych - sito Eratostenesa */ /* program sito.c */
/* kompilacja:
use_pgi
pgcc -mp -o sito -Minfo sito-2.c */ /* wykonanie:
#PBS -N sito-4
#PBS -S /bin/csh
#PBS -l nodes=1:ppn=4 #PBS -l mem=100mb
#PBS -l walltime=00:10:00 cd ~zjc/omp
setenv OMP_NUM_THREADS 4 ./sito >wynik-sito-4 */
#include <stdio.h> #include <math.h> #include <omp.h> #include <stdlib.h>
#define N 10000000 /* definiuje zakres 2..N */ #define S (int)sqrt(N)
#define M N/10
  int main(int argc, char** argv) {
long int a[S + 1]; /*
long int podzielniki[S + 1]; /* tablica pomocnicza */
long int pierwsze[M]; /* podzielniki z zakresu 2..S */
long int i, k, liczba, reszta;
long int lpodz = 0; /* liczba liczby pierwsze w przedziale 2 .. N */
long int llpier = 0; /* liczba podzielnikow w tablicy podzielniki */ liczb pierwszych w tablicy pierwsze */
double czas; /* zmienna do mierzenia czasu */





