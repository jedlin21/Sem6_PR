#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>
#include <time.h>

using namespace std;

const int n = 10000000;
bool numbersTable[n + 1];


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


int main()
{
	liczSekwencyjnie();
}