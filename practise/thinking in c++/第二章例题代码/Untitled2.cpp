#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	ifstream in("Untitled1.cpp");
	string s,line;
	while(getline(in,line))
	s += line + "\n";
	cout << s;
}



