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
	std::cout << "Czas: " << ((double)(stop - start)/CLOCKS_PER_SEC) << endl;
}


void liczFunkcyjnie()
{
	for(int x=0; x<n; x++) numbersTable[x]=false;
	clock_t start, stop;
	omp_set_nested(1);
	start = clock();

	szukajPierwszych();

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
	std::cout << "Czas: " << ((double)(stop - start)/CLOCKS_PER_SEC) << endl;
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
    int th_id=omp_get_thread_num();

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
	std::cout << "Czas: " << ((double)(stop - start)/CLOCKS_PER_SEC) << endl;
}

int main()
{
	liczSekwencyjnie();

	V.clear();
	liczFunkcyjnie();
	
	V.clear();
	liczRownolegleDomeny();
}