#include<iostream>
#include<cstdlib>
#include <time.h>
#include <omp.h>
using namespace std;


int main()
{
	clock_t start, stop;
	double start_omp, stop_omp;
	int m,n;
	bool *tab;
	
	cout<<"(sekwencyjny) Podaj zakres górny przedziału: 100 000 000  \n";
	m = 50;
	n = 100;
	
	tab = new bool [n+1];
	
	for(int i=2; i<=n; i++) //zerowanie tablicy
		tab[i] = 0;

	
	start = clock();
    start_omp =  omp_get_wtime();

	for (int i=m; i*i<=n; i++) //przeszukujemy kolejnych kandydatów na pierwsze
	{	
		if(!tab[i])				//jesli liczba jest pierwsza(ma wartosc 0)
		for (int j = i*i ; j<=n; j+=i) //to wykreslamy jej wielokrotnosci
			tab[j] = 1;			//ustawiając wartosć na 1
	}
	
	stop = clock();
	stop_omp =  omp_get_wtime();

	cout<<"Kolejne liczby pierwsze z przedziału [2.."<<n<<"]: ";
	for(int i=2;i<=n;i++)
		if(!tab[i])
			cout<<i<<" ";
			
	printf("\n");
	printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/CLOCKS_PER_SEC));
    printf("Czas przetwarzania wynosi %f sekund(rzeczywisty)\n",((double)(stop_omp - start_omp)));
	cout<<endl;
	
	delete []tab;

    return 0;
}