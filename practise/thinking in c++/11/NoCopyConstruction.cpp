class NoCC {
    int i;
    NoCC(const NoCC&);
public:
    NoCC(int ii = 0) : i(ii) {}
    ~NoCC(){}
    void print(){}
};

void f(NoCC);

int main() {
    NoCC n;
    // f(n);
    //NoCC n2 = n;
    //NoCC n3(n);
}
