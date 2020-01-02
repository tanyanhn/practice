class A {
public:
    A& f() const {
    static int i = 1;
    return *this;
    }
};

int main() {
    A a;
    A b = a.f();
}
