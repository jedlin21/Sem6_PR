/* Wyznaczanie liczb pierwszych - sito Eratostenesa */
/* program sito.c */
/* kompilacja:
use_pgi
pgcc -mp -o sito -Minfo sito-2.c */
/* wykonanie:
#PBS -N sito-4
#PBS -S /bin/csh
#PBS -l nodes=1:ppn=4
#PBS -l mem=100mb
#PBS -l walltime=00:10:00
cd ~zjc/omp
setenv OMP_NUM_THREADS 4
./sito >wynik-sito-4 */
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#define N 10000000 /* definiuje zakres 2..N */
#define S (int)sqrt(N)
#define M N/10
int main(int argc, char** argv) {
    long int a[S + 1]; /* tablica pomocnicza */
    long int podzielniki[S + 1]; /* podzielniki z zakresu 2..S */
    long int pierwsze[M]; /* liczby pierwsze w przedziale 2 .. N */
    long int i, k, liczba, reszta;
    long int lpodz = 0; /* liczba podzielnikow w tablicy podzielniki */
    long int llpier = 0; /* liczba liczb pierwszych w tablicy pierwsze */
    double czas; /* zmienna do mierzenia czasu */
    clock_t start, stop;
    omp_set_num_threads(2);
    printf("Liczba watkow: %d\n", omp_get_max_threads());
    czas = omp_get_wtime(); /* pomiar czasu */
    start = clock();
    /* wyznaczanie podzielnikow z zakresu 2..S */
    #pragma omp parallel for default(none) shared(a)
    for (i = 2; i <= S; i++) a[i] = 1; /* inicjalizacja */
    for (i = 2; i <= S; i++)
    if (a[i] == 1) {
    pierwsze[llpier++] = podzielniki[lpodz++] = i; /* zapamietanie liczby pierwszej */
    /* wykreslanie liczb zlozonych bedacych wielokrotnosciami i */
    for (k = i + i; k <= S; k += i) a[k] = 0;
    }
    /* rownolegle wyznaczanie liczb pierwszych */
    #pragma omp parallel for default(none) private(k, reszta) \
    shared(llpier, lpodz, pierwsze, podzielniki)
    for (liczba = S + 1; liczba <= N; liczba++) {
    for (k = 0; k < lpodz; k++) {
    reszta = (liczba % podzielniki[k]);
    if (reszta == 0) break; /* liczba zlozona */
    }
    if (reszta != 0) {
    #pragma omp critical
    pierwsze[llpier++] = liczba; /* zapamietanie liczby pierwszej */
    }
    }
    czas = omp_get_wtime() - czas; /* obliczenie czasu dzialania */
    stop = clock();
    printf("czas: %f sek wtick: %f sek\n", czas, omp_get_wtick());
    std::cout << "Czas: " << ((double)(stop - start)/CLOCKS_PER_SEC) << std::endl;
    printf("Liczba liczb pierwszych: %d\n", llpier);
    printf("------------- lpodz: %d \n", lpodz);
    /* printf("Wszystkie liczby pierwsze ************\n");
    for (i = 0; i < llpier; i++) {
    printf(" %ld ", pierwsze[i]);
    if (i % 10 == 0) printf("\n");
    }
    printf("\n*************\n"); */
    return 0;
}