#include<iostream>
using namespace std;

int f(double c){
	return static_cast<int>(c);
}

int main(){
	int (*fp)(double);
	fp=f;
	cout<<(*fp)(9.9);
}
