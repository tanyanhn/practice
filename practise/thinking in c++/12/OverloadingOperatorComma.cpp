#include <iostream>

#include "../require.h"
using namespace std;

class After {
public:
    After(){}
    ~After(){}
    const After& operator,(const After&) const {
        cout << "After::operator,()\n";
        return *this;
    }
    void print(){}
};

class Before {};

Before& operator,(int, Before& b) {
    cout << "Before::operator,()\n";
    return b;
}

int main(int argc, char *argv[])
{
    After a, b;
    a, b;

    Before c;
    1, c;
    return 0;
}
