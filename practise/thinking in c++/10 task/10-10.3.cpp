#include <iostream>

extern void setVall(int);
extern void setVal2(int);
extern int getVall();
extern int getVal2();

int main(){
    using namespace std;
    setVall(1);
    setVal2(2);
    cout << "val in 10-10.1.cpp == " << getVall() << endl;
    cout << "val in 10-19.2.cpp == " << getVal2() << endl;
}
