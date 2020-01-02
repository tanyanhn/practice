#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Set {
    vector<T*> v;
    int next;
    int quantity;
    static const int sz = 10;
    void inflate(int increase = sz) {
        vector<T*> v1(quantity + increase);
        for(int i = 0 ; i < quantity; i++)
            v1[i] = v[i];
        quantity += increase;
        v = v1;
    }
public:
    Set() : v(sz), next(0), quantity(sz) {
        for(int i = 0; i < sz; i++)
            v[sz] = 0;
    }
    ~Set() {
        iterator b = begin(), e = end();
        while(!(b == e)){
            T* t = remove(b);
            delete t;
            b++;
        }
    }
    int count() const { return (next-1);}
    friend class iterator;
    class iterator {
        int index;
        Set& s;
    public:
        iterator(Set& set) :s(set), index(0) {}
        iterator(const iterator& it) : s(it.s), index(it.index) {}
        iterator(Set& set,bool) : s(set) , index(set.quantity - 1) {}
        iterator& operator=(const iterator& it) {
            s = it.s;
            index = it.index;
            return *this;
        }
        iterator& operator++() {
            index++;
            return *this;
        }
        const iterator operator++(int) {
            iterator i = *this;
            index++;
            return i;
        }
        T* operator*() const { return s.v[index];}
        T* remove() { return s.remove(index); }
        bool operator==(const iterator& it) const {
            return index == it.index;
        }
        iterator& operator+(int i) {
            index += i;
            return *this;
        }
        friend class Set;
        friend ostream& operator<<(ostream& os, const iterator it){
            print(os,it.s,it.index);
            return os;
        }
    };
    friend void print(ostream& os, Set& s, int index) {
        os << s.v[index];
    }
    iterator begin() { return iterator(*this); }
    iterator end() { return iterator(*this, true);}
    iterator find(T* t) {
        iterator b = begin(), e = end();
        while(!(b == e)){
            if(*b == t) return b;
            b++;
        }
        return e;
    }
    iterator insert(T* t, bool& tf) {
        iterator e = end();
        if(e == find(t)){
            iterator s = find(0);
            if(!(s == e))
            {v[s.index] = t;next++ ; tf = true; return s; }
            else {inflate(sz); insert(t,tf);}
        }
        tf = false;
        return find(t);
    }
    T* remove(int index) {
        T* t = v[index];
        v[index] = 0;
        next--;
        return t;
    }
    T* remove(iterator it) {
        it.remove();
    }
    T* remove(T* t) {
        iterator s = find(t), e = end();
        if(s == e) return 0;
        next--;
        T* m = *s;
        v[s.index] = 0;
        return m;
    }
};

int main() {
    Set<int> set;
    bool tf;int* k;
    int* ip = new int(8);
    // vector<int> vk(100);
      set.insert(ip,tf);
    for(int j = 0; j < 100; j++){
        k = new int(j * j);
        set.insert(k, tf);
    }
    int m = 1;
    Set<int>::iterator b = set.begin(), e = set.end();
    while(!(b == e)){
        cout << m << ':' << b << endl;
        b++;m++;
    }
    b = set.find(ip);
    cout << "ip: " << b <<"\n";
    int* p = set.remove(b);
    delete p;
    p = set.remove(25);
    cout << "25: " << p <<"\n";
    delete p;
    e = e +(-47);
    int* t = *e;
    p = set.remove(t);
    cout << "-47: " << p <<"\n";
    delete p;
    b = set.begin(); e = set.end();m = 1;
    while(!(b == e)){
        cout << m << ':' << b << endl;
        b++;m++;
    }
}
