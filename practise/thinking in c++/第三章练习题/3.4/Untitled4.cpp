#include<iostream>
using namespace std;

int main(){
	int c;
	while(1){
		cout << "MAIN MENU:"<<endl;
		cout <<"1:left,2:right,3:quit->";
		cin >> c;
		if(c==3)
		break;
		switch(c){
			case 1:{cout <<"LEFT MENU:"<<endl;
			        cout <<"select 1:a or 2:b:";
			        cin >>c;
			        switch(c){
			        	case 1:{
			        		cout <<"you chose 'a'"<<endl;
			        		continue;
							break;
						}
						case 2:{
			        		cout <<"you chose 'b'"<<endl;
			        		continue;
							break;
						}
						default:{
							cout <<"you didn't chose a or b"<<endl;
			        		continue;
							break;
						}
					}
				break;}
			case 2:{cout <<"RIGHT MENU:"<<endl;
			        cout <<"select 1: or 2:d:";
			        cin >>c;
			        switch(c){
			        	case 1:{
			        		cout <<"you chose 'c'"<<endl;
			        		continue;
							break;
						}
						case 2:{
			        		cout <<"you chose 'd'"<<endl;
			        		continue;
							break;
						}
						default:{
							cout <<"you didn't chose c or d"<<endl;
			        		continue;
							break;
						}
					}
				break;}
				default:{
					cout <<"you must type l or r or q"<<endl;
					break;
				}
			}
			
		}
		cout<< "quitting menu..."<<endl;
	}

