#include<iostream>
using namespace std;
int main(){
	int a=0, b=1, c=2 ,d=3 ,e=4 ;
	a= (b++, c++, d++, e++);
	cout << "a = " << a <<endl;
	(a =b++),c++ ,d++ ,e++;
	cout <<"a = " << a << endl;
}
