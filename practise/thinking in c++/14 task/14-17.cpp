// =M @echo Compile InaccessibleBase.cpp by hand!
class Base  {
public:
    Base(){}
    ~Base(){}
    void print(){}
};

class Private : private Base {
public:
    Private(){}
    ~Private(){}
    void print(){}
};

class Protected : protected Base {
public:
    Protected(){}
    ~Protected(){}
    void print(){}
};

int main(){
    Private pri;
    Protected pro;

    // Both statement are errors:
    Base* b = static_cast<Base*>(&pri);
    b = static_cast<Base*>(&pro);
}
