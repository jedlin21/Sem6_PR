#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <iostream>

long long num_steps = 1000000000;
//long long num_steps = 1000000;
double step;

int main(int argc, char* argv[])
{
    clock_t start, stop;
    double start_omp, stop_omp;
    double pi, sum=0.0;
    //int i;
    step = 1./(double)num_steps;
    start = clock();
    start_omp =  omp_get_wtime();
    omp_set_num_threads(4);
    double x;
    
    #pragma omp parallel private(x)
        {
            //printf("num_threads = %d from thread %d\n", omp_get_num_threads(), omp_get_thread_num());
            //std::cout << omp_get_thread_num() << " hello " << omp_get_num_threads() << std::endl;
            
        #pragma omp for reduction (+:sum)
            for (int i=0; i<num_steps; i++)
            {
                //std::cout << i << " " << sum << " " << omp_get_thread_num() << " " << omp_get_num_threads() << std::endl;
                x = (i + .5)*step;
                sum = sum + 4.0/(1.+ x*x);
            }
        }    
    pi = sum*step;
    stop = clock();
    stop_omp =  omp_get_wtime() ;

	printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	printf("Czas przetwarzania wynosi %f sekund(preocesorosekundy)\n",((double)(stop - start)/CLOCKS_PER_SEC));
    printf("Czas przetwarzania wynosi %f sekund(rzeczywisty)\n",((double)(stop_omp - start_omp)));
    
	return 0;
}