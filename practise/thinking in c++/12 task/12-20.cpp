class A {
    int i;
public:
    A(){}
    ~A(){}
    void print(){}
    friend A& operator=(A& a, int i) {
        a.i = i;
        return *this;
    }
};

int main () {
    
}
/*12-20.cpp:7:36: error: ‘A& operator=(A&, int)’ must be a nonstatic member function
friend A& operator=(A& a, int i) {
^*/
