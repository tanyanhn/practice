#include<iostream>
#include<string>
using namespace std;

void func1(string* p){
	*p="work";
}

void func2(string& a){
	string* q;
	q=&a;
	*q="hardwork"; 
}

int main(){
	string a,b;
	a="lazy";b="lazy";
	cout << a << endl <<b<<endl;
	func1(&a);
	func2(b);
	cout << a << endl <<b;
}
