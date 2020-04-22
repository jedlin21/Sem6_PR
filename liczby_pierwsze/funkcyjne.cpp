#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>
#include <time.h>

using namespace std;

const int n = 10000000;
bool numbersTable[n + 1];

vector<int> V;

void szukajPierwszychDoSqrtN()
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

void liczFunkcyjnie()
{
	for(int x=0; x<n; x++) numbersTable[x]=false;
	clock_t start, stop;
	omp_set_nested(1);
	start = clock();

	szukajPierwszychDoSqrtN();

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

int main()
{
	omp_set_num_threads(4);
	V.clear();
	liczFunkcyjnie();
}