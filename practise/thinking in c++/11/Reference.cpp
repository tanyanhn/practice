int* f(int* x) {
    (*x)++;
    return x;
}

int& g(int& x) {
    x++;
    return x;
}

int& h() {
    int q;
    //! return q;
    static int x;
    return x;
}

int main () {
    int a = 0;
    f(&a);
    g(a);
}
