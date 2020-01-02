#include <iostream>
using namespace std;

class Int{
    int i;
public:
    Int(int ii = 1) : i(ii) {
        if(i > 1000000 || i < 0) {
            cout << i << " too big or negative.\n";
            abort();
        }
    }
    int get(){ return i;}
    friend Int operator+(const Int& a, const Int& b) {
        Int c(a.get() + b.get());
        return c;
    }
    friend ostream& operator<<(ostream& os, const Int& a){
        os << a.get();
        return os;
    }
};

int main() {
    cout << "writing you mumber:\n";
    int x,y;
    cin >> x; cin >> y;
    cout << endl;
    Int a(x), b(y);
    cout << a + b << endl;
}
