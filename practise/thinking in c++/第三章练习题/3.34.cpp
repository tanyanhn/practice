#include<iostream>
#include<string>
using namespace std;

#define DF(N) string N(){  \
   string k= #N ;  \
    return(k);   \
}

DF(a);DF(b);DF(c);DF(d);DF(e);DF(f);DF(g);

string (*func_table[])()={a,b,c,d,e,f,g};

int main(){
	while(1){
		cout <<"Press a key from 'a' to 'g'" "or q to quit" <<endl;
		char c,cr;
		cin.get(c);cin.get(cr);
		if (c=='q')
		  break;
		if(c<'a'||c>'g')
		continue;
		string s;
		s=(*func_table[c-'a'])();
		cout <<"function "<< s<<" called ..."<<endl;
	}
}
