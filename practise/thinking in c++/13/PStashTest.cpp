// Test of pointer Stash
#include <iostream>
#include <fstream>
#include "PStash.h"
#include <string>
#include "../require.h"
using namespace std;

int main(int argc, char *argv[])
{
    PStash intStash;
    // 'new' works with built-in types, too. Note
    // the "pseudo-constructor" syntax:
    for (int i = 0; i < 25; i++)
        intStash.add(new int(i));
    for (int j = 0; j < intStash.count(); j++)
        cout << "intStash[" << j << "] = " << *(int*)intStash[j] << "\n";
    // Clean up:
    for(int k = 0; k < intStash.count(); k++)
        delete (int*)intStash.remove(k);
    ifstream in ("PStashTest.cpp");
    assure(in, "PStashTest.cpp");
    PStash stringStash;
    string line;
    while (getline(in, line))
        stringStash.add(new string(line));
    // Print out the strings:
    for (int u = 0; stringStash[u]; u++)
        cout << "stringStash[" << u << "] = " << *(string*)stringStash[u] <<endl;
    // Clean up:
    for (int v = 0; v < stringStash.count(); v++)
        delete reinterpret_cast<string*>(stringStash.remove(v));
    return 0;
}
