#include <iostream>
#include "ArrayList.h"

int main(int argc, char *argv[])
{
    std::cout << "Begin to test...\n";
    CRAZYFISH::ArrayList<int> A(5, 3);
    A.printArrayList();
    for (int i = 0; i < 5; i++)
        A[i] = i;

    for (int i = 0; i < 5; i++)
        std::cout << A[i] << "\t";
    std::cout << "\n";

    std::cout << "Test << :" << A << "\n";
    std::cout << A.find(3) << "\n";
    CRAZYFISH::ArrayList<int> B(5);
    B[0] = 5;
    B[1] = 1;
    B[2] = 4;
    B[3] = 2;
    B[4] = 3;
    B.merge_sort();
    
}
