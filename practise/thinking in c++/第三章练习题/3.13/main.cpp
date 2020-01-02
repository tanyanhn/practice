#include"printBinary.h"
#include<iostream>
using namespace std;

#define PR(STR,EXPR) \
  cout << STR; printBinary(EXPR); cout << endl;
  
int main(){
	unsigned int getval;
	unsigned char a,b;
	cout <<"Enter a number between 0 and 255: ";
	cin >> getval; a=getval;
	PR("a in binary: ",a);
	cout <<"Enter a number between 0 and 255: ";
	cin >> getval; b=getval;
	PR("b in binary: ",b);
	PR("rol(a)= ",rol(a));
	PR("ror(a)= ",ror(a));
}
