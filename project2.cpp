#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    clock_t start, stop;
    int n;
    bool liczbaPierwsza = true;

    cout << "Podaj liczbę: ";
    cin >> n;

    bool liczby[ n + 1];

    for(int i = 0; i<=n; i++)
    {
        liczby[i] = false;
    }

    start = clock();
    double omp_start = omp_get_wtime();

    for (int i = 2; i <= n; i++)
    {
        liczbaPierwsza = true;
#pragma omp parallel num_threads(4)
        {
#pragma omp for
            for (int j = 2; j <= sqrt(i); j++)
            {
                if (i % j == 0)
                {
                    liczbaPierwsza = false;
                    // break;
                }
            }
            if(liczbaPierwsza)
            {
                liczby[i] = true;
            }
        }
    }
    double omp_stop = omp_get_wtime();
    stop = clock();

     for(int i = 2; i < n; i++)
    {
        if(liczby[i])
        {
            cout<< i << ", ";
        }
    }

    cout<<endl;

    printf("Czas przetwarzania wynosi %f sekund\n", ((double)(stop - start) / CLOCKS_PER_SEC));
    printf("Czas rzeczywisty wynosi %f sekund\n", ((double)(omp_stop - omp_start)));

    cout << endl;

    return 0;
}