#include<iostream>
#include<climits>
using namespace std;

void ieeePrint(float x){
	unsigned char* p=reinterpret_cast<unsigned char*>(&x);
	int bitno=0;
	for(int i =sizeof (float)-1;i>=0;i--){
		for(int j =CHAR_BIT-1;j>=0;--j,++bitno){
			cout <<!!(p[i]&(1<<j));
			if(bitno==0||bitno==8)
			  cout<<' ';
		}
	}
	cout <<endl;
}

int main(){
	ieeePrint(2.0);
	ieeePrint(6.5);
	ieeePrint(-6.5);
}
