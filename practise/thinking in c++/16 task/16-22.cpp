#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
using namespace std;
template <class T>
class SafeVector : private vector<void*> {
public:
    void push_back(T* s) {
        vector<void*>::push_back(s);
    }
    T* operator[](size_t n)  {
        return reinterpret_cast<T*>(vector<void*>::operator[](n));
    }
    const T* operator[](size_t n) const {
        return reinterpret_cast<const T*>(vector<void*>::operator[](n));
    }
    using vector<void*>::size;
};

int main(){
    SafeVector<string> v;
    string s1("live"), s2("long"), s3("and"), s4("prosper");
    v.push_back(&s1);
    v.push_back(&s2);
    v.push_back(&s3);
    v.push_back(&s4);
    for(size_t i = 0; i < v.size(); ++i)
        cout << *v[i] << endl;
    
}
