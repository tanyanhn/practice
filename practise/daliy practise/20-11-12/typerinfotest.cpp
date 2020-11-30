#include<typeinfo>
#include<iostream>

using namespace std;

template <class T,typename K >
class Person {
public:
    Person(){}
    Person(const Person&){}
    // Person& operator=(const Person&){}
    virtual ~Person(){}
};


template<class T>
class man : public Person<T, int> {
public:
    man(){}
    man(const man&){}
    //man& operator=(const man&){}
    ~man(){int k;
        k = 1;}
};

int main(int argc, char *argv[])
{
    Person<double,int>* p = new man<double>;
    auto& rp = *p;
    cout << "*p is " << typeid(p).name() << "  " << typeid(*p).hash_code() << endl;
    cout << "*p is " << typeid(rp).name() << "  " << typeid(*p).hash_code() << endl;
    return 0;
}
