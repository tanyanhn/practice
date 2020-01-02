class SpaceShip  {
public:
    void fly() {}
    SpaceShip(){}
    ~SpaceShip(){}
    void print(){}
};

class Shuttle : public SpaceShip {
public:
    void land() {}
    Shuttle(){}
    ~Shuttle(){}
    void print(){}
};

int main(){
    Shuttle shut;
    SpaceShip& ship = static_cast<SpaceShip&>(shut);
    ship.land();
}
