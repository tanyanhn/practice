#include <cstring>
#include <iostream>
#include "../require.h"
using namespace std;

class chararray {
    static const int max = 5;
    char data[5];
public:
    chararray(char c = ' ') {memset(data, c , max); };
    void print() const {
        for (int i = 0 ; i < max ; ++i)
            cout << data[i];
        cout << endl;
    }
    
};
int main(int argc, char *argv[])
{
    chararray a('x');
    a.print();
    
    return 0;
}
