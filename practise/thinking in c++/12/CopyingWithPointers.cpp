
// Solving the pointer aliasing problemby
// duplicating what is pointed to during
// assignment and copy-construction.
#include <iostream>
#include <string>
#include "../require.h"
using namespace std;

class Dog {
    string nm;
public:
    Dog(const string& name) : nm(name) {
        cout << "Creating Dog : " << *this << "\n";
    }
    // Synthesized copy-construction & operator=
    // are correct.
    // Create a Dog from a Dog pointer:
    Dog(const Dog* dp, const string& msg) : nm(dp->nm + msg) {
        cout << "Copied dog " << *this << "from " << *dp << endl;
    }
    ~Dog(){
        cout << "Deleting Dog: " << *this << "\n";
    }
    void rename(const string& newName) {
        nm = newName;
        cout << "Dog renamed to: " << *this << "\n";
    }
    friend ostream& operator<<(ostream& os, const Dog& d) {
        return os << "[" << d.nm << "]";\
    }
    void print(){}
};

class DogHouse {
    Dog* p;
    string houseName;
public:
    DogHouse(Dog* dog, const string& house) : p(dog), houseName(house) {}
    DogHouse(const DogHouse& dh) : p(new Dog(dh.p, "copy-constructed")),
                                   houseName(dh.houseName + "copy-constructed") {}
    DogHouse& operator=(const DogHouse& dh) {
        // Check for self-assignment:
        if(&dh != this) {
            p = new Dog(dh.p, " assigned");
            houseName = dh.houseName + " assigned";
        }
        return *this;
    }
    void renameHouse(const string& newName) {
        houseName = newName;
    }
    Dog* getDog() const { return p; }
    ~DogHouse(){
        cout << "~DogHouse :" << houseName <<endl;
        delete p;
    }
    friend ostream& operator<<(ostream& os, const DogHouse& dh) {
        return os << "[" << dh.houseName << "] contains " << *dh.p;
    }
    void print(){}
};

int main(int argc, char *argv[])
{
    DogHouse fidos(new Dog("Fido"), "FidoHouse");
    cout << fidos << endl;
    DogHouse fidos2 = fidos; // Copy construction
    cout << fidos2 << endl;
    fidos2.getDog()->rename("Spot");
    fidos2.renameHouse("SpotHouse");
    cout << fidos2 << endl;
    fidos =fidos2; // Assignment
    cout << fidos << endl;
    fidos.getDog()->rename("Max");
    fidos2.renameHouse("MaxHouse");
    return 0;
}
