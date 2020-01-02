#include <string>
#include <cstddef>
#include <iostream>
#include "../require.h"
using namespace std;

#define DEBUG(x) cout << #x " = " << x << endl


int main(int argc, char *argv[])
{
    if (argc = 2) {
        string s(argv[1]);
        size_t siz = s.size();
        for (size_t n = 0; n < siz; ++n) {
            s = s.erase(siz - n - 1, 1);
            DEBUG(s);}
        string q(argv[2]);
        siz = q.size();
        for (size_t n = 0; n < siz; ++n) {
            s = q.erase(siz - n - 1, 1);
            DEBUG(s);
        }
    }
    return 0;
}
