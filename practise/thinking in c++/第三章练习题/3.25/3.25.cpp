#include"PrintBinary.cpp"
#include<iostream>
using namespace std;

void printBinary(unsigned char);

int main(){
	float x=128.0;
	unsigned char* p=reinterpret_cast<unsigned char*>(&x);
	for(int i = 0;i<sizeof(float);i++)
	   printBinary(p[i]);
	cout <<endl;
}
