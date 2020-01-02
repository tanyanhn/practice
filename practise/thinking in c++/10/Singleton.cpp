#include <iostream>
#include "../require.h"
using namespace std;

class Egg {
    static Egg e;
    int i;
    Egg (int ii ) : i(ii) {}
    Egg (const Egg& );
public:
    static Egg* instance() { return &e;}
    int val() const { return i ;}
};

Egg Egg::e(47);

int main(int argc, char *argv[])
{
    cout << Egg::instance()->val() << endl;
    
    return 0;
}
