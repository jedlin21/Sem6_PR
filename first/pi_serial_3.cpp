#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <iostream>

long long num_steps = 1000000000;
double step;

int main(int argc, char* argv[])
{
    clock_t start, stop;
    double start_omp, stop_omp;
    double pi, sum=0.0;
    int i;
    step = 1./(double)num_steps;
    start = clock();
    start_omp =  omp_get_wtime();
    #pragma omp parallel num_threads(1)
        {
        #pragma omp for 
            for (i=0; i<num_steps; i++)
            {
                double x = (i + .5)*step;
                #pragma omp atomic
                sum = sum + 4.0/(1.+ x*x);
            }
        }    
    pi = sum*step;
    stop = clock();
    stop_omp =  omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/CLOCKS_PER_SEC));
    printf("Czas przetwarzania wynosi %f sekund(rzeczywisty)\n",((double)(stop_omp - start_omp)));
    
	return 0;
}