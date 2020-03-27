#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <iostream>

long long num_steps = 1000000000;
//long long num_steps = 100000;
double step;

int main(int argc, char* argv[])
{
    clock_t start, stop;
    double start_omp, stop_omp;
    double pi, finalSum = 0.0;
    volatile double part_sum[54] = { 0 };
    int i;
    step = 1./(double)num_steps;
    
    omp_set_num_threads(2);
    for(int j = 0; j<100; j++){
            start = clock();
            start_omp =  omp_get_wtime();
        #pragma omp parallel  
            {
            int id = omp_get_thread_num();
            
            #pragma  omp flush(part_sum)
            #pragma omp for 
                for (i=0; i<num_steps; i++)
                {
                    //std::cout << i << " " << sum << " " << omp_get_thread_num() << " " << omp_get_num_threads() << std::endl;
                    double x = (i + .5)*step;
                    part_sum[2*id + j] += 4.0/(1.+ x*x);
                }
            
            #pragma omp atomic
            finalSum += part_sum[id]; 
            
        }
        pi = finalSum*step;
        stop = clock();
        stop_omp =  omp_get_wtime() ;

       // printf("Wartosc liczby PI wynosi %15.12f\n",pi);
        printf("Iteracja %d\n",j);
        //printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/CLOCKS_PER_SEC));
        printf("Czas przetwarzania wynosi %f sekund(rzeczywisty)\n",((double)(stop_omp - start_omp)));
    }
	return 0;
}