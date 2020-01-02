#include<iostream>
using namespace std;

union Packed{
	char i;
	short j;
	int k;
	float f;
	double d; 
};

int main(){
	cout << "sizeof(Packed) ="
	     << sizeof(Packed) << endl;
	     Packed x;
	     x.i = 'c';
	     cout << x.i << endl;
	     x.d = 3.14159;
	     cout << x.d << endl;
}
