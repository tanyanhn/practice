#include<iostream>
#include"printBinary.cpp"
using namespace std;

void printBinary(unsigned char);

void change(void* p,int k, int j){
	int* t=reinterpret_cast<int*>(p);
	for(int i=0;i<k;i++)
		*(t+i)=j;
}

int main(){
	int a[]={3,6,23,5};
	for(int i=0;i<4;i++)
	printBinary(a[i]);
	cout << endl; 
	void* p=reinterpret_cast<void*>(a);
	change(p,sizeof a,9);
	for(int i=0;i<4;i++)
	printBinary(a[i]);
}
