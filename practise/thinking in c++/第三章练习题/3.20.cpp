#include<iostream>
using namespace std;

typedef struct {
	int i,j,k;
}ThreeDpoint;

int main(){
	ThreeDpoint a[10];
	cout << "sizeof(ThreeDpoint) = "<< sizeof(ThreeDpoint) <<endl;
	for(int i = 0; i<10;i++)
	   cout << "&a[" << i << "] = "
	        << &a[i] << endl;
} 
