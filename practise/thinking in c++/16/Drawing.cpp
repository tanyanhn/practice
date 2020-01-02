#include <vector> // Uses Standard vector too!
#include "TPStash2.h"
#include "TStack2.h"
#include "Shape.h"
using namespace std;

// A Drawing is primarily a container of Shapes:
class Drawing : public PStash<Shape> {
public:
    ~Drawing() { cout << "~Drawing\n"; }
};

// A Plan is a different container of Shapes:
class Plan :  public Stack<Shape> {
public:
    ~Plan() { cout << "~Plan\n"; }
};

// A Schematic is a different container of Shapes:
class Schematic : public vector<Shape*> {
public:
    ~Schematic() { cout << "~Schematic\n"; }
};

// A function template
template<class Iter>
void drawAll(Iter start, Iter end) {
    while(start != end) {
        (*start)->draw();
        start++;
    }
}

int main() {
    // Each type of container has a different interface:
    Drawing d;
    d.add(new Circle);
    d.add(new Square);
    d.add(new Line);
    Plan p;
    p.push(new Line);
    p.push(new Square);
    p.push(new Circle);
    Schematic s;
    s.push_back(new Square);
    s.push_back(new Circle);
    s.push_back(new Line);
    Shape* sarray[] = {
        new Circle, new Square, new Line
    };
    // The iterators and the template function
    // allow them to be treated generically :
    cout << "Drawing d:\n";
    drawAll(d.begin(), d.end());
    cout << "Plan p:\n";
    drawAll(p.begin(), p.end());
    cout << "Schematic s:\n";
    drawAll(s.begin(), s.end());
    cout << "Array sarray:\n";
    // Even workd with array pointers:
    drawAll(sarray, sarray + sizeof(sarray)/sizeof(*sarray));
    cout << "End of main\n";
}
