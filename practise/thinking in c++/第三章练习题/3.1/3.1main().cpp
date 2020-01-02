#include<iostream>
#include"3.1头文件.h"
using namespace std;

int main(){
	int a,c,f;
	float d;
	char b;
	cout << "输入 a"<<endl;
	cin >> a; 
	cout << "输入 b"<<endl;
	cin >> b;
	cout << "输入 c"<<endl;
	cin >> c; 
	cout << "输入 d"<<endl;
	cin >> d; 
	cout << "输入 f"<<endl;
	cin >> f; 
	func1(a);
	func2(b);
	func3(c);
	func4(d,f);
} 
