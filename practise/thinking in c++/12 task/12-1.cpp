class A {
    int i;
public:
    A(int ii = 0) : i(ii) {}
    ~A(){}
    const A& operator++() {
        i++;
        return *this;
    }
    const A operator++(int) {
        A a(i);
        i++;
        return a;
    }
    void print(){}
};

int main() {
    A a;
    a++;
    ++a;
}
