#include<iostream>
#include "ExampleConfig.h"
#include "myrand.h"

int doubleNumber(int x){
    return 2 * x;
}

int main(int argc, char** argv){
    using namespace std;
    int x = atoi(argv[1]);
    cout << "Version: " << VERSION << endl;
    cout << doubleNumber(x) << endl;
    smyrand(x);
    for(auto i = 0; i < 14; i++)
        cout << myrand() << " ";
    cout << endl;
    return 0;
}