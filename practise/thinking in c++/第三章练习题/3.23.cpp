#include<iostream>
using namespace std;

union Primitives {
	char c;
	short s;
	int i;
	long l;
	float f;
	double d;
	long double ld;
};

int main(){
	Primitives p[10];
	Primitives* pp=p;
	cout << "sizeof(Primitives) = "
	     << sizeof(Primitives) <<endl;
	cout << "pp = " << pp <<endl;
	pp++;
	cout << "pp = " << pp <<endl;
}
