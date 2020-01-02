#include<iostream>
#include<string>
using namespace std;

typedef struct people{
	string a;
	string b;
	int i;
}human;

int main(){
	human x;
	human* p;
	x.a="tan";x.b="yan";x.i=21;
	p=&x;
	cout << x.a <<" "<<x.b<<endl<<x.i<<endl;
	cout << p<< endl;
	p->a="zeng";p->b="xin";p->i=20;
	cout << x.a <<" "<<x.b<<endl<<x.i<<endl;
	cout << &x<< endl;
}

