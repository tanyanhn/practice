#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(){
	int i;
	ifstream f ("新建文本文档.txt");
	string word;
	while(f >> word){
		if(word=="zero") i=0;
		else if(word=="one") i=1;
		else if(word=="two") i=2;
		else if(word=="three") i=3;
		else if(word=="four") i=4;
		else if(word=="five") i=5;
		else if(word=="six") i=6;
		else if(word=="seven") i=7;
		else if(word=="eight") i=8;
		else if(word=="nine") i=9;
		else  break;
		switch (i){
			case 0: cout<< "funny"<<endl;
			case 1: cout<< "upset"<<endl;
			case 2: cout<< "awful"<<endl;
			case 3: cout<< "fantastic"<<endl;
			case 4: cout<< "intreasting"<<endl;
			case 5: cout<< "meanless"<<endl;
			case 6: cout<< "funny"<<endl;
			case 7: cout<< "useless"<<endl;
			case 8: cout<< "nothing"<<endl;
			case 9: cout<< "funny"<<endl;
		}
	}
}
