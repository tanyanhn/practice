#include <iostream>
using namespace std;

class Dog {
public:
    int run() const {
        cout << "run\n";
        return 0;
    }
    int eat(int i) const {
        cout << "eat\n";
        return i;
    }
    int sleep(int i, int j) const  {
        cout << "ZZZ\n";
        return i + j;
    }
    typedef int (Dog::*PMF0)() const;
    typedef int (Dog::*PMF1)(int) const;
    typedef int (Dog::*PMF2)(int , int) const;
    // operator->* must return an object
    // that has an operator():
    template<class PMF>
    class FunctionObject {
        Dog* ptr;
        PMF pmem;
    public:
        // Save the object pointer and member pointer
        FunctionObject(Dog* wp, PMF pmf)
            : ptr(wp), pmem(pmf) {
            cout << "FunctonObject constructor\n";
        }
        // Make the call using the object pointer
        // and member pointer
        int operator()() const {
            cout << "FunctionObject::operator()\n";
            return (ptr->*pmem)(); // Make the call
        }
        int operator()(int i) const {
            cout << "FunctionObject::operator(int)\n";
            return (ptr->*pmem)(i); 
        }
        int operator()(int i, int j) const {
            cout << "FunctionObject::operator(int, int)\n";
            return (ptr->*pmem)(i, j);
        }
    };

    template<class PMF>
    FunctionObject<PMF> operator->*(PMF pmf) {
        cout << "operator->*" << endl;
        return FunctionObject<PMF>(this, pmf);
    }
};

int main() {
    Dog w;
    Dog::PMF0 pmf0 = &Dog::run;
    cout << (w->*pmf0)() << endl;
    Dog::PMF1 pmf1 = &Dog::eat;
    cout << (w->*pmf1)(2) << endl;
    Dog::PMF2 pmf2 = &Dog::sleep;
    cout << (w->*pmf2)(3, 4) << endl;
}
