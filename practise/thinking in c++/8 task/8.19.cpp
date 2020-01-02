#include <iostream>
#include "../require.h"
using namespace std;

class team {
    const float f;
    float g;
public:
    team(float fg = 4 ) ;
    ~team(){};
    void print();
};
team::team(float fg  ) : f(fg) , g( fg + 1) {};
void team::print(){
    cout << f << endl << g << endl;
};
int main(int argc, char *argv[])
{
    team A[2];
    A[0].print();
    A[1].print();
    return 0;
}
