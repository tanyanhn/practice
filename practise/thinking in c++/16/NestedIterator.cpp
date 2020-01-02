// Nesting an iterator inside the container

#include "fibonacci.h"
#include "../require.h"
#include <iostream>
#include <string>
using namespace std;

class IntStack {
    static const int ssize = 100;
    int stack[ssize];
    int top;
public:
    IntStack() : top(0) {}
    void push(int i) {
        require(top < ssize, "Too many push()es");
        stack[top++] = i;
    }
    int pop() {
        require(top > 0, "Too many pop()s");
        return stack[--top];
    }
    class iterator;
    friend iterator;
    class iterator {
        IntStack& s;
        int index;
    public:
        iterator(IntStack& is) : s(is), index(0) {}
        // To create the "end sentinel" iterator:
        iterator(IntStack& is, bool) : s(is), index(s.top) {}
        iterator(const iterator& is) : s(is.s), index(is.index) {}
        int current() const { return s.stack[index]; }
        iterator& operator++() { // Prefix
            require(index < s.top, "iterator moved out of range");
            index++;
            return *this;
        }
        iterator operator++(int) { // Postfix
            require(index < s.top, "iterator moved out of range");
            iterator a(*this);
            index++;
            return a;
        }
        // Jump an iterator forward
        iterator& operator+=(int amount) {
            require(index + amount < s.top, "IntStack::iterator::operator+=() tried to move out of bounds" );
            index += amount;
            return *this;
        }
        // To see if you're at the end:
        bool operator==(const iterator& rv) const {
            return index == rv.index;
        }
        bool operator!=(const iterator& rv) const {
            return index != rv.index;
        }
        friend ostream& operator<<(ostream& os, const iterator& it) {
            return os << it.current();
        }
    };
    iterator begin() { return iterator(*this); }
    // create the "end sentinel":
    iterator end() { return iterator(*this, true); }
};

int main() {
    IntStack is;
    for(int i = 0; i < 20; i++)
        is.push(fibonacci(i));
    cout << "Traverse the whole IntStack\n";
    IntStack::iterator it = is.begin();
    while(it != is.end())
        cout << it++ << endl;
    cout << "Traverse a portion of the IntStack\n";
    IntStack::iterator start = is.begin(), end = is.begin();
    start += 5, end += 15;
    cout << "start = " << start << endl;
    cout << "end = " << end << endl;
    while(start != end)
        cout << start++ << endl;
}
