// Templatized Stack with nested iterator
#ifndef TSTACK2_H
#define TSTACK2_H
#include "../require.h"
template<class T> class Stack {
    struct Link {
        T* data;
        Link* next;
        Link(T* dat, Link* nxt) : data(dat), next(nxt) {}
    }* head;
public:
    Stack() : head(0) {}
    ~Stack();
    void push(T* dat) {
        head = new Link(dat, head);
    }
    T* peek() const {
        return head ? head->data : 0;
    }
    T* pop();
    // Nested iterator class:
    class iterator; // Declaration required
    friend class iterator; // Make it a friend
    class iterator { // Now define it
        Stack::Link* p;
    public:
        iterator(const Stack<T>& t1) : p(t1.head) {}
        // Copy-constructor:
        iterator(const iterator& t1) : p(t1.p) {}
        // The end sentinel iterator:
        iterator() : p(0) {}
        // operator++ returns boolean indicating end:
        bool operator++() {
            if(p->next)
                p = p->next;
            else p = 0; // Indecaties end of list
            return bool(p);
        }
        bool operator++(int) { return operator++(); }
        T* current() const {
            if(!p) return 0;
            return p->data;
        }
        // Pointer dereference operator:
        T* operator->() const {
            require(p != 0, "PStack::iterator::operator->returns 0");
            return current();
        }
        T* operator*() const { return current(); }
        // bool conversion for conditional test:
        operator bool() const { return bool(p); }
        // Comparison to test for end:
        bool operator==(const iterator& l) const {
            return p == l.p;
        }
        bool operator!=(const iterator& l) const {
            return p != l.p;
        } 
    };
    iterator begin() const {
        return iterator(*this);
    }
    iterator end() const { return iterator(); }
};

template<class T> Stack<T>::~Stack() {
    while(head)
        delete pop();
}

template<class T> T* Stack<T>::pop() {
    if(head == 0) return 0;
    T* result = head->data;
    Link* oldHead = head;
    head = head->next;
    delete oldHead;
    return result;
}

#endif
