#include<string>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main(){
	vector<string>words;
	ifstream in("Untitled3.cpp");
	string word;
	while(in >> word)
	 words.push_back(word);
	 for(int i= 0; i< words.size(); i++)
	  cout << words[i] << endl; 
} 
