#include<iostream>
using namespace std;
int main(){
	const int a=6;
	volatile int b;
	int* p=(int*)&a;
    int* q =(int*)&b;
	q = const_cast<int*>(&b);
	*p=1;
	*q=2;

} 
