// A class to reuse
#ifndef USEFUL_H
#define USEFUL_H

class X {
    int i;
public:
    X(){ i = 0; }
    ~X(){}
    void set(int ii) { i = ii; }
    int read() const {return i; }
    int permute() { return i = i * 47; }
    void print(){}
};

#endif
