#include<iostream>
using namespace std;

int main(){
	int x,y;
	cout << 2 <<endl;
    for(x=3;x<100;x++){
		for(y=2;y<x;y++){
			if(x%y!=0)
			  continue;
			else
				break;
			}
			if(y==x) cout<< x <<endl;}
			
		
	}

