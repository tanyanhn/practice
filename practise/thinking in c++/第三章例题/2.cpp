#include<iostream>
using namespace std;

int main(){
	void* vp;
	char c;
	int i=3;
	float f;
	double d;
	vp = &i;
	cout  << *((int*)vp);
	 
}
