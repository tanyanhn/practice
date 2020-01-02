#include<iostream>
using namespace std;

int main(){
	for (int i = 0; i < 128; i =i + 1)
	    if ( i != 26)
	      cout << "value: " << i
	           << " character: "
			   << char(i) 
			   << endl; 
} 
