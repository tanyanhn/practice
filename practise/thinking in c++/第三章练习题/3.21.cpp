#include<iostream>
#include<string>
using namespace std;

int main(){
	string a[]={"I","am","tan","yan"};
	for (int i =0 ;i<sizeof a/ sizeof a[0];i++)
	    cout << a[i] <<endl;
}
