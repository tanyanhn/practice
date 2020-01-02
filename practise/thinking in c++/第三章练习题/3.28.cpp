#include<iostream>
using namespace std;


void print(double* d,int k){
	for(int i=0;i<k;i++)
	  cout << d[i] <<endl;
}

int main(){
	double a[5]={0,0,0,0,0};
	print(a,sizeof a / sizeof a[0]);
	unsigned char* p =reinterpret_cast<unsigned char*>(&a);
	for(int i=0;i<sizeof p;i++){
	   p[i]=1.0; cout <<p[i]<<endl;
    }
}
