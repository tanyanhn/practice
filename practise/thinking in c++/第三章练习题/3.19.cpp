#include<iostream>
using namespace std;

int main(){
	double a[10];
	cout << "sizeof(int) = "<< sizeof(double) <<endl;
	for(int i = 0; i<10;i++)
	   cout << "&a[" << i << "] = "
	        << &a[i] << endl;
} 
