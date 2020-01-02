#include "AutoCounter.h"
#include "TPStash.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    PStash<AutoCounter> acStash;
    for(int i = 0; i < 10; i++)
        acStash.add(AutoCounter::create());
    cout << "Removing 5 manually:\n";
    for(int j = 0; j < 5; j++)
        delete acStash.remove(j);
    cout << "Remove two without deleting them:";
    // ... to generate the cleanup error message.
    cout << acStash.remove(5) << "\n";
    cout << acStash.remove(6) << "\n";
    cout << "The destructor cleans up the rest: \n";
    // Repeat the test from earlier chapters:
    ifstream in("TPStashTest.cpp");
    assure(in, "TPStashTest.cpp");
    PStash<string> stringStash;
    string line;
    while(getline(in, line))
        stringStash.add(new string(line));
    // Print out the strings:
    for(int u = 0; stringStash[u]; u++)
        cout << "stringStash[" << u << "] = " << *stringStash[u] << "\n"; 
}
