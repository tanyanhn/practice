#include<string>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main(){
	vector<string> words;
	ifstream in("2-2.cpp");
	string word ,k; k = "int";
	int j=0;
	while(in>>word)
	  words.push_back(word);
	for(int i = 0; i < words.size(); i++){
	  if(words[i] == k)  j++;}
	cout << j <<endl;
} 
