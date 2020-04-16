#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>
#include <time.h>

using namespace std;

const int n = 1000000000;

bool numbersTable[n + 1];

vector<int> V;

void szukajPierwszych()
{
	for (int i = 2; i*i*i*i <= n; i++ )  // szukaj pierwszych w <2, sqrt(n)>
	{
		if (numbersTable[i] == false)
		{
			for (int j = 2 * i ; j*j <= n; j += i) {
				numbersTable[j] = true;
			}
		}
	}
	for(int i=2; i*i<=n; i++) 
		if(!numbersTable[i]) {
			V.push_back(i); 
		}
}

void liczSekwencyjnie()
{
	for(int x=0; x<n; x++) numbersTable[x]=false;
	clock_t start, stop;
	start = clock();
	for (int i = 2; i*i <= n; i++ )
	{
		if (numbersTable[i] == true)
			continue;
		for (int j = 2 * i ; j <= n; j += i) {
			numbersTable[j] = true;
		}
	}
	stop = clock();
	int ilosc=0;
	for(int x=0; x<n; x++) if(numbersTable[x]==false) ilosc++;
	std::cout << "Ilosc liczb pierwszych: " << ilosc << endl;
	std::cout << "Czas: " << ((double)(stop - start)/1000.0) << endl;
}


void liczRownolegle1()
{
	for(int x=0; x<n; x++) numbersTable[x]=false;
	clock_t start, stop;
	omp_set_nested(1);
	start = clock();
	int m=sqrt((double)n);
	for (int i = 2; i*i <= n; i++ )
	{
		if (numbersTable[i] == true)
			continue; 
		#pragma omp parallel for
		for (int j = 2 * i ; j <= n; j += i) {
			numbersTable[j] = true;
		}
	}
	stop = clock();
	int ilosc=0;
	for(int x=0; x<n; x++) if(numbersTable[x]==false) ilosc++;
	std::cout << "Ilosc liczb pierwszych: " << ilosc << endl;
	std::cout << "Czas: " << ((double)(stop - start)/1000.0) << endl;
}

void liczRownolegle2()
{
	for(int x=0; x<n; x++) numbersTable[x]=false;
	clock_t start, stop;
	omp_set_nested(1);
	start = clock();
	int m=sqrt((double)n);
	for (int i = 2; i*i <= n; i++ )
	{
		if (numbersTable[i] == true)
			continue;
#pragma omp parallel for schedule(static, 1)
		for (int j = 2 * i ; j <= n; j += i) {
			numbersTable[j] = true;
		}
	}
	stop = clock();
	int ilosc=0;
	for(int x=0; x<n; x++) if(numbersTable[x]==false) ilosc++;
	std::cout << "Ilosc liczb pierwszych: " << ilosc << endl;
	std::cout << "Czas: " << ((double)(stop - start)/1000.0) << endl;
}


void liczRownolegle3()
{
	for(int x=0; x<n; x++) numbersTable[x]=false;
	clock_t start, stop;
	start = clock();
#pragma omp parallel
	{
	      // HANDLE thread_uchwyt=GetCurrentThread();
               int th_id=omp_get_thread_num();
            //   DWORD_PTR mask = (1 << (th_id % 4 ));
            //   DWORD_PTR result = SetThreadAffinityMask(thread_uchwyt,mask);
	        int liczbaWatkow=omp_get_num_threads();
	        int RozmiarBloku=n/liczbaWatkow;
	        int m=sqrt((double)n);
		int mythid=omp_get_thread_num();

		int lewa=mythid*RozmiarBloku;
		int prawa=min((mythid+1)*RozmiarBloku-1, n-1);
		for (int i = 2; i <= m; i++ ) 
		{
			if (numbersTable[i] == true) 
				continue; 
			int z_lewe=max((double)2, ceil((double)lewa/(double)i));
			int z_prawe=floor((double)prawa/(double)i);
			for (int j = z_lewe ; j <= z_prawe; j++) {
				numbersTable[j*i] = true;
			}
		}
	}

	stop = clock();
	int ilosc=0;
	for(int x=0; x<n; x++) if(numbersTable[x]==false) ilosc++;
	std::cout << "Ilosc liczb pierwszych: " << ilosc << endl;
	std::cout << "Czas: " << ((double)(stop - start)/1000.0) << endl;
}

void liczRownolegleDomeny(int RozmiarBloku=131072)
{
	for(int x=0; x<n; x++) numbersTable[x]=false;
	omp_set_dynamic(false);
	clock_t start, stop;
	start = clock();

	szukajPierwszych();
#pragma omp parallel
	{
    //HANDLE thread_uchwyt=GetCurrentThread();
    int th_id=omp_get_thread_num();
    //DWORD_PTR mask = (1 << (th_id % 4 ));
    //DWORD_PTR result = SetThreadAffinityMask(thread_uchwyt,mask);

#pragma omp for
    for(int x=0; x<=n/RozmiarBloku; x++)
        {
            int lewa=x*RozmiarBloku;
            int prawa=min((x+1)*RozmiarBloku-1, n-1);
            for(int y=0; y<V.size(); y++)
            {
                int lp=V[y];
                int z_lewe=max((double)2,                
                ceil((double)lewa/(double)lp));
                int z_prawe=floor((double)prawa/(double)lp);
                for(int z=z_lewe; z<=z_prawe; z++)
                {
                    numbersTable[z*lp]=true;
                }
            }
        }
    }

	stop = clock();
	V.clear();
	int ilosc=0;
	for(int x=0; x<n; x++) if(numbersTable[x]==false) ilosc++;
	
	std::cout << "Ilosc liczb pierwszych: " << ilosc << endl;
	std::cout << "Czas: " << ((double)(stop - start)/1000.0) << endl;
}
