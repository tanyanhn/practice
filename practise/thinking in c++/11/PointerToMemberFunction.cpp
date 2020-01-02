#include<iostream>
using namespace std;

class Widget {
    void f(int k) const { cout << k << " Widget::f()\n"; }
    void g(int k) const { cout << k << " Widget::g()\n"; }
    void h(int k) const { cout << k << " Widget::h()\n"; }
    void i(int k) const { cout << k << " Widget::i()\n"; }
    static const int cnt = 4;
    void (Widget::*fptr[cnt])(int) const;
public:
    Widget(){
        fptr[0] = &Widget::f;
        fptr[1] = &Widget::g;
        fptr[2] = &Widget::h;
        fptr[3] = &Widget::i;
    }
    void select(int i, int j) {
        if (i < 0 || i >= cnt) return;
        (this->*fptr[i])(j);
    }
    int count () { return cnt; }
    ~Widget(){}
    void print(){}
};

int main() {
    Widget w;
    for (int i = 0; i < w.count(); i++)
        w.select(i , (i)^10 );
}
