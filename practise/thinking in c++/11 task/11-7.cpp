#include<iostream>
using namespace std;

int i = 1;
int* pp = &i; 
int** p = &pp;

void f(int**& q) {
    (**q)++;
}

int main() {
    f(p);
    cout << i;
}
