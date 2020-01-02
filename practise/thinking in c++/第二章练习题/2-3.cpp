#include<string>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main(){
	vector<string> words;
	ifstream in("2-2.cpp");
	string word;
	int j=0;
	while(in>>word){
	  j++;
	  words.push_back(word);}
	for(int i = 0; i < words.size(); i++)
	  cout << words[i] << endl;
	cout << j <<endl;
} 
