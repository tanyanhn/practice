#include<string>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main(){
	vector<string> v;
	ifstream in("Untitled2.cpp");
	string line;
	while(getline(in,line))
	v.push_back(line);//Add the line to the end
	//Add line number:
	for (int i=0; i<v.size();i++)
	cout << i <<": "<<v[i]<<endl;  
}
