#include <string>
#include <fstream>
using namespace std;

int main (){
	ifstream in("Untitled0.cpp");//Open for reading
	ofstream out("Untitled0.cpp");//Open for writing
	string s;
	while(getline(in,s)) //Discards newline char
	out << s << "\n";//...must add it back
} ///:~
