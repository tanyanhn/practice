#include "TStack2.h"
#include "../require.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("TStack2Test.cpp");
    assure(file, "TStack2Test.cpp");
    Stack<string> textlines;
    // Read file and store lines in the list:
    string line;
    while (getline(file, line))
        textlines.push(new string(line));
    int i = 0;
    // Use iterator to print lines from the list:
    Stack<string>::iterator it = textlines.begin(), it1 = textlines.begin();
    Stack<string>::iterator* it2 = 0;
    while(it != textlines.end()) {
        cout << it->c_str() << endl;
        it++;
        if(++i == 10) // Remember 10th line
            it2 = new Stack<string>::iterator(it);
    }
    it = textlines.begin();
    cout << (*it2)->c_str() << endl;
    while(it != textlines.end()) {
        it++;
        textlines.pop();
    }
    it = textlines.begin();
    cout << (*it2)->c_str() << endl;
    while(it != textlines.end()) {
        cout << it->c_str() << endl;
        it++;
        // if(++i == 10) // Remember 10th line
        //   it2 = new Stack<string>::iterator(it);
    }
    cout << (*it2)->c_str() << endl;
    // (*it2)++;
    // cout << (*it2)->c_str() << endl;
    delete it2;
}

