#include<iostream>
using namespace std;

enum color {
	BLACK,
	RED,
	GREEN,
	BLUE,
	WHITE
};

int main(){
	for (int hue=BLACK;hue<=WHITE;++hue)
	  cout << hue <<' ';
}
