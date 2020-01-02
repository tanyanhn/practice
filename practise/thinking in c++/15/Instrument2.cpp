// Inherrtance & upcasting
#include <iostream>
using namespace std;
enum note{
    middleC, Csharp, Eflat
}; // Etc.

class Instrument  {
public:
    virtual void play(note) const {
        cout << "Instrument::play" << endl;
    }
    Instrument(){}
    ~Instrument(){}
    void print(){}
};

// Wind objects are Instruments
// because they have the same interface:
class Wind : public Instrument {
public:
    // Redefien interface function:
    void play(note) const {
        cout << "Wind::play\n";
    }
    Wind(){}
    ~Wind(){}
    void print(){}
};

void tune(Instrument& i) {
    // ...
    i.play(middleC);
}

int main() {
    Wind flute;
    tune(flute); // Upcasting
}
