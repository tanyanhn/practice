// Operator new for arrays
#include <new> // Size_t definition
#include <fstream>
using namespace std;
ofstream trace("ArrayOperatorNew.out");

class Widget {
    static const int sz = 10;
    int i[sz];
public:
    Widget(){ trace << "*"; }
    ~Widget(){ trace << "~"; }
    void* operator new(size_t sz) {
        trace << "Widget::new: " << sz << " bytes" << endl;
        return ::new char[sz];
    }
    void operator delete(void* p) {
        trace << "Widget::delete" << endl;
        free(p);
    }
    void* operator new[](size_t sz) {
        trace << "Widget::new[]" << sz << " bytes" << endl;
        return ::new char[sz];
    }
    void operator delete[](void* p) {
        trace << "Widget::delete[]" << endl;
        free(p);
    }
    void print(){}
};

int main () {
    trace << "new Widget" << endl;
    Widget* w = new Widget;
    trace << "\ndelete Widget" << endl;
    delete w;
    trace << "\nnew Widget[25]" << endl;
    Widget* wa = new Widget[25];
    trace << "\ndelete []Widget" << endl;
    delete []wa;
}
