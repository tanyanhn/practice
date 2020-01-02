#include <iostream>
#include "ArrayList.h"
#include <time.h>
#include <fstream>

int main (int argc, char *argv[])
{
    std::cout << "Begin to test..." << std::endl; 

    int N0 = 100000;
    int value;
    long N1 = 100;
    long N2 = N1*N1; 
    long N3 = N2*N1;
    long N4 = N3*N1;
    clock_t start, finish;

    CRAZYFISH::ArrayList<long> A1(N1);
    CRAZYFISH::ArrayList<long> A2(N2);
    CRAZYFISH::ArrayList<long> A3(N3);
    CRAZYFISH::ArrayList<long> A4(N4);
    
    std::cout << N1 << "\n" << N2<< "\n" << "\n";
	for(long i = 0; i < N1; i++)
	  A1[i]=i;
	for(long i = 0; i < N2; i++)
	  A2[i]=i;
	for(long i = 0; i < N3; i++)
	  A3[i]=i;
	for(long i = 0; i < N4; i++)
        A4[i]=i;
    
    for(int i = 0;i < 4; i++){
    start = clock();
	for(int j = 1; j <= N0; j++)
	  value=A1.fast_find(N1-1);
      finish = clock();
      double ticks = (double)(finish - start)/CLOCKS_PER_SEC; 
	std::cout << ticks << std::endl;
	std::cout << value << std::endl;
    }
    return 0;
};
